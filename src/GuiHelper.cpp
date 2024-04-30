#include "Gui_DPF.hpp"
#include "defines.h"
#include "full_parameters.hpp"

using namespace CS2_FullParam;

void CCetoneUI::_createKnob(ScopedPointer<ImageKnob>& knob, uint32_t paramId, uint absolutePosX, uint absolutePosY, uint rotationAngle)
{
    DISTRHO_SAFE_ASSERT(paramId >= 0 && paramId < pNumParameters)

	Image& knob_image = fImgKnob;
    pParameters myParamId = (pParameters) paramId;

	knob = new ImageKnob(this, knob_image, ImageKnob::Vertical);
	knob->setId(paramId);
	knob->setAbsolutePos(absolutePosX, absolutePosY);
	knob->setRange(getParameterMinValue(myParamId), getParameterMaxValue(myParamId));
	knob->setDefault(getParameterDefValue(myParamId));
	knob->setValue(getParameterDefValue(myParamId));
	knob->setRotationAngle(rotationAngle);
	knob->setCallback(this);

    this->fKnobScaleDrawPoints.push_back(Point<int>(absolutePosX, absolutePosY));
	this->fKnobMap.insert(std::map<uint32_t, ImageKnob*>::value_type(paramId, knob.get()));
}

void CCetoneUI::_createSlider(ScopedPointer<ImageSlider>& slider, uint32_t paramId, uint startPosX, uint startPosY, uint endPosX, uint endPosY, float step, bool inverted)
{
#if 0
    slider = new ImageSlider(this, fSliderImage);
    slider->setId(paramId);
    slider->setStartPos(startPosX, startPosY);
    slider->setEndPos(endPosX, endPosY);
    slider->setRange(MinatonParams::paramMinValue(paramId), MinatonParams::paramMaxValue(paramId));
    slider->setStep(step);
    slider->setValue(MinatonParams::paramDefaultValue(paramId));
    slider->setInverted(inverted);
    slider->setCallback(this);
#endif
}

void CCetoneUI::_createSwitchButton(ScopedPointer<ImageSwitch>& switchButton, uint32_t controllerId, Image& imageOn, Image& imageOff, uint absolutePosX, uint absolutePosY)
{
	switchButton = new ImageSwitch(this, imageOff, imageOn);
	switchButton->setId(controllerId);
	switchButton->setAbsolutePos(absolutePosX, absolutePosY);
	switchButton->setCallback(this);
	switchButton->setDown(false);
}

void CCetoneUI::_createButton(ScopedPointer<ImageButton>& button, uint id, Image& imageNormal, Image& imagePressed, uint absolutePosX, uint absolutePosY)
{
	button = new ImageButton(this, imageNormal, imagePressed);
	button->setId(id);
	button->setAbsolutePos(absolutePosX, absolutePosY);
	button->setCallback(this);
}

void CCetoneUI::_syncOscWaveSelection(uint8_t oscId, uint32_t oscWave)
{
	DISTRHO_SAFE_ASSERT(oscId >= 0 && oscId < 3)
	DISTRHO_SAFE_ASSERT(oscWave >= 0 && oscWave <= 16)

	ImageSwitch *btnOff = fOscWaveOff[oscId], *btnSaw = fOscWaveSaw[oscId], *btnPulse = fOscWavePulse[oscId], *btnTri = fOscWaveTri[oscId], *btnNoise = fOscWaveNoise[oscId];

	this->fOscWave[oscId] = oscWave;

	switch (oscWave) {
		case OSCW_OFF:
			btnOff->setDown(true);
			btnSaw->setDown(false);
			btnPulse->setDown(false);
			btnTri->setDown(false);
			btnNoise->setDown(false);
			break;
		case OSCW_SAW:
			btnOff->setDown(false);
			btnSaw->setDown(true);
			btnPulse->setDown(false);
			btnTri->setDown(false);
			btnNoise->setDown(false);
			break;
		case OSCW_PULSE:
			btnOff->setDown(false);
			btnSaw->setDown(false);
			btnPulse->setDown(true);
			btnTri->setDown(false);
			btnNoise->setDown(false);
			break;
		case OSCW_TRI:
			btnOff->setDown(false);
			btnSaw->setDown(false);
			btnPulse->setDown(false);
			btnTri->setDown(true);
			btnNoise->setDown(false);
			break;
		case OSCW_NOISE:
			btnOff->setDown(false);
			btnSaw->setDown(false);
			btnPulse->setDown(false);
			btnTri->setDown(false);
			btnNoise->setDown(true);
			break;
	}
}

