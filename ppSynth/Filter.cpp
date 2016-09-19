#include "Filter.h"

namespace Steinberg {
namespace Vst {
namespace PPSynth {

Filter::Filter(ParameterStorage* paramStorage, double sampleRate){
	this->paramStorage = paramStorage;
	this->sampleRate = sampleRate;
}

}
}
}
