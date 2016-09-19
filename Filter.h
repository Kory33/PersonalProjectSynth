#pragma once

#include "Parameters.h"

namespace Steinberg{
namespace Vst{
namespace PPSynth{

class Filter {
public:
	// TODO implement Filter class in detail
	Filter(ParameterStorage* paramStorage, double sampleRate);
private:
	ParameterStorage* paramStorage;
	double sampleRate;
};

}
}
}