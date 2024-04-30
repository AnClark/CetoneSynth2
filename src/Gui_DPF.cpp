#include "Gui_DPF.hpp"

#include "fonts/CetoneFonts.hpp"
#include "images/CS2_Art.hpp"
#include "parameters.h"

namespace Art = CS2_Art;
namespace Buttons = CS2_Art;
namespace Fonts = CetoneFonts;

CCetoneUI::CCetoneUI()
	: DISTRHO::UI(Art::backgroundWidth, Art::backgroundHeight)
	, fImgBackground(Art::backgroundData, Art::backgroundWidth, Art::backgroundHeight, kImageFormatBGR)
	, fImgKnob(Art::knob_normalData, Art::knob_normalWidth, Art::knob_normalHeight, kImageFormatBGRA)
	, fImgKnobRed(Art::knob_redData, Art::knob_redWidth, Art::knob_redHeight, kImageFormatBGR)
	, fImgKnobScale(Art::knob_scaleData, Art::knob_scaleWidth, Art::knob_scaleHeight, kImageFormatBGRA)
	, fImgBtnOff_0(Buttons::btn_off_0Data, 40, 16)
	, fImgBtnOff_1(Buttons::btn_off_1Data, 40, 16)
	, fImgBtnSaw_0(Buttons::btn_saw_offData, 40, 16)
	, fImgBtnSaw_1(Buttons::btn_saw_onData, 40, 16)
	, fImgBtnPulse_0(Buttons::btn_pulse_offData, 40, 16)
	, fImgBtnPulse_1(Buttons::btn_pulse_onData, 40, 16)
	, fImgBtnTri_0(Buttons::btn_tri_offData, 40, 16)
	, fImgBtnTri_1(Buttons::btn_tri_onData, 40, 16)
	, fImgBtnNoise_0(Buttons::btn_noise_offData, 40, 16)
	, fImgBtnNoise_1(Buttons::btn_noise_onData, 40, 16)
	, fImgNorm_0(Buttons::btn_norm_offData, 40, 16)
	, fImgNorm_1(Buttons::btn_norm_onData, 40, 16)
	, fImgAdd_0(Buttons::btn_add_offData, 40, 16)
	, fImgAdd_1(Buttons::btn_add_onData, 40, 16)
	, fImgMul_0(Buttons::btn_mul_offData, 40, 16)
	, fImgMul_1(Buttons::btn_mul_onData, 40, 16)
	, fImgSuper_0(Buttons::btn_super_offData, 40, 16)
	, fImgSuper_1(Buttons::btn_super_onData, 40, 16)
{
	/* Initialize NanoVG font and text buffer */
	NanoVG::FontId font = fNanoText.createFontFromMemory("Source Sans Regular", Fonts::SourceSans3_RegularData, Fonts::SourceSans3_RegularDataSize, false);
	fNanoText.fontFaceId(font);
	memset(fLabelBuffer, '\0', sizeof(char) * (32 + 1));

	_createKnob(fOsc1Semi, pOSemi1, 4, 51);
	_createKnob(fOsc1Fine, pOFine1, 44, 51);
	_createKnob(fOsc1Morph, pOMorph1, 84, 51);

	_createKnob(fOsc2Semi, pOSemi2, 213, 51);
	_createKnob(fOsc2Fine, pOFine2, 253, 51);
	_createKnob(fOsc2Morph, pOMorph2, 293, 51);

	_createKnob(fOsc3Semi, pOSemi3, 422, 51);
	_createKnob(fOsc3Fine, pOFine3, 462, 51);
	_createKnob(fOsc3Morph, pOMorph3, 502, 51);

	_createKnob(fFilterCutoff, pFCutoff, 4, 154);
	_createKnob(fFilterResonance, pFQ, 44, 154);
	_createKnob(fFilterGain, pFGain, 84, 154);
	_createKnob(fFilterVel, pFVelsens, 124, 154);
	_createKnob(fFilterEnv, pFEnv2, 164, 154);

	_createKnob(fMixVol, pMixVol, 293, 154);
	_createKnob(fMixVel, pMixVelsens, 333, 154);
	_createKnob(fMixPan, pMixPan, 373, 154);
	_createKnob(fMixVol1, pMixVol1, 413, 154);
	_createKnob(fMixVol2, pMixVol2, 453, 154);
	_createKnob(fMixVol3, pMixVol3, 493, 154);

	_createKnob(fAmpAttack, pAttack1, 4, 241);
	_createKnob(fAmpHold, pHold1, 44, 241);
	_createKnob(fAmpDecay, pDecay1, 84, 241);
	_createKnob(fAmpSustain, pSustain1, 124, 241);
	_createKnob(fAmpRelease, pRelease1, 164, 241);

	_createKnob(fMod1Attack, pAttack2, 213, 241);
	_createKnob(fMod1Hold, pHold2, 253, 241);
	_createKnob(fMod1Decay, pDecay2, 293, 241);
	_createKnob(fMod1Sustain, pSustain2, 333, 241);
	_createKnob(fMod1Release, pRelease2, 373, 241);

	_createKnob(fMod2Attack, pAttack3, 422, 241);
	_createKnob(fMod2Hold, pHold3, 462, 241);
	_createKnob(fMod2Decay, pDecay3, 502, 241);
	_createKnob(fMod2Sustain, pSustain3, 542, 241);
	_createKnob(fMod2Release, pRelease3, 582, 241);

	_createKnob(fLfo1Speed, pL1Speed, 4, 328);
	_createKnob(fLfo1Delay, pL1Delay, 44, 328);
	_createKnob(fLfo1Pw, pL1PW, 84, 328);
	_createKnob(fLfo1KTrack, pL1Keytrack, 124, 328);

	_createKnob(fLfo2Speed, pL2Speed, 4, 415);
	_createKnob(fLfo2Delay, pL2Delay, 44, 415);
	_createKnob(fLfo2Pw, pL2PW, 84, 415);
	_createKnob(fLfo2KTrack, pL2Keytrack, 124, 415);

	_createKnob(fVoices, pVoices, 542, 154);
	_createKnob(fGlide, pGlide, 582 , 154);

	_createKnob(fMod1Source, pM1Source, 250, 328);
	_createKnob(fMod1Amount, pM1Amount, 290, 328);
	_createKnob(fMod1Dest, pM1Dest, 330, 328);

	_createKnob(fMod2Source, pM2Source, 376, 328);
	_createKnob(fMod2Amount, pM2Amount, 416, 328);
	_createKnob(fMod2Dest, pM2Dest, 456, 328);

	_createKnob(fMod3Source, pM3Source, 502, 328);
	_createKnob(fMod3Amount, pM3Amount, 542, 328);
	_createKnob(fMod3Dest, pM3Dest, 582, 328);

	_createKnob(fMod4Source, pM4Source, 250, 415);
	_createKnob(fMod4Amount, pM4Amount, 290, 415);
	_createKnob(fMod4Dest, pM4Dest, 330, 415);

	_createKnob(fMod5Source, pM5Source, 376, 415);
	_createKnob(fMod5Amount, pM5Amount, 416, 415);
	_createKnob(fMod5Dest, pM5Dest, 456, 415);

	_createKnob(fMod6Source, pM6Source, 502, 415);
	_createKnob(fMod6Amount, pM6Amount, 542, 415);
	_createKnob(fMod6Dest, pM6Dest, 582, 415);

	_createKnob(fArpSpeed, pArpSpeed, 4, 502);
	_createKnob(fArpLength, pArpLength, 44, 502);
	_createKnob(fArpNote1, pArpNote1, 84, 502);
	_createKnob(fArpNote2, pArpNote2, 124, 502);
	_createKnob(fArpNote3, pArpNote3, 164, 502);
	_createKnob(fArpNote4, pArpNote4, 204, 502);
	_createKnob(fArpNote5, pArpNote5, 244, 502);
	_createKnob(fArpNote6, pArpNote6, 284, 502);
	_createKnob(fArpNote7, pArpNote7, 324, 502);
	_createKnob(fArpNote8, pArpNote8, 364, 502);

	_createKnob(fAudioVol, pAudioVol, 453, 502);
	_createKnob(fAudioPan, pAudioPan, 493, 502);

	_createSwitchButton(fOscWaveOff[0], kOOff1, fImgBtnOff_1, fImgBtnOff_0, 164, 36);
	_createSwitchButton(fOscWaveSaw[0], kOSaw1, fImgBtnSaw_1, fImgBtnSaw_0, 164, 54);
	_createSwitchButton(fOscWavePulse[0], kOPulse1, fImgBtnPulse_1, fImgBtnPulse_0, 164, 70);
	_createSwitchButton(fOscWaveTri[0], kOTri1, fImgBtnTri_1, fImgBtnTri_0, 164, 86);
	_createSwitchButton(fOscWaveNoise[0], kONoise1, fImgBtnNoise_1, fImgBtnNoise_0, 164, 102);

	_createSwitchButton(fOscWaveOff[1], kOOff2, fImgBtnOff_1, fImgBtnOff_0, 373, 36);
	_createSwitchButton(fOscWaveSaw[1], kOSaw2, fImgBtnSaw_1, fImgBtnSaw_0, 373, 54);
	_createSwitchButton(fOscWavePulse[1], kOPulse2, fImgBtnPulse_1, fImgBtnPulse_0, 373, 70);
	_createSwitchButton(fOscWaveTri[1], kOTri2, fImgBtnTri_1, fImgBtnTri_0, 373, 86);
	_createSwitchButton(fOscWaveNoise[1], kONoise2, fImgBtnNoise_1, fImgBtnNoise_0, 373, 102);

	_createSwitchButton(fOscWaveOff[2], kOOff3, fImgBtnOff_1, fImgBtnOff_0, 582, 36);
	_createSwitchButton(fOscWaveSaw[2], kOSaw3, fImgBtnSaw_1, fImgBtnSaw_0, 582, 54);
	_createSwitchButton(fOscWavePulse[2], kOPulse3, fImgBtnPulse_1, fImgBtnPulse_0, 582, 70);
	_createSwitchButton(fOscWaveTri[2], kOTri3, fImgBtnTri_1, fImgBtnTri_0, 582, 86);
	_createSwitchButton(fOscWaveNoise[2], kONoise3, fImgBtnNoise_1, fImgBtnNoise_0, 582, 102);

	_createSwitchButton(fOscModeNorm[0], kONormal1, fImgNorm_1, fImgNorm_0, 4, 102);
	_createSwitchButton(fOscModeAdd[0], kOAdd1, fImgAdd_1, fImgAdd_0, 44, 102);
	_createSwitchButton(fOscModeMul[0], kOMul1, fImgMul_1, fImgMul_0, 84, 102);
	_createSwitchButton(fOscModeSuper[0], kOSuper1, fImgSuper_1, fImgSuper_0, 124, 102);

	_createSwitchButton(fOscModeNorm[1], kONormal2, fImgNorm_1, fImgNorm_0, 213, 102);
	_createSwitchButton(fOscModeAdd[1], kOAdd2, fImgAdd_1, fImgAdd_0, 253, 102);
	_createSwitchButton(fOscModeMul[1], kOMul2, fImgMul_1, fImgMul_0, 293, 102);
	_createSwitchButton(fOscModeSuper[1], kOSuper2, fImgSuper_1, fImgSuper_0, 333, 102);

	_createSwitchButton(fOscModeNorm[2], kONormal3, fImgNorm_1, fImgNorm_0, 422, 102);
	_createSwitchButton(fOscModeAdd[2], kOAdd3, fImgAdd_1, fImgAdd_0, 462, 102);
	_createSwitchButton(fOscModeMul[2], kOMul3, fImgMul_1, fImgMul_0, 502, 102);
	_createSwitchButton(fOscModeSuper[2], kOSuper3, fImgSuper_1, fImgSuper_0, 542, 102);

	_createSwitchButton(fLfoWaveOff[0], kL1Off, fImgBtnOff_1, fImgBtnOff_0, 164, 313);
	_createSwitchButton(fLfoWaveSaw[0], kL1Saw, fImgBtnSaw_1, fImgBtnSaw_0, 204, 313);
	_createSwitchButton(fLfoWavePulse[0], kL1Pulse, fImgBtnPulse_1, fImgBtnPulse_0, 204, 329);
	_createSwitchButton(fLfoWaveTri[0], kL1Tri, fImgBtnTri_1, fImgBtnTri_0, 204, 345);
	_createSwitchButton(fLfoWaveNoise[0], kL1Noise, fImgBtnNoise_1, fImgBtnNoise_0, 204, 361);

	_createSwitchButton(fLfoWaveOff[1], kL2Off, fImgBtnOff_1, fImgBtnOff_0, 164, 400);
	_createSwitchButton(fLfoWaveSaw[1], kL2Saw, fImgBtnSaw_1, fImgBtnSaw_0, 204, 400);
	_createSwitchButton(fLfoWavePulse[1], kL2Pulse, fImgBtnPulse_1, fImgBtnPulse_0, 204, 416);
	_createSwitchButton(fLfoWaveTri[1], kL2Tri, fImgBtnTri_1, fImgBtnTri_0, 204, 432);
	_createSwitchButton(fLfoWaveNoise[1], kL2Noise, fImgBtnNoise_1, fImgBtnNoise_0, 204, 448);
}

