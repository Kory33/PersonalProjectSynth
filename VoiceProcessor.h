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

#define OSCILLATOR_POLYLAYER_NUM 64
#define OSCILLATOR_NUM 8
#define DEFAULTPARAM_MASTER_VOLUME 1.

namespace Steinberg {
namespace Vst {
namespace PPSynth{

enum class vOscParameters{
	OscParamNum
};

enum class vFiltParameters{
	FiltParamNum
};

// set of parameters used in synth
struct GlobalParameterState{
	OscillatorParameter oscParam[OSCILLATOR_NUM];

	FilterParameter filterParam;

	ParamValue masterVolume;
	
	// set a parameter
	tresult setState(IBStream*);

	// get a parameter
	tresult getState(IBStream*);
};


uint32 paramNum = static_cast<int>(vOscParameters::OscParamNum) * OSCILLATOR_NUM + 
			   static_cast<int>(vFiltParameters::FiltParamNum);

// VoiceProcessor class
template<class SamplePrecision>
class Voice : public VoiceBase<paramNum, SamplePrecision, 2, GlobalParameterState> {
public:
	Voice ();
	~Voice();

	void setSampleRate (ParamValue sampleRate);
	void noteOn (int32 pitch, ParamValue velocity, float tuning, int32 sampleOffset, int32 nId);
	void noteOff (ParamValue velocity, int32 sampleOffset);

	bool process (SamplePrecision* outputBuffers[2], int32 numSamples);
	void reset ();

	void setNoteExpressionValue (int32 index, ParamValue value);
};

}
}
}