#define SET_PARAM_WAVE(param_id, osc_index, v) \
	this->fOscWave[osc_index] = v; \
	setParameterValue(param_id, v);

void CCetoneUI::_checkOscWaveSelection(uint32_t controllerId)
{
	switch (controllerId) {
		case kOOff1:
			SET_PARAM_WAVE(pOWave1, 0, OSCW_OFF);
			break;
		case kOSaw1:
			SET_PARAM_WAVE(pOWave1, 0, OSCW_SAW);
			break;
		case kOPulse1:
			SET_PARAM_WAVE(pOWave1, 0, OSCW_PULSE);
			break;
		case kOTri1:
			SET_PARAM_WAVE(pOWave1, 0, OSCW_TRI);
			break;
		case kONoise1:
			SET_PARAM_WAVE(pOWave1, 0, OSCW_NOISE);
			break;

		case kOOff2:
			SET_PARAM_WAVE(pOWave2, 1, OSCW_OFF);
			break;
		case kOSaw2:
			SET_PARAM_WAVE(pOWave2, 1, OSCW_SAW);
			break;
		case kOPulse2:
			SET_PARAM_WAVE(pOWave2, 1, OSCW_PULSE);
			break;
		case kOTri2:
			SET_PARAM_WAVE(pOWave2, 1, OSCW_TRI);
			break;
		case kONoise2:
			SET_PARAM_WAVE(pOWave2, 1, OSCW_NOISE);
			break;

		case kOOff3:
			SET_PARAM_WAVE(pOWave3, 2, OSCW_OFF);
			break;
		case kOSaw3:
			SET_PARAM_WAVE(pOWave3, 2, OSCW_SAW);
			break;
		case kOPulse3:
			SET_PARAM_WAVE(pOWave3, 2, OSCW_PULSE);
			break;
		case kOTri3:
			SET_PARAM_WAVE(pOWave3, 2, OSCW_TRI);
			break;
		case kONoise3:
			SET_PARAM_WAVE(pOWave3, 2, OSCW_NOISE);
			break;

		[[likely]] default:
			return;
	}

	_syncOscWaveSelection(0, this->fOscWave[0]);
	_syncOscWaveSelection(1, this->fOscWave[1]);
	_syncOscWaveSelection(2, this->fOscWave[2]);
}

void CCetoneUI::_syncOscModeSelection(uint8_t oscId, uint32_t oscMode)
{
	DISTRHO_SAFE_ASSERT(oscId >= 0 && oscId < 3)
	DISTRHO_SAFE_ASSERT(oscMode >= 0 && oscMode <= OSCM_SUPER)

	ImageSwitch *btnNorm = fOscModeNorm[oscId], *btnAdd = fOscModeAdd[oscId], *btnMul = fOscModeMul[oscId], *btnSuper = fOscModeSuper[oscId];

	this->fOscMode[oscId] = oscMode;

	switch (oscMode) {
		case OSCM_NORMAL:
			btnNorm->setDown(true);
			btnAdd->setDown(false);
			btnMul->setDown(false);
			btnSuper->setDown(false);
			break;
		case OSCM_ADD:
			btnNorm->setDown(false);
			btnAdd->setDown(true);
			btnMul->setDown(false);
			btnSuper->setDown(false);
			break;
		case OSCM_MUL:
			btnNorm->setDown(false);
			btnAdd->setDown(false);
			btnMul->setDown(true);
			btnSuper->setDown(false);
			break;
		case OSCM_SUPER:
			btnNorm->setDown(false);
			btnAdd->setDown(false);
			btnMul->setDown(false);
			btnSuper->setDown(true);
			break;
	}
}

#define SET_PARAM_MODE(param_id, osc_index, v) \
	this->fOscMode[osc_index] = v; \
	setParameterValue(param_id, v);

