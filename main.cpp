#include <iostream>
#include <libremidi/libremidi.hpp>

class MidiPlayer {
    private:
        libremidi::midi_out midi_out;

    public:
        bool initialize(){
            try {
                midi_out.open_virtual_port("My Virtual Port");
                std::cout << "Virtual MIDI port 'My Virtual Port' created!" << std::endl;
                return true;
            } catch (const std::exception& e) {
                std::cout << "MIDI Error: " << e.what() << std::endl;
                return false;
            }
        }

        void arpeggio() {
            int notes[] = {60, 64, 67, 72};
            int current_note = 0;

            while (true) {
                // note on
                auto err = midi_out.send_message(0x90, notes[current_note], 100);
                if (err == stdx::error{}) {
                    std::cout << "Error sending note on message" << std::endl;
                }

                std::this_thread::sleep_for(std::chrono::milliseconds(400));

                // note off
                err = midi_out.send_message(0x80, notes[current_note], 0);
                if (err == stdx::error{}) {
                    std::cout << "Error sending note off message" << std::endl;
                }

                std::this_thread::sleep_for(std::chrono::milliseconds(100));
                current_note = (current_note + 1) % 4;
            }
        }
};

int main() {
    MidiPlayer midi;
    
    if (midi.initialize()) {
        std::cout << "Check Ableton now - port should be visible!" << std::endl;
    }

    std::cout << "Starting midi playback now..." << std::endl;
    std::cout << "press CTRL+C to stop..." << std::endl;
    midi.arpeggio();
    
    return 0;
}