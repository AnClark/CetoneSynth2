#include "Gui_DPF.hpp"

#include "fonts/CetoneFonts.hpp"
#include "images/CS2_Art.hpp"
#include "parameters.h"

namespace Art = CS2_Art;
namespace Fonts = CetoneFonts;

CCetoneUI::CCetoneUI()
	: DISTRHO::UI(Art::backgroundWidth, Art::backgroundHeight)
	, fImgBackground(Art::backgroundData, Art::backgroundWidth, Art::backgroundHeight, kImageFormatBGR)
	, fImgKnob(Art::knob_normalData, Art::knob_normalWidth, Art::knob_normalHeight, kImageFormatBGRA)
	, fImgKnobRed(Art::knob_redData, Art::knob_redWidth, Art::knob_redHeight, kImageFormatBGR)
	, fImgKnobScale(Art::knob_scaleData, Art::knob_scaleWidth, Art::knob_scaleHeight, kImageFormatBGRA)
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
}

void CCetoneUI::parameterChanged(uint32_t index, float value)
{
	// Sync knobs' value
	auto iterCurrentKnob = fKnobMap.find(index);
	if (iterCurrentKnob != fKnobMap.end())	// Map key exists
		iterCurrentKnob->second->setValue(value);

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
	setParameterValue(button->getId(), down);
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
