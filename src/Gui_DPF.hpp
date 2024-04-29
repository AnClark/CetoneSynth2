#pragma once

#include "DistrhoUI.hpp"
#include "ImageWidgets.hpp"
#include "NanoVG.hpp"

#include <vector>
#include <map>

using DGL_NAMESPACE::ImageAboutWindow;
using DGL_NAMESPACE::ImageButton;
using DGL_NAMESPACE::ImageKnob;
using DGL_NAMESPACE::ImageSlider;
using DGL_NAMESPACE::ImageSwitch;

// -----------------------------------------------------------------------

class CCetoneUI : public DISTRHO::UI,
				  public ImageButton::Callback,
				  public ImageKnob::Callback,
				  public ImageSlider::Callback,
				  public ImageSwitch::Callback,
				  public IdleCallback {
public:
	CCetoneUI();

protected:
	// -------------------------------------------------------------------
	// DSP Callbacks

	void parameterChanged(uint32_t index, float value) override;

	// -------------------------------------------------------------------
	// Widget Callbacks

	void imageButtonClicked(ImageButton* button, int) override;
	void imageSwitchClicked(ImageSwitch* button, bool) override;
	void imageKnobDragStarted(ImageKnob* knob) override;
	void imageKnobDragFinished(ImageKnob* knob) override;
	void imageKnobValueChanged(ImageKnob* knob, float value) override;
	void imageSliderDragStarted(ImageSlider* slider) override;
	void imageSliderDragFinished(ImageSlider* slider) override;
	void imageSliderValueChanged(ImageSlider* slider, float value) override;

	void onDisplay() override;

	// -------------------------------------------------------------------
	// Other Callbacks

	void idleCallback() override;

private:
	// -------------------------------------------------------------------
	// Label renderer

	NanoVG fNanoText;
	char fLabelBuffer[32 + 1];

	// -------------------------------------------------------------------
	// Image resources

	Image fImgBackground, fImgKnobScale;
	Image fImgKnob, fImgKnobRed;
    std::vector<Point<int>> fKnobScaleDrawPoints;

	// -------------------------------------------------------------------
	// Widgets

	ScopedPointer<ImageKnob> fOsc1Semi, fOsc1Fine, fOsc1Morph;
	ScopedPointer<ImageKnob> fOsc2Semi, fOsc2Fine, fOsc2Morph;
	ScopedPointer<ImageKnob> fOsc3Semi, fOsc3Fine, fOsc3Morph;

    ScopedPointer<ImageKnob> fFilterCutoff, fFilterResonance, fFilterGain, fFilterVel, fFilterEnv;
    ScopedPointer<ImageKnob> fMixVol, fMixVel, fMixPan, fMixVol1, fMixVol2, fMixVol3;

	ScopedPointer<ImageKnob> fAmpAttack, fAmpHold, fAmpDecay, fAmpSustain, fAmpRelease;
	ScopedPointer<ImageKnob> fMod1Attack, fMod1Hold, fMod1Decay, fMod1Sustain, fMod1Release;
	ScopedPointer<ImageKnob> fMod2Attack, fMod2Hold, fMod2Decay, fMod2Sustain, fMod2Release;

	ScopedPointer<ImageKnob> fVoices, fGlide;

	ScopedPointer<ImageKnob> fLfo1Speed, fLfo1Delay, fLfo1Pw, fLfo1KTrack;
	ScopedPointer<ImageKnob> fLfo2Speed, fLfo2Delay, fLfo2Pw, fLfo2KTrack;

	ScopedPointer<ImageKnob> fMod1Source, fMod1Amount, fMod1Dest;
	ScopedPointer<ImageKnob> fMod2Source, fMod2Amount, fMod2Dest;
	ScopedPointer<ImageKnob> fMod3Source, fMod3Amount, fMod3Dest;
	ScopedPointer<ImageKnob> fMod4Source, fMod4Amount, fMod4Dest;
	ScopedPointer<ImageKnob> fMod5Source, fMod5Amount, fMod5Dest;
	ScopedPointer<ImageKnob> fMod6Source, fMod6Amount, fMod6Dest;

	ScopedPointer<ImageKnob> fArpSpeed, fArpLength;
	ScopedPointer<ImageKnob> fArpNote1, fArpNote2, fArpNote3, fArpNote4;
	ScopedPointer<ImageKnob> fArpNote5, fArpNote6, fArpNote7, fArpNote8;

	ScopedPointer<ImageKnob> fAudioVol, fAudioPan;

	// -------------------------------------------------------------------
	// Parameter maps

	std::map<uint32_t, ImageKnob*> fKnobMap;

	// -------------------------------------------------------------------
	// Helpers

	void _createKnob(ScopedPointer<ImageKnob>& knob, uint32_t paramId, uint absolutePosX, uint absolutePosY, uint rotationAngle = 275);
	void _createSlider(ScopedPointer<ImageSlider>& slider, uint32_t paramId, uint startPosX, uint startPosY, uint endPosX, uint endPosY, float step, bool inverted = false);
	void _createSwitchButton(ScopedPointer<ImageSwitch>& switchButton, uint32_t paramId, uint absolutePosX, uint absolutePosY);
	void _createButton(ScopedPointer<ImageButton>& button, uint id, Image& imageNormal, Image& imagePressed, uint absolutePosX, uint absolutePosY);

	DISTRHO_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CCetoneUI)
};

// -----------------------------------------------------------------------

// --------------------------------
// Button IDs

constexpr uint BTN_PANIC = d_cconst('p', 'n', 'i', 'c');

// -----------------------------------------------------------------------
