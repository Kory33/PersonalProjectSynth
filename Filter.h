#pragma once

#include "Parameters.h"

namespace Steinberg{
namespace Vst{
namespace PPSynth{

class Filter {
public:
	// TODO implement Filter class in detail
	Filter(ParameterContainer* paramStorage, double sampleRate);
private:
	ParameterContainer* paramStorage;
	double sampleRate;
};

}
}
}