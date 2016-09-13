#pragma once

#include "public.sdk/samples/vst/common/voicebase.h"
#include "public.sdk/samples/vst/common/voiceprocessor.h"
#include "pluginterfaces/vst/ivstevents.h"
#include "pluginterfaces/base/futils.h"
#include "Oscillator.h"
#include "Filter.h"

#ifndef VOICEPROCESSOR_BLOCKSIZE
	#define VOICEPROCESSOR_BLOCKSIZE 32
#endif

#define OSCILLATOR_NUM 8

namespace Steinberg {
namespace Vst {
namespace PPSynth {

// set of parameters used in synth
struct GlobalParameterState{
	OscillatorParameter oscParam[OSCILLATOR_NUM];

	FilterParameter filterParam;

	ParamValue masterVolume;
};

}
}
}

