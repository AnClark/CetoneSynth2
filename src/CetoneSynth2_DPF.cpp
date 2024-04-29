#include "CetoneSynth2.h"
#include "full_parameters.hpp"

// -----------------------------------------------------------
// DISTRHO APIs

void CS2::initParameter(uint32_t index, Parameter& parameter)
{
    parameter.hints = kParameterIsAutomatable;

    // Fallback to classic VST 2.4 param range (0.0 ~ 1.0), to fit with Cetone's own param handlers.
    parameter.ranges.min = CS2_FullParam::getParameterMinValue(pParameters(index));
    parameter.ranges.max = CS2_FullParam::getParameterMaxValue(pParameters(index));
    parameter.ranges.def = CS2_FullParam::getParameterDefValue(pParameters(index));

    // Must set parameter.symbol, this is the unique ID of each parameter.
    // If not set, you can neither save presets nor reset to factory default, in VST3 and CLAP!
    char buff[256];
    CS2_FullParam::getParameterName_FullVer(pParameters(index), buff);
    parameter.symbol = String(buff).replace(' ', '_').replace('.', '_');
    parameter.name = String(buff);

    switch (index) {
        // The following parameters are switches
        case pFExp:
        case pL1Sync:
        case pL1Retrig:
        case pL1SNH:
        case pL2Sync:
        case pL2Retrig:
        case pL2SNH:
        case pArpSync:
        case pArpLoop:
            parameter.hints |= kParameterIsBoolean;
            break;

        // The following parameters are integer
        case pOSemi1:
        case pOSemi2:
        case pOSemi3:
        case pOFine1:
        case pOFine2:
        case pOFine3:
        case pOMode1:
        case pOMode2:
        case pOMode3:
        case pFMode:
        case pOFlags1:
        case pOFlags2:
        case pOFlags3:
            parameter.hints |= kParameterIsInteger;
            break;
    }
}

float CS2::getParameterValue(uint32_t index) const
{
    return this->getParameter_FullVer(index);
}

void CS2::setParameterValue(uint32_t index, float value)
{
    this->setParameter_FullVer(index, value);
}

void CS2::activate()
{
    this->resume();
}

void CS2::run(const float** inputs, float** outputs, uint32_t frames, const DISTRHO::MidiEvent* midiEvents, uint32_t midiEventCount)
{
    this->processEvents(midiEvents, midiEventCount);
    this->processReplacing((float**)inputs, outputs, frames);
}

void CS2::sampleRateChanged(double newSampleRate)
{
    this->setSampleRate(newSampleRate);
}

void CS2::bufferSizeChanged(int newBufferSize)
{
    this->setBlockSize(newBufferSize);
}


// -----------------------------------------------------------
// Extensions of Neotec's plugin API

float CS2::getParameter_FullVer(VstInt32 index) const
{
	DISTRHO_SAFE_ASSERT_RETURN(index >= 0 && index < pNumParameters, 0.0f)

	if (index == pVoices)
		return (float)this->_Synth->sPrg.voices;

	return this->_Synth->GetParameter(index);
}

void CS2::setParameter_FullVer(VstInt32 index, float value)
{
	DISTRHO_SAFE_ASSERT_RETURN(index >= 0 && index < pNumParameters, )

	// The following 2 parameters should only be changed via MIDI CC
	if (index == pAftertouch || index == pModwheel)
		return;

	this->_Synth->SetParameter(index, value);
}
