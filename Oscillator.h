#pragma once
#include "Parameters.h"

namespace Steinberg{
namespace Vst{
namespace PPSynth{

class Oscillator {
public:
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
