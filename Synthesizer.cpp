#pragma once
#include "Synthesizer.h"

namespace Steinberg{
namespace Vst{
namespace PPSynth{

template<class Precision, int32 numChannels, int32 numOscillators, int32 numFilters, class ParameterStorage>
Synthesizer<Precision, numChannels, numOscillators, numFilters, ParameterStorage>::Synthesizer(float sampleRate, ParameterStorage* gParamStorage){
	for(int32 i = 0; i < numOscillators; i++){
		this->oscillators[i] = new Oscillator(gParamStorage, sampleRate);
	}
}

template<class Precision, int32 numChannels, int32 numOscillators, int32 numFilters, class ParameterStorage>
tresult Synthesizer<Precision, numChannels, numOscillators, numFilters, ParameterStorage>::process(ProcessData& data){

}

}
}
}