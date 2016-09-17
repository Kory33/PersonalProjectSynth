#include "version.h"
#include "Processor.h"

#include "public.sdk/source/main/pluginfactoryvst3.h"

#define PP_SYNTH_VENDOR "Kory"
#define PP_SYNTH_URL    "kory.f5.si"
#define PP_SYNTH_EMAIL  "mailto:konryoitdv@gmail.com"

#define PP_SYNTH_NAME "PP Synth"
#define PP_SYNTH_SUBCATEGORIES Vst::PlugType::kInstrumentSynth

#define MYVST_SUBCATEGORIES Vst::PlugType::kInstrumentSynth

BEGIN_FACTORY_DEF(PP_SYNTH_VENDOR, PP_SYNTH_URL, PP_SYNTH_EMAIL)
	// create class
	DEF_CLASS2(INLINE_UID_FROM_FUID(Steinberg::Vst::PPSynth::Processor::cid),
		PClassInfo::kManyInstances,
		kVstAudioEffectClass,
		PP_SYNTH_NAME,
		Vst::kDistributable,
		PP_SYNTH_SUBCATEGORIES,
		VERSION_STR,
		kVstVersionString,
		Steinberg::Vst::PPSynth::Processor::createInstance )

END_FACTORY


bool InitModule(){ return true; };
bool DeinitModule(){ return true; };

