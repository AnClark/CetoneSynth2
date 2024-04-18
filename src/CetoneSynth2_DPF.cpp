#include "CetoneSynth2.h"

void CS2::initParameter(uint32_t index, Parameter& parameter)
{
    parameter.hints = kParameterIsAutomatable;

    // Fallback to classic VST 2.4 param range (0.0 ~ 1.0), to fit with Cetone's own param handlers.
    parameter.ranges.min = 0.0f;
    parameter.ranges.max = 1.0f;
    parameter.ranges.def = getParameter(index);

    // Must set parameter.symbol, this is the unique ID of each parameter.
    // If not set, you can neither save presets nor reset to factory default, in VST3 and CLAP!
    char buff[256];
    getParameterName(index, buff);
    parameter.symbol = String(buff).replace(' ', '_').replace('.', '_');
    parameter.name = String(buff);
}

float CS2::getParameterValue(uint32_t index) const
{
    return this->getParameter(index);
}

void CS2::setParameterValue(uint32_t index, float value)
{
    this->setParameter(index, value);
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
