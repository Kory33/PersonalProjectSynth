#pragma once

#include "pluginterfaces/vst/ivstaudioprocessor.h"
#include "pluginterfaces/vst/ivstevents.h"
#include "pluginterfaces/base/futils.h"

#include "Oscillator.h"
#include "Filter.h"
#include "VirtualKeyboard.h"

#define MIDI_CHANNEL_NUM 16

namespace Steinberg {
namespace Vst {
namespace PPSynth{

class SynthesizerBase{
public:
	SynthesizerBase(){};
	virtual ~SynthesizerBase(){};

	virtual tresult process(ProcessData& data) = 0;
};

// main process class
template<class Precision, int32 numChannels, int32 numOscillators, int32 numFilters, class ParameterStorage>
class Synthesizer : public SynthesizerBase{
public:
	explicit Synthesizer(float sampleRate, ParameterStorage* paramStorage);
	~Synthesizer();

	tresult process(ProcessData& data) override;
private:
	Oscillator* oscillators[numOscillators];
	Filter* filters[numFilters];
	VirtualKeyboard keyboards[MIDI_CHANNEL_NUM];
	ParameterStorage* paramStorage;

	void initOscillators(float sampleRate, ParameterStorage* paramStorage);
	void initFilters(float sampleRate, ParameterStorage* paramStorage);
	void processEvent(Event e);
};


template<class Precision, int32 numChannels, int32 numOscillators, int32 numFilters, class ParameterStorage>
Synthesizer<Precision, numChannels, numOscillators, numFilters, ParameterStorage>::Synthesizer(float sampleRate, ParameterStorage* paramStorage){
	this->initOscillators(sampleRate, paramStorage);
	this->initFilters(sampleRate, paramStorage);
}

template <class Precision, int32 numChannels, int32 numOscillators, int32 numFilters, class ParameterStorage>
Synthesizer<Precision, numChannels, numOscillators, numFilters, ParameterStorage>::~Synthesizer(){
	// finalize oscillators
	for(int32 i = 0; i < numOscillators; i++){
		if(this->oscillators[i]){
			delete this->oscillators[i];
		}
	}

	// finalize filters
	for(int32 i = 0; i < numFilters; i++){
		if(this->filters[i]){
			delete this->filters[i];
		}
	}
}


template<class Precision, int32 numChannels, int32 numOscillators, int32 numFilters, class ParameterStorage>
tresult Synthesizer<Precision, numChannels, numOscillators, numFilters, ParameterStorage>::process(ProcessData& data){
	const int32 numSamples = data.numSamples;
	int32 samplesProcessed = 0;

	IEventList* inputEvents = data.inputEvents;
	Event event = {0};
	Event* eventPtr = nullptr;
	int32 eventIndex = 0;
	int32 numEvents = inputEvents ? inputEvents->getEventCount() : 0;

	if(numEvents){
		inputEvents->getEvent(0, event);
		eventPtr = &event;
	}

	// initialize audio output buffers
	for(int i = 0; i < numChannels; i++){
		memset(data.outputs[0].channelBuffers32[i], 0, data.numSamples * sizeof(Precision));
	}

	return kResultTrue;
}

template <class Precision, int32 numChannels, int32 numOscillators, int32 numFilters, class ParameterStorage>
void Synthesizer<Precision, numChannels, numOscillators, numFilters, ParameterStorage>::initOscillators(float sampleRate, ParameterStorage* paramStorage){
	// initialize oscillators
	for(int32 i = 0; i < numOscillators; i++){
		this->oscillators[i] = new Oscillator(paramStorage, sampleRate);
	}
}

template <class Precision, int32 numChannels, int32 numOscillators, int32 numFilters, class ParameterStorage>
void Synthesizer<Precision, numChannels, numOscillators, numFilters, ParameterStorage>::initFilters(float sampleRate, ParameterStorage* paramStorage){
	// initialize filters
	for(int32 i = 0; i < numFilters; i++){
		this->filters[i] = new Filter(paramStorage, sampleRate);
	}
}

template <class Precision, int32 numChannels, int32 numOscillators, int32 numFilters, class ParameterStorage>
void Synthesizer<Precision, numChannels, numOscillators, numFilters, ParameterStorage>::processEvent(Event e){

}

}
}
}

