#include "Gui_DPF.hpp"
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

void CCetoneUI::_createSwitchButton(ScopedPointer<ImageSwitch>& switchButton, uint32_t paramId, uint absolutePosX, uint absolutePosY)
{
#if 0
	switchButton = new ImageSwitch(this, fImgSwitchButton_OFF, fImgSwitchButton_ON);
	switchButton->setId(paramId);
	switchButton->setAbsolutePos(absolutePosX, absolutePosY);
	switchButton->setCallback(this);
#endif
}

void CCetoneUI::_createButton(ScopedPointer<ImageButton>& button, uint id, Image& imageNormal, Image& imagePressed, uint absolutePosX, uint absolutePosY)
{
	button = new ImageButton(this, imageNormal, imagePressed);
	button->setId(id);
	button->setAbsolutePos(absolutePosX, absolutePosY);
	button->setCallback(this);
}
