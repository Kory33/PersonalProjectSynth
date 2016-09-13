#pragma once
#include "public.sdk/source/vst/vstaudioeffect.h"
#include "VoiceProcessor.h"

namespace Steinberg{
namespace Vst{

namespace PPSynth{

class Processor : public AudioEffect{
public:
	tresult PLUGIN_API initialize(FUnknown*) override;

	tresult PLUGIN_API setState(IBStream*) override;
	tresult PLUGIN_API getState(IBStream*) override;

	tresult PLUGIN_API setBusArrangements(SpeakerArrangement*, int32, SpeakerArrangement*, int32) override;

	tresult PLUGIN_API canProcessSampleSize(int32) override;

	tresult PLUGIN_API setActive(TBool) override;
	tresult PLUGIN_API process(ProcessData&) override;

	static FUnknown* createInstance(void*){ return static_cast <IAudioProcessor*>(new Processor()); }

	static const FUID cid;

protected:
	VoiceProcessor* voiceProcessor;  // TODO implement voice processor
	GlobalParameterState paramState; // TODO implement parameters
};

// set FUID of Processor
const FUID Processor::cid(0xFCE05A10, 0x1C124D9B, 0xB6516F4B, 0x8F4B804B);

}
}
}

