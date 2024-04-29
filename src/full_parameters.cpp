#include "CetoneSynth2.h"
#include "parameters.h"

struct CS2_PARAM
{
	const char* name;
	float min;
	float max;
	float def;	// See CS2::CreateEmptyPrg()
};

static constexpr CS2_PARAM PARAM_LIST[pNumParameters] = {
	{"Osc1 Semitone", -64, 64 + 12, 64},
	{"Osc1 Fine", -64, 64, 64},
	{"Osc1 Morph", 0, 127, 64},
	{"Osc1 Wave", 0, 16, OSCW_SAW},   // Using bit calculation
	{"Osc1 Mode", 0, OSCM_SUPER + 1, OSCM_NORMAL},
	{"Osc1 Flags", 0, 0xFF, 0x80},
	{"Osc1 Spread", 0, 0, 0},  // TODO: Fix it up!

	{"Osc2 Semitone", -64, 64 + 12, 64},
	{"Osc2 Fine", -64, 64, 64 - 12},
	{"Osc2 Morph", 0, 127, 64},
	{"Osc2 Wave", 0, 16, OSCW_SAW},   // Using bit calculation
	{"Osc2 Mode", 0, OSCM_SUPER + 1, OSCM_NORMAL},
	{"Osc2 Flags", 0, 0xFF, 0x80},
	{"Osc2 Spread", 0, 0, 0},  // TODO: Fix it up!

	{"Osc3 Semitone", -64, 64 + 12, 64 + 12},
	{"Osc3 Fine", -64, 64, 64},
	{"Osc3 Morph", 0, 127, 64},
	{"Osc3 Wave", 0, 16, OSCW_SAW},   // Using bit calculation
	{"Osc3 Mode", 0, OSCM_SUPER + 1, OSCM_NORMAL},
	{"Osc3 Flags", 0, 0xFF, 0x80},
	{"Osc3 Spread", 0, 0, 0},  // TODO: Fix it up!

	{"Amp. A", 0, 127, 10},
	{"Amp. H", 0, 127, 10},
	{"Amp. D", 0, 127, 10},
	{"Amp. S", 0, 127, 90},
	{"Amp. R", 0, 127, 40},

	{"Mod1 A", 0, 127, 0},
	{"Mod1 H", 0, 127, 0},
	{"Mod1 D", 0, 127, 0},
	{"Mod1 S", 0, 127, 0},
	{"Mod1 R", 0, 127, 0},

	{"Mod2 A", 0, 127, 0},
	{"Mod2 H", 0, 127, 0},
	{"Mod2 D", 0, 127, 0},
	{"Mod2 S", 0, 127, 0},
	{"Mod2 R", 0, 127, 0},

	{"Master Vol.", 0, 127, 64},
	{"Pan", -64, 64, 64},
	{"VelSens", -64, 64, 64},
	{"Osc1 Vol.", 0, 127, 64},
	{"Osc2 Vol.", 0, 127, 64},
	{"Osc3 Vol.", 0, 127, 64},

	{"F. Cutoff", 0, 127, 127},
	{"F. Reso.", 0, 127, 64},
	{"F. VelSens", -64, 64, 64},
	{"F. Gain", -64, 64, 64},
	{"F. Env2", -64, 64, 64},
	{"F. Mode", FILTM_12DB, FILTM_24DB, FILTM_12DB},
	{"F. Type", FILTT_LP, FILTT_BR, FILTT_LP},
	{"F. Exp", 0, 255, 0},   // BOOL

	{"Voices", 0, 15, 10},	// This is AnClark's own default value
	{"Glide", 0, 127},

	{"Arp. Speed", 0, 127, 0},
	{"Arp. Length", 0, 7, 0},
	{"Arp. Note1", -64, 64 + 12, 64},
	{"Arp. Note2", -64, 64 + 12, 64},
	{"Arp. Note3", -64, 64 + 12, 64},
	{"Arp. Note4", -64, 64 + 12, 64},
	{"Arp. Note5", -64, 64 + 12, 64},
	{"Arp. Note6", -64, 64 + 12, 64},
	{"Arp. Note7", -64, 64 + 12, 64},
	{"Arp. Note8", -64, 64 + 12, 64},
	{"Arp. Sync", 0, 255, 255},	// BOOL
	{"Arp. Loop", 0, 255, 255},	// BOOL

	{"L1 Speed", 0, 127, 0},
	{"L1 Delay", 0, 127, 0},
	{"L1 PW", 0, 127, 64},
	{"L1 Keytrack", -64, 64, 64},
	{"L1 Wave", 0, 16, 0},	// Using bit calculation
	{"L1 Sync", 0, 255, 0},		// BOOL
	{"L1 Retrig", 0, 255, 0},	// BOOL
	{"L1 SNH", 0, 255, 0},		// BOOL

	{"L2 Speed", 0, 127, 0},
	{"L2 Delay", 0, 127, 0},
	{"L2 PW", 0, 127, 64},
	{"L2 Keytrack", -64, 64, 64},
	{"L2 Wave", 0, 16, 0},	// Using bit calculation
	{"L2 Sync", 0, 255, 0},		// BOOL
	{"L2 Retrig", 0, 255, 0},	// BOOL
	{"L2 SNH", 0, 255, 0},		// BOOL

	{"M1 Source", 0, 127, 0},
	{"M1 Amount", -64, 64},
	{"M1 Dest", 0, 127, 0},

	{"M2 Source", 0, 127, 0},
	{"M2 Amount", -64, 64, 64},
	{"M2 Dest", 0, 127, 0},

	{"M3 Source", 0, 127, 0},
	{"M3 Amount", -64, 64, 64},
	{"M3 Dest", 0, 127, 0},

	{"M4 Source", 0, 127, 0},
	{"M4 Amount", -64, 64, 64},
	{"M4 Dest", 0, 127, 0},

	{"M5 Source", 0, 127, 0},
	{"M5 Amount", -64, 64, 64},
	{"M5 Dest", 0, 127, 0},

	{"M6 Source", 0, 127, 0},
	{"M6 Amount", -64, 64, 64},
	{"M6 Dest", 0, 127, 0},

	// The following 2 parameters should only be changed via MIDI CC.
	// They should be read-only on generic UI (considered as output parameter).
	{"Aftertouch", 0, 15, 0},
	{"Mod Wheel", 0, 15, 0},

	{"Audio Vol.", 0, 127, 0},
	{"Audio Pan", -64, 64, 0},
};

void CS2::getParameterName_FullVer(VstInt32 index, char* text)
{
	if (index >= 0 && index < pNumParameters)
		vst_strncpy(text, PARAM_LIST[index].name, kVstMaxParamStrLen);
	else
		vst_strncpy(text, "Unknown", kVstMaxParamStrLen);
}

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

float CS2::getParameterMinValue(VstInt32 index)
{
	DISTRHO_SAFE_ASSERT_RETURN(index >= 0 && index < pNumParameters, 0.0f)

	return PARAM_LIST[index].min;
}

float CS2::getParameterMaxValue(VstInt32 index)
{
	DISTRHO_SAFE_ASSERT_RETURN(index >= 0 && index < pNumParameters, 0.0f)

	return PARAM_LIST[index].max;
}

float CS2::getParameterDefValue(VstInt32 index)
{
	DISTRHO_SAFE_ASSERT_RETURN(index >= 0 && index < pNumParameters, 0.0f)

	return PARAM_LIST[index].def;
}
