#pragma once

#include "Synthesizer.h"

namespace Steinberg{
namespace Vst{
namespace PPSynth{

class Filter {
public:
	// TODO implement Filter class in detail
	Filter(ParameterContainer paramStorage, double sampleRate);

	static FilterParameter getDefaultParameter() {
		return;
	}
};

}
}
}