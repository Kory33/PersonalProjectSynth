#pragma once
#include "VoiceProcessor.h"

namespace Steinberg{
namespace Vst{
namespace PPSynth{

template <class SamplePrecision>
Voice<SamplePrecision>::Voice(){
}

template <class SamplePrecision>
Voice<SamplePrecision>::~Voice(){
}
	
template <class SamplePrecision>
bool Voice<SamplePrecision>::process(SamplePrecision* outputBuffers[2], int32 numSamples) {
	return true;
}

template <class SamplePrecision>
void Voice<SamplePrecision>::setSampleRate(ParamValue sampleRate) {
	
}

template <class SamplePrecision>
void Voice<SamplePrecision>::noteOn(int32 pitch, ParamValue velocity, float tuning, int32 sampleOffset, int32 nId) {
	
}

template <class SamplePrecision>
void Voice<SamplePrecision>::noteOff(ParamValue velocity, int32 sampleOffset) {
	
}

template <class SamplePrecision>
void Voice<SamplePrecision>::reset(){
}

template <class SamplePrecision>
void Voice<SamplePrecision>::setNoteExpressionValue(int32 index, ParamValue value){
}


}
}
}