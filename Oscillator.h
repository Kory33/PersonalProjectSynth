#pragma once
#include "Parameters.h"

namespace Steinberg{
namespace Vst{
namespace PPSynth{

class Oscillator {
public:
	// TODO implement Oscillator class in detail
	Oscillator(ParameterContainer* paramStorage, double sampleRate);

private:
	ParameterContainer* paramStorage;
	double sampleRate;
};

}
}
}
