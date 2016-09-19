#include "Filter.h"

namespace Steinberg {
namespace Vst {
namespace PPSynth {

Filter::Filter(ParameterContainer* paramStorage, double sampleRate){
	this->paramStorage = paramStorage;
	this->sampleRate = sampleRate;
}

}
}
}
