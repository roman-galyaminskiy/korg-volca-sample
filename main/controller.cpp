#include "controller.hpp"

Controller::Controller(Mediator *m, USB *u): USBH_MIDI(u), mediator(m) {}

void Controller::start() {
  // SERIAL_MONITOR.println("Checking USB...");
  if (pUsb->Init() == -1) {
    while (1); //halt
  }//if (Usb.Init() == -1...
  delay( 200 );

  // SERIAL_MONITOR.println("SUCCESS");
}

void Controller::enableExtendedMode() {
  uint8_t msg[3] = {CHANNEL1_NOTE_ON, 12, 0};

  // TODO: Status check
  // uint8_t msg[3] = {CHANNEL1_NOTE_ON, 11, 0};
  // Midi.SendData(msg, 1);
  // delay(1);
  // MIDI_poll();

//  pUsb->Task();
//  if (pUsb->getUsbTaskState()==USB_STATE_RUNNING) {
//    delay(1);
//  }

  do {
    pUsb->Task();
    if ( pUsb->getUsbTaskState() == USB_STATE_RUNNING ) {
      // Off
      pUsb->Task();
      SendData(msg, 1);
      delay(1);
    
      // On
      msg[2] = 127;
      pUsb->Task();
      SendData(msg, 1);
      delay(1);
    
      extended_mode_enabled = 1;
    }
  } while (extended_mode_enabled == 0);

  // SERIAL_MONITOR.println("Extended mode enabled");
}

void Controller::changed(uint8_t *event, uint8_t size) {
  mediator->notify(this, event, size);
}

void Controller::listen() {
  pUsb->Task();

  uint8_t outBuf[ 3 ];
  uint8_t size;
  uint8_t voice_number = -1;
  do {
    if ( (size = RecvData(outBuf)) > 0 ) {
      // SERIAL_MONITOR.print(outBuf[0], DEC);
      // SERIAL_MONITOR.print(" ");
      // SERIAL_MONITOR.print(outBuf[1], DEC);
      // SERIAL_MONITOR.print(" ");
      // SERIAL_MONITOR.print(outBuf[2], DEC);
      // SERIAL_MONITOR.println();

      if (outBuf[0] == CHANNEL1_NOTE_ON) {
        if (outBuf[1] >= PAD1 && outBuf[1] <= PAD16) {
          change_pad_color(outBuf[1], RED);
        }
      }
      else if (outBuf[0] == CHANNEL1_NOTE_OFF) {
        if (outBuf[1] >= PAD1 && outBuf[1] <= PAD16) {
          change_pad_color(outBuf[1], BLACK);
        }
      }
      changed(outBuf, size);
    }    

  } while (size > 0);
}

void Controller::change_pad_color(int8_t pad_index, uint8_t color_code) {
  uint8_t msg[3] = {CHANNEL1_NOTE_ON, pad_notes[pad_index], color_code};

  pUsb->Task();
  SendData(msg, 1);
  delay(1);
}
