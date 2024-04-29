#pragma once

//#include <windows.h>
//#include "aeffeditor.h"
//#include "audioeffectx.h"
#include "DistrhoPlugin.hpp"
#include "VST2.4_Compatibility.hpp"
#include "Synth.h"
#ifdef _WIN32
#include <windows.h>
#endif

class CS2 : public DISTRHO::Plugin//AudioEffectX
{
public:
	//CS2(audioMasterCallback audioMaster);
	CS2();
	~CS2();

	const char*	getLabel() const noexcept override { return EFFECT_NAME; }
	const char*	getDescription() const override { return "Multifunctional synthesizer"; }
	const char*	getMaker() const noexcept override { return DISTRHO_PLUGIN_BRAND; }
	const char*	getLicense() const noexcept override { return "GPLv3"; }
	uint32_t	getVersion() const noexcept override { return d_version(1, 0, 0); }
	int64_t	getUniqueId() const noexcept override { return d_cconst('c', 'S', 'C', '2'); }

	void	initParameter(uint32_t index, Parameter& parameter) override;
	float	getParameterValue(uint32_t index) const override;
	void	setParameterValue(uint32_t index, float value) override;

	void	activate() override;
	void	run(const float** inputs, float** outputs, uint32_t frames, const MidiEvent* midiEvents, uint32_t midiEventCount) override;
	void	bufferSizeChanged(int newBufferSize);
	void	sampleRateChanged(double newSampleRate) override;

	void		process(float **inputs, float **outputs, VstInt32 sampleFrames); 	
	void		processReplacing(float** inputs, float** outputs, VstInt32 sampleFrames);
	VstInt32	getVendorVersion ();
	bool		getEffectName(char* name);
	bool		getVendorString(char* text);
	bool		getProductString(char* text);
	void		setSampleRate(float sampleRate);
	void		setBlockSize(VstInt32 blockSize);
	void		setBlockSizeAndSampleRate(VstInt32 blockSize, float sampleRate) { this->setSampleRate(sampleRate); this->setBlockSize(blockSize); }
	VstInt32	getNumMidiInputChannels() { return 1; };
	VstInt32	getNumMidiOutputChannels() { return 1; };
	VstInt32	canDo(char* text);
	//VstInt32	processEvents(VstEvents *events);
	VstInt32	processEvents(const DISTRHO::MidiEvent* events, uint32_t eventCount);
	void		HandleMidi(int p0, int p1, int p2);

	void		setParameter(VstInt32 index, float value);
	void		setParameter_FullVer(VstInt32 index, float value);
	float		getParameter(VstInt32 index) const;
	float		getParameter_FullVer(VstInt32 index) const;
	void		getParameterLabel(VstInt32 index, char* label);
	void		getParameterDisplay(VstInt32 index, char* text);
	void		getParameterName(VstInt32 index, char* text);
	void		getParameterName_FullVer(VstInt32 index, char* text);
	float		getParameterMinValue(VstInt32 index);
	float		getParameterMaxValue(VstInt32 index);
	float		getParameterDefValue(VstInt32 index);
	void		getProgramName(char* name);
	bool		getProgramNameIndexed(VstInt32 category, VstInt32 index, char* name);
	void		setProgramName(char* name);
	void		setProgram(VstInt32 program);
	VstInt32	getChunk(void **data, bool isPreset = false);
	VstInt32	setChunk(void *data, VstInt32 byteSize, bool isPreset = false);
	void		CreateEmptyPrg(sPRG* p, int nr = -1);
	void		resume();
	void		suspend();
	void		LoadPresets(const char* name);
	char*		GetFileName(const char* name);
	[[__maybe_unused__]]	void	GuiUpdater(int ctrl);
	void		CCDispatcher(int ctrl, int val);
private:
	void		CheckPrg();
	void		CheckPrg(int i);
	void		SetVersion();
	void		SetVersion(int i);
	char		path[512];
	char		tempname[512];
	LARGE_INTEGER perfFreq;
	void		myProcess(float **inputs, float **outputs, VstInt32 sampleFrames, bool replace); 	
	int			np0, np1, np2, cdelta;
	Synth*		_Synth;
	MidiStack*	mStack;
	sPRG		programs[128];
	sPRG		emptyPrg;

	// VST 2.4 specific variables. Seems to provided by SDK
	VstInt32	curProgram;
	float		sampleRate;
};