void CCetoneUI::_checkOscModeSelection(uint32_t controllerId)
{
	switch (controllerId) {
		case kONormal1:
			SET_PARAM_MODE(pOMode1, 0, OSCM_NORMAL);
			break;
		case kOAdd1:
			SET_PARAM_MODE(pOMode1, 0, OSCM_ADD);
			break;
		case kOMul1:
			SET_PARAM_MODE(pOMode1, 0, OSCM_MUL);
			break;
		case kOSuper1:
			SET_PARAM_MODE(pOMode1, 0, OSCM_SUPER);
			break;

		case kONormal2:
			SET_PARAM_MODE(pOMode2, 1, OSCM_NORMAL);
			break;
		case kOAdd2:
			SET_PARAM_MODE(pOMode2, 1, OSCM_ADD);
			break;
		case kOMul2:
			SET_PARAM_MODE(pOMode2, 1, OSCM_MUL);
			break;
		case kOSuper2:
			SET_PARAM_MODE(pOMode2, 1, OSCM_SUPER);
			break;

		case kONormal3:
			SET_PARAM_MODE(pOMode3, 2, OSCM_NORMAL);
			break;
		case kOAdd3:
			SET_PARAM_MODE(pOMode3, 2, OSCM_ADD);
			break;
		case kOMul3:
			SET_PARAM_MODE(pOMode3, 2, OSCM_MUL);
			break;
		case kOSuper3:
			SET_PARAM_MODE(pOMode3, 2, OSCM_SUPER);
			break;

		[[likely]] default:
			return;
	}

	_syncOscModeSelection(0, this->fOscMode[0]);
	_syncOscModeSelection(1, this->fOscMode[1]);
	_syncOscModeSelection(2, this->fOscMode[2]);
}

void CCetoneUI::_syncLfoWaveSelection(uint8_t lfoId, uint32_t lfoWave)
{
	DISTRHO_SAFE_ASSERT(lfoId >= 0 && lfoId < 2)
	DISTRHO_SAFE_ASSERT(lfoWave >= 0 && lfoWave <= 16)

	ImageSwitch *btnOff = fLfoWaveOff[lfoId], *btnSaw = fLfoWaveSaw[lfoId], *btnPulse = fLfoWavePulse[lfoId], *btnTri = fLfoWaveTri[lfoId], *btnNoise = fLfoWaveNoise[lfoId];

	this->fLfoWave[lfoId] = lfoWave;

	switch (lfoWave) {
		case OSCW_OFF:
			btnOff->setDown(true);
			btnSaw->setDown(false);
			btnPulse->setDown(false);
			btnTri->setDown(false);
			btnNoise->setDown(false);
			break;
		case OSCW_SAW:
			btnOff->setDown(false);
			btnSaw->setDown(true);
			btnPulse->setDown(false);
			btnTri->setDown(false);
			btnNoise->setDown(false);
			break;
		case OSCW_PULSE:
			btnOff->setDown(false);
			btnSaw->setDown(false);
			btnPulse->setDown(true);
			btnTri->setDown(false);
			btnNoise->setDown(false);
			break;
		case OSCW_TRI:
			btnOff->setDown(false);
			btnSaw->setDown(false);
			btnPulse->setDown(false);
			btnTri->setDown(true);
			btnNoise->setDown(false);
			break;
		case OSCW_NOISE:
			btnOff->setDown(false);
			btnSaw->setDown(false);
			btnPulse->setDown(false);
			btnTri->setDown(false);
			btnNoise->setDown(true);
			break;
	}
}

#define SET_PARAM_WAVE_LFO(param_id, lfo_index, v) \
	this->fLfoWave[lfo_index] = v; \
	setParameterValue(param_id, v);

void CCetoneUI::_checkLfoWaveSelection(uint32_t controllerId)
{
	switch (controllerId) {
		case kL1Off:
			SET_PARAM_WAVE_LFO(pL1Wave, 0, OSCW_OFF);
			break;
		case kL1Saw:
			SET_PARAM_WAVE_LFO(pL1Wave, 0, OSCW_SAW);
			break;
		case kL1Pulse:
			SET_PARAM_WAVE_LFO(pL1Wave, 0, OSCW_PULSE);
			break;
		case kL1Tri:
			SET_PARAM_WAVE_LFO(pL1Wave, 0, OSCW_TRI);
			break;
		case kL1Noise:
			SET_PARAM_WAVE_LFO(pL1Wave, 0, OSCW_NOISE);
			break;

		case kL2Off:
			SET_PARAM_WAVE_LFO(pL2Wave, 1, OSCW_OFF);
			break;
		case kL2Saw:
			SET_PARAM_WAVE_LFO(pL2Wave, 1, OSCW_SAW);
			break;
		case kL2Pulse:
			SET_PARAM_WAVE_LFO(pL2Wave, 1, OSCW_PULSE);
			break;
		case kL2Tri:
			SET_PARAM_WAVE_LFO(pL2Wave, 1, OSCW_TRI);
			break;
		case kL2Noise:
			SET_PARAM_WAVE_LFO(pL2Wave, 1, OSCW_NOISE);
			break;

		[[likely]] default:
			return;
	}

	_syncLfoWaveSelection(0, this->fLfoWave[0]);
	_syncLfoWaveSelection(1, this->fLfoWave[1]);
}