void CCetoneUI::parameterChanged(uint32_t index, float value)
{
	// Sync knobs' value
	auto iterCurrentKnob = fKnobMap.find(index);
	if (iterCurrentKnob != fKnobMap.end()) {	// Map key exists
		iterCurrentKnob->second->setValue(value);
		return;
	}

	// Sync Osc switch buttons' value
	switch (index) {
		case pOWave1:
			_syncOscWaveSelection(0, (uint32_t)value);
			break;
		case pOWave2:
			_syncOscWaveSelection(1, (uint32_t)value);
			break;
		case pOWave3:
			_syncOscWaveSelection(2, (uint32_t)value);
			break;

		case pOMode1:
			_syncOscModeSelection(0, (uint32_t)value);
			break;
		case pOMode2:
			_syncOscModeSelection(1, (uint32_t)value);
			break;
		case pOMode3:
			_syncOscModeSelection(2, (uint32_t)value);
			break;

		case pL1Wave:
			_syncLfoWaveSelection(0, (uint32_t)value);
			break;
		case pL2Wave:
			_syncLfoWaveSelection(1, (uint32_t)value);
			break;
	}

	// Explicitly ask DPF to redraw UI (for updating labels)
	repaint();
}

// -------------------------------------------------------------------
// Widget Callbacks

