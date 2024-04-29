#pragma once

#include "parameters.h"

struct CS2_PARAM
{
	const char* name;
	float min;
	float max;
	float def;	// See CS2::CreateEmptyPrg()
};

namespace CS2_FullParam {
	void    getParameterName_FullVer(pParameters index, char* text);
	float   getParameterMinValue(pParameters index);
	float	getParameterMaxValue(pParameters index);
	float	getParameterDefValue(pParameters index);
}
