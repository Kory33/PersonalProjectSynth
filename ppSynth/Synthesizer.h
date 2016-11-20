#pragma once

#include "pluginterfaces/vst/ivstaudioprocessor.h"
#include "pluginterfaces/vst/ivstevents.h"
#include "pluginterfaces/base/futils.h"

#include "Oscillator.h"
#include "Filter.h"
#include <algorithm>

#define PROCESS_BLOCK_SIZE 32

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
	Oscillator<Precision>* oscillators[numOscillators];
	Filter* filters[numFilters];
	ParameterStorage* paramStorage;

	void initOscillators(float sampleRate, ParameterStorage* paramStorage);
	void initFilters(float sampleRate, ParameterStorage* paramStorage);
	void pushEvent(Event e, int32 processBlockOffset);
	
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

/**
 * Receives events from the host program and writes the signal output
 * Chunk of samples(data.numSamples) is devided into smaller "process-block",
 * and they will be processed sequentially.
 */

template<class Precision, int32 numChannels, int32 numOscillators, int32 numFilters, class ParameterStorage>
tresult Synthesizer<Precision, numChannels, numOscillators, numFilters, ParameterStorage>::process(ProcessData& data){
	const int32 numSamples = data.numSamples;

	IEventList* inputEvents = data.inputEvents;

	Event event = {0};
	int32 eventIndex = 0;

	int32 numEvents = inputEvents ? inputEvents->getEventCount() : 0;
	if(numEvents == 0) return kResultTrue;

	// get first event
	inputEvents->getEvent(0, event);

	// prepare buffer array to let oscillators store the output
	Precision oscillatorOutputBuffer[numOscillators][numChannels][PROCESS_BLOCK_SIZE];

	int32 remainingSamples = numSamples;
	int32 processBlockOffset = 0;

	while(remainingSamples > 0) {
		int32 samplesToBeProcessed = std::min<int32>(PROCESS_BLOCK_SIZE, remainingSamples);

		while(eventIndex < numEvents) {
			// next event is outside current process block
			if(event.sampleOffset - processBlockOffset > samplesToBeProcessed) break;

			// register the event
			this->pushEvent(event, processBlockOffset);

			// get next event
			eventIndex++;
			if(inputEvents->getEvent(eventIndex, event) != kResultTrue) break;
		}

		// process the process-block and store signal output to the buffers
		for(int32 i = 0; i < numOscillators;) {
			this->oscillators[i]->processBuffer(oscillatorOutputBuffer[i], numChannels, PROCESS_BLOCK_SIZE);
		}

		//TODO add process to the output from synthesizer

		remainingSamples -= samplesToBeProcessed;
		processBlockOffset += samplesToBeProcessed;
	}

	return kResultTrue;
}

template <class Precision, int32 numChannels, int32 numOscillators, int32 numFilters, class ParameterStorage>
void Synthesizer<Precision, numChannels, numOscillators, numFilters, ParameterStorage>::initOscillators(float sampleRate, ParameterStorage* paramStorage){
	// initialize oscillators
	for(int32 i = 0; i < numOscillators; i++){
		this->oscillators[i] = new Oscillator<Precision>(paramStorage, sampleRate);
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
void Synthesizer<Precision, numChannels, numOscillators, numFilters, ParameterStorage>::pushEvent(Event e, int32 processBlockOffset){
	// TODO implementation
}

}
}
}