void CCetoneUI::imageButtonClicked(ImageButton* button, int)
{
#if 0
	switch (button->getId()) {
	case BTN_PANIC: {
		panic();
		break;
	}
	}
#endif
}

void CCetoneUI::imageSwitchClicked(ImageSwitch* button, bool down)
{
	_checkOscWaveSelection(button->getId());
	_checkOscModeSelection(button->getId());
	_checkLfoWaveSelection(button->getId());
}

void CCetoneUI::imageKnobDragStarted(ImageKnob* knob)
{
	editParameter(knob->getId(), true);
}

void CCetoneUI::imageKnobDragFinished(ImageKnob* knob)
{
	editParameter(knob->getId(), false);
}

void CCetoneUI::imageKnobValueChanged(ImageKnob* knob, float value)
{
	setParameterValue(knob->getId(), value);

	// Explicitly ask DPF to redraw UI (for updating labels)
	repaint();
}

void CCetoneUI::imageSliderDragStarted(ImageSlider* slider)
{
	editParameter(slider->getId(), true);
}

void CCetoneUI::imageSliderDragFinished(ImageSlider* slider)
{
	editParameter(slider->getId(), false);
}

void CCetoneUI::imageSliderValueChanged(ImageSlider* slider, float value)
{
	setParameterValue(slider->getId(), value);
}

void CCetoneUI::onDisplay()
{
	/**
	 * Draw background
	 */
	const GraphicsContext& context(getGraphicsContext());

	fImgBackground.draw(context);

	for (auto iter = fKnobScaleDrawPoints.begin(); iter != fKnobScaleDrawPoints.end(); ++iter) {
		fImgKnobScale.drawAt(context, *iter);
	}

	/**
	 * Draw labels
	 * NOTICE: Must invoke `repaint()` when tuning widgets, otherwise UI won't update.
	 */
	constexpr float r = 255.0f;
	constexpr float g = 255.0f;
	constexpr float b = 255.0f;

	fNanoText.beginFrame(this);
	fNanoText.fontSize(18);
	fNanoText.textAlign(NanoVG::ALIGN_CENTER | NanoVG::ALIGN_MIDDLE);

	fNanoText.fillColor(Color(r, g, b));

	fNanoText.endFrame();
}

void CCetoneUI::idleCallback() { }

// -----------------------------------------------------------------------

START_NAMESPACE_DISTRHO

UI* createUI()
{
	return new CCetoneUI();
}

END_NAMESPACE_DISTRHO
