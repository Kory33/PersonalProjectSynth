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
	receiveChannel,
	filterParamOffset
};

enum class vFiltParameters{
	masterParamOffset = static_cast<int>(vOscParameters::filterParamOffset) * OSCILLATOR_NUM
};

enum class vMasterParameters {
	paramTotalNum = static_cast<int>(vFiltParameters::masterParamOffset)
};

// set of parameters used in synth
struct GlobalParameterState{
	OscillatorParameter oscParam[OSCILLATOR_NUM];

	FilterParameter filterParam;

	ParamValue masterVolume;
	
	// set a parameter
	tresult setState(IBStream* stream);

	// get a parameter
	tresult getState(IBStream* stream);
};

// VoiceProcessor class
template<class SamplePrecision>
class Voice : public VoiceBase<vMasterParameters::paramTotalNum, SamplePrecision, 2, GlobalParameterState> {

	typedef VoiceBase<vMasterParameters::paramTotalNum, SamplePrecision, 2, GlobalParameterState> VBase;
public:
	Voice ();
	~Voice();

	// set the sampling rate
	void setSampleRate (ParamValue sampleRate) override;

	// noteon event
	void noteOn (int32 pitch, ParamValue velocity, float tuning, int32 sampleOffset, int32 nId) override;
	void noteOff (ParamValue velocity, int32 sampleOffset) override;

	bool process (SamplePrecision* outputBuffers[2], int32 numSamples);
	void reset () override;

	void setNoteExpressionValue (int32 index, ParamValue value) override;

protected:

};

}
}
}

