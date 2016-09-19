#pragma once
#include "Parameters.h"

namespace Steinberg{
namespace Vst{
namespace PPSynth{

class Oscillator {
public:
	// TODO implement Oscillator class in detail
	Oscillator(ParameterStorage* paramStorage, double sampleRate);

private:
	ParameterStorage* paramStorage;
	double sampleRate;
};

}
}
}
