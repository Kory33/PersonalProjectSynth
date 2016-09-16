#include "pluginterfaces/vst/ivstparameterchanges.h"
#include "Processor.h"

/**
 * @author Kory33
 *
 * Program flow is almost identicle to
 * public.sdk/samples/vst/note_expression_synth/source/note_expression_synth_processor.cpp
 * 
 * some parts of the code is modified for readability and separation of task
 */

namespace Steinberg {
namespace Vst {
	
namespace PPSynth {
	Processor::Processor() : synthesizer(nullptr){
//		setControllerClass(); // TODO add controller class to processor

		this->paramState = new ParameterContainer(OSCILLATOR_NUM, FILTER_NUM);
	}

	tresult Processor::initialize(FUnknown* context) {
		tresult result = AudioEffect::initialize(context);

		// add I/O
		if(result == kResultTrue) {
			addAudioOutput(STR16("Audio Output"), SpeakerArr::kStereo);
			addAudioInput(STR16("Audio Input"), 1);
		}

		return result;
	}

	tresult Processor::setState(IBStream* state) {
		return paramState->setState(state);
	}

	tresult Processor::getState(IBStream* state) {
		return paramState->getState(state);
	}

	tresult Processor::setBusArrangements(SpeakerArrangement* inputs, int32 inputNum, SpeakerArrangement* outputs, int32 outputNum){
		// 0 input and 1 stereo output
		if(inputNum == 0 && outputNum == 1 && outputs[0] == SpeakerArr::kStereo) {
			return AudioEffect::setBusArrangements(inputs, inputNum, outputs, outputNum);
		}

		return kResultFalse;
	}

	tresult Processor::canProcessSampleSize(int32 symbolicSampleSize){
		if(symbolicSampleSize == kSample32 || symbolicSampleSize == kSample64) {
			return kResultTrue;
		}
		return kResultFalse;
	}

	tresult Processor::setActive(TBool state) {
		if(state) {
			return this->activate();
		} else {
			return this->deactivate();
		}
	}

	tresult Processor::process(ProcessData& data) {
		if(data.inputParameterChanges) {
			this->modifyParameter(data);
		}

		tresult result = (data.numOutputs < 1) ? result = kResultTrue : this->synthesizer->process(data);

		if(result == kResultTrue) {
//			if(synthesizer->getActiveVoices() == 0 && data.numOutputs > 0) {
//				// silence channels
//				data.outputs[0].silenceFlags = 0x11;
//			}
		}

		return result;
	}

	tresult Processor::activate() {
		if(this->synthesizer == nullptr){
			if(processSetup.symbolicSampleSize == kSample32){
				// single precision
				this->synthesizer = new Synthesizer<double, CHANNEL_NUM, OSCILLATOR_NUM, FILTER_NUM, ParameterContainer>(float(processSetup.sampleRate), paramState);

			} else if(processSetup.symbolicSampleSize == kSample32){
				// double precision
				this->synthesizer = new Synthesizer<double, CHANNEL_NUM, OSCILLATOR_NUM, FILTER_NUM, ParameterContainer>(float(processSetup.sampleRate), paramState);

			} else {
				return kInvalidArgument;
			}
		}

		return AudioEffect::setActive(true);
	}

	tresult Processor::deactivate() {
		// delete voice processor
		if(this->synthesizer != nullptr) {
			delete this->synthesizer;
			synthesizer = nullptr;
		}

		return AudioEffect::setActive(false);
	}

	void Processor::modifyParameter(const ProcessData&) {
		//TODO implement parameter change
	}
}

}
}
