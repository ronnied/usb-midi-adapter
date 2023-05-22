#include <MIDI.h>
#include <USB-MIDI.h>
#include <HardwareSerial.h>

using Transport = MIDI_NAMESPACE::SerialMIDI<HardwareSerial>;
Transport serialMIDI(Serial1);
MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, MIDIS)
USBMIDI_CREATE_DEFAULT_INSTANCE();

void handleNoteOn(byte channel, byte pitch, byte velocity) {
  MIDI.sendNoteOn(pitch, velocity, channel);
  //Serial.println('on');
}

void handleNoteOff(byte channel, byte pitch, byte velocity) {
  MIDI.sendNoteOff(pitch, velocity, channel);
  //Serial.println('off');
}

void handleControlChange(byte channel, byte command, byte value) {
  MIDI.sendControlChange(command, value, channel);
}

void setup(){
  pinMode(2, INPUT);
  MIDIS.setHandleNoteOn(handleNoteOn);
  MIDIS.setHandleNoteOff(handleNoteOff);
  MIDIS.setHandleControlChange(handleControlChange);
  MIDIS.begin(MIDI_CHANNEL_OMNI);
  MIDI.begin();
}

void loop(){
  MIDIS.read();
}