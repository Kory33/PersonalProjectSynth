#pragma once
#include "public.sdk/source/vst/vstaudioeffect.h"
#include "Synthesizer.h"
#include "Parameters.h"

#define OSCILLATOR_NUM 8
#define FILTER_NUM 2
#define CHANNEL_NUM 2

namespace Steinberg{
namespace Vst{

namespace PPSynth{

class Processor : public AudioEffect{
public:
	Processor();
	~Processor();
	tresult PLUGIN_API initialize(FUnknown* context) override;

	tresult PLUGIN_API setState(IBStream* state) override;
	tresult PLUGIN_API getState(IBStream* state) override;

	tresult PLUGIN_API setBusArrangements(SpeakerArrangement* inputs, int32 inputNum, SpeakerArrangement* outputs, int32 outputNum) override;

	tresult PLUGIN_API canProcessSampleSize(int32 symbolicSampleSize) override;

	tresult PLUGIN_API setActive(TBool state) override;
	tresult PLUGIN_API process(ProcessData& data) override;

	static FUnknown* createInstance(void*) {
		return static_cast<IAudioProcessor*>(new Processor());
	}

	static const FUID cid;

protected:
	SynthesizerBase* synthesizer;
	ParameterContainer* paramState;

private:
	tresult activate();
	tresult deactivate();
	void modifyParameter(const ProcessData&);
};

// set FUID of Processor
const FUID Processor::cid(0xFCE05A10, 0x1C124D9B, 0xB6516F4B, 0x8F4B804B);

}
}
}

