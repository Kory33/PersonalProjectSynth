#pragma once
#include "Parameters.h"

namespace Steinberg{
namespace Vst{
namespace PPSynth{

template<class Precision>
class Oscillator {
public:
	// TODO implement Oscillator class in detail
	Oscillator(ParameterStorage* paramStorage, double sampleRate);
	void processBuffer(Precision (*outputBuffer)[], int32 numChannels, int bufferSize);

private:
	ParameterStorage* paramStorage;
	double sampleRate;
};

template<class Precision>
Oscillator<Precision>::Oscillator(ParameterStorage* paramStorage, double sampleRate) {
	this->paramStorage = paramStorage;
	this->sampleRate = sampleRate;
}

template<class Precision>
void Oscillator<Precision>::processBuffer(Precision(*outputBuffer)[], int32 numChannels, int bufferSize){
	//TODO implement output to buffer
}


}
}
}

