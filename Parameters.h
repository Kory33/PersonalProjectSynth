#pragma once
#define DEFAULTPARAM_MASTER_VOLUME 1.
#include <pluginterfaces/vst/ivstcontextmenu.h>
#include <pluginterfaces/base/ibstream.h>

namespace Steinberg{
namespace Vst{
namespace PPSynth{

// paramters used in controlling oscillator
//
// ADSR envelope processor's parameter is included
// since an oscillator has an ADSR envelope processor (aggregation)
struct OscillatorParameter{
	// --- default values ---
	OscillatorParameter(){}

	// --- members ---
	// TODO implement oscillator's parameter

};

// paramters used in controlling filter
struct FilterParameter{
	// --- default values ---
	FilterParameter(){}

	// --- members ---
	// TODO implement filter's parameter
};

// set of parameters used in synth
class ParameterContainer{
public:
	ParameterContainer(int oscNum, int filterNum, double masterVolume = DEFAULTPARAM_MASTER_VOLUME) {
		// init oscillators' parameters
		this->oscParams = new OscillatorParameter[oscNum];
		for(int i = 0; i < oscNum; i++){
			this->oscParams[i] = OscillatorParameter();
		}

		// init filters' parameters
		this->filterParams = new FilterParameter[filterNum];
		for(int i = 0; i < filterNum; i++){
			this->filterParams[i] = FilterParameter();
		}

		this->masterVolume = masterVolume;
	}

	~ParameterContainer() {
		if(oscParams) delete[] oscParams;
		if(filterParams) delete[] filterParams;
	}

	OscillatorParameter* oscParams = nullptr;
	FilterParameter* filterParams = nullptr;

	ParamValue masterVolume;

	// set a parameter
	tresult setState(IBStream* stream);

	// get a parameter
	tresult getState(IBStream* stream);
};

}
}
}
