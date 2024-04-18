#pragma once

#include "MSVC_Compatibility.hpp"

//#define CS2DEBUG

#ifdef CS2DEBUG
#include "log.h"
#endif

#define nCLAMP(min, val, max) ((val > max) ? max : ((val < min) ? min : val))

#define PI 3.14159265f
#define PId 3.14159265358979323846
#define UNDENORM(v) if( (*((uint32_t*)&v) & 0x7f800000) == 0) v = 0

#define NOTE_MAX 120
#define NOTE_MAX1 (NOTE_MAX-1)
#define PITCH_MAX 12000
#define PITCH_MAX1 (PITCH_MAX-1)

#define WAVETABLE_LENGTH 2048
#define WAVETABLE_LENGTHf 2048.0f
#define WAVETABLE_LENGTH1 (WAVETABLE_LENGTH-1)
#define WAVETABLE_LENGTH2 (WAVETABLE_LENGTH/2)
#define WAVETABLE_LENGTH4 (WAVETABLE_LENGTH/4)
#define WAVETABLE_MASK (WAVETABLE_LENGTH-1)

#define OSCW_OFF 0
#define OSCW_SAW 1
#define OSCW_PULSE 2
#define OSCW_TRI 4
#define OSCW_NOISE 8

#define OSCM_NORMAL 0
#define OSCM_ADD 1
#define OSCM_MUL 2
#define OSCM_SUPER 3

#define EFFECT_NAME "CetoneSynth2"
#define CLASS_NAME "CetoneSynth2"
#define VENDOR_NAME "Neotec Software"
#define PRODUCT_NAME "CetoneSynth2"
#define VERSION_NUMBER 6
#define REAL_VERSION 0x007500

typedef struct
{
	uint16_t frac;
	int16_t index;
} sFIXED;

typedef union
{
	sFIXED fixed;
	int32_t int32;
} oSTEP;

typedef struct
{
	uint8_t semi;
	uint8_t fine;
	uint8_t morph;
	uint8_t flags;
	uint8_t wave;
	uint8_t mode;
	uint8_t spread;
	uint8_t pad;
} sOSC;	// 8

typedef struct
{
	uint8_t a, h, d, s, r;
	uint8_t pad[3];
} sENV;	// 8

typedef struct
{
	uint8_t speed;
	uint8_t delay;
	uint8_t pw;
	uint8_t keytrack;
	uint8_t wave;
	uint8_t sync;
	uint8_t snh;
	uint8_t retrig;
} sLFO;	// 8

typedef struct
{
	uint8_t source;
	uint8_t amount;
	uint8_t dest;
	uint8_t pad[1];
} sMOD;	// 4

typedef struct
{
	uint8_t cutoff;
	uint8_t q;
	uint8_t gain;
	uint8_t velsens;
	uint8_t env2;
	uint8_t db;
	uint8_t mode;
	uint8_t exp;
} sFILT;	// 8

typedef struct
{
	uint8_t volume;
	uint8_t velsens;
	uint8_t panning;
	uint8_t osc1;
	uint8_t osc2;
	uint8_t osc3;
	uint8_t pad[2];
} sMIX;	// 8

typedef struct
{
	uint8_t flags;
	uint8_t speed;
	uint8_t length;
	uint8_t loop;
	uint8_t sync;
	uint8_t note[8];
	uint8_t pad[3];
} sARP;	// 16

typedef struct 
{
	int32_t version;	// 4
	char name[26];		// + 26		= 30
	sOSC osc[3];		// + 3 * 8	= 54
	sLFO lfo[2];		// + 2 * 8	= 70
	sENV env[3];		// + 3 * 8	= 94
	sFILT filter;		// + 8		= 102
	sMIX mixer;			// + 8		= 110
	sMOD mod[6];		// + 6 * 4	= 134
	sARP arp;			// + 16		= 150
	uint8_t voices;	// 151
	uint8_t glide;	// 152
	uint8_t audioVol;
	uint8_t audioPan;
	uint8_t pad[102];
} sPRG;

#if _M_IX86_FP > 0
#define truncate(x) ((int)(x))
#else
__forceinline int truncate(float flt)
{
	return static_cast<int>(flt);
}
#endif
