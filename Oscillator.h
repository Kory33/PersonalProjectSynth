#pragma once
#include "Parameters.h"

namespace Steinberg{
namespace Vst{
namespace PPSynth{

class Oscillator {
public:
	// TODO implement Oscillator class in detail
	Oscillator(ParameterContainer paramStorage, double sampleRate);

	// returns default parameters of oscillator
	static OscillatorParameter getDefaultParamter() {
		return;
	}

	void reset();

private:
	ParameterContainer* paramState;
};

}
}
}
