#pragma once

#define MIDI_KEYBOARD_KEYNUM 128

namespace Steinberg{
namespace Vst{
namespace PPSynth{

class VirtualKeyboard{
public:
	VirtualKeyboard(){};
	void flushEventQueue();
private:
	bool keyPressedState[MIDI_KEYBOARD_KEYNUM];

};

}
}
}