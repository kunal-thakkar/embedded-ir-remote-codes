/*
 * IRremote: IRsendNecStandardDemo
 *
 *  Demonstrates sending NEC IR codes in standard format with 16 bit Address  8bit Data
 * An IR LED must be connected to Arduino PWM pin 3 (IR_SEND_PIN).
 * To receive IR signals in compatible format, you must comment out the line
 * #define USE_NEC_STANDARD in IRremote.h.
 *
 *  This file is part of Arduino-IRremote https://github.com/z3t0/Arduino-IRremote.
 */

#include <IRremote.h>

IRsend IrSender;

// On the Zero and others we switch explicitly to SerialUSB
#if defined(ARDUINO_ARCH_SAMD)
#define Serial SerialUSB
#endif

unsigned long codes[] = {0xFF906F,
  0xFFA25D,0xFFE21D,0xFF22DD,0xFF02FD,0xFFC23D,0xFFE01F,0xFFA857,0xFF906F,0xFF6897,0xFF9867,0xFFB04F,0xFF30CF,0xFF18E7,0xFF7A85,
  0xFF10EF,0xFF38C7,0xFF5AA5,0xFF42BD,0xFF4AB5,0xFF52AD,0x958525,0xFFB847,0xFFF807,0xFFD827,0xFF8877,0xFFB24D,0xFF00FF,0xFF58A7,
  0xFFE817,0xFF50AF,0xFF48B7,0xFF32CD,0xFF7887,0xFF28D7,0xFF20DF,0xFF708F,0xFFF00F,0xFFA05F,0xFF609F,0xFFD02F,0xFFC837,0xFF08F7,
  0x115200,0xFFC03F,0x653639,0xFF629D,0xD1306A,0xFF40BF,0x303248,0x9716BE,0x3D9AE3,0x618202,0x8C2265,0x488F3C,0x449E79,0xFF1BC0,
  0x20FE4D,0x488977,0xFF0000,0xFFFFFF,0x566260,0x052AC6,0xD99B43,0x43474B,0xAE1D0F,0xEE0FED,0xBCB947,0x33BE4D,0xCCF985,0xCDE439,
  0x48E4FB,0xA3F7F8,0x688541,0x30614F,0x4BB640,0x4BB6C0,0x07D898,0x4BB475,0xA767B5,0x48755C,0x48C535,0xAAC5B6,0x1D6AD7,0x5B0F9E,
  0x54DB93,0xAEF6D6,0xE76A16,0x478693,0xADD100,0xADD200,0xC49BD5,0xB9985C,0xBDF456,0x7877F7,0xF72DE9,0x0B650E,0x9810B1,0xFFFA85,
  0xFF38CF,0x7F9A88,0x1025D6,0x54E2D3,0x363715,0xEBEE86,0x5C78D2,0x189675
};
#define len 106
#define RESEND_CODE 7
#define NEXT_CODE 5
int idx = 0;
unsigned long sCommand = 0x6F;

void setup() {
    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(RESEND_CODE, INPUT_PULLUP);
    pinMode(NEXT_CODE, INPUT_PULLUP);

    Serial.begin(115200);
#if defined(__AVR_ATmega32U4__) || defined(SERIAL_USB) || defined(SERIAL_PORT_USBVIRTUAL)
    delay(2000); // To be able to connect Serial monitor after reset and before first printout
#endif
    // Just to know which program is running on my Arduino
    Serial.println(F("START " __FILE__ " from " __DATE__));
    Serial.print(F("Ready to send IR signals at pin "));
    Serial.println(IR_SEND_PIN);
    sCommand = codes[idx] & 0xFFFFFF;
}

void loop() {
  if(digitalRead(RESEND_CODE) == LOW){
    IrSender.sendNEC(sCommand & 0xFFFFFF, 32);
    Serial.print(F("Send NEC standard: command=0x"));
    Serial.print(sCommand & 0xFFFFFF, HEX);
    Serial.print(" idx = ");
    Serial.println(idx);
    while(digitalRead(RESEND_CODE) == LOW);
  }
  if(digitalRead(NEXT_CODE) == LOW){
    if(idx < len-1)
      idx++;
    sCommand = codes[idx] & 0xFFFFFF;
    Serial.print(F("New command=0x"));
    Serial.println(sCommand, HEX);
    delay(1000);
    while(digitalRead(NEXT_CODE) == LOW);
  }
}
