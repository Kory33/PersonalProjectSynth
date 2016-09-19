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
	Filter filters[numFilters];
	VirtualKeyboard keyboards[MIDI_CHANNEL_NUM];

	void initOscillators(float sampleRate, ParameterStorage* paramStorage);
	void initFilters(float sampleRate, ParameterStorage* paramStorage);
	void processEvent(Event e);
};

}
}
}

