#include <Arduino.h>
#include "MyLedControl.h"
#include "binary.h"
#include <IRremote.hpp>
#include "PinDefinitionsAndMore.h"

#define DIN 23
#define CLK 18
#define CS 5
LedControl lc=LedControl(DIN,CLK,CS,1);

// delay time between faces
unsigned long delaytime=1000;

// letters
const byte a[8]={B00111100,B01000010,B01000010,B01111110,B01000010,B01000010,B01000010,B01000010};
const byte b[8]={B01111100,B01000010,B01000010,B01111100,B01000010,B01000010,B01000010,B01111100};
const byte c[8]={B00111110,B01000000,B01000000,B01000000,B01000000,B01000000,B01000000,B00111110};
const byte d[8]={B01111100,B01000010,B01000010,B01000010,B01000010,B01000010,B01000010,B01111100};
const byte e[8]={B01111110,B01000000,B01000000,B01111000,B01000000,B01000000,B01000000,B01111110};
const byte f[8]={B01111110,B01000000,B01000000,B01111000,B01000000,B01000000,B01000000,B01000000};
const byte g[8]={B00111100,B01000010,B01000010,B01000000,B01001110,B01000010,B01000010,B00111100};
const byte h[8]={B01000010,B01000010,B01000010,B01111110,B01000010,B01000010,B01000010,B01000010};
const byte i[8]={B01111100,B00010000,B00010000,B00010000,B00010000,B00010000,B00010000,B01111100};
const byte j[8]={B00000010,B00000010,B00000010,B00000010,B00000010,B00000010,B01000010,B00111100};
const byte k[8]={B01000100,B01001000,B01010000,B01100000,B01010000,B01001000,B01000100,B01000010};
const byte l[8]={B01000000,B01000000,B01000000,B01000000,B01000000,B01000000,B01000000,B01111110};
const byte m[8]={B01000010,B01100110,B01011010,B01000010,B01000010,B01000010,B01000010,B01000010};
const byte n[8]={B01000010,B01100010,B01010010,B01001010,B01000110,B01000010,B01000010,B01000010};
const byte o[8]={B00111100,B01000010,B01000010,B01000010,B01000010,B01000010,B01000010,B00111100};
const byte p[8]={B00111100,B01000010,B01000010,B01111100,B01000000,B01000000,B01000000,B01000000};
const byte q[8]={B00111100,B01000010,B01000010,B01000010,B01000010,B01001010,B01000100,B00111011};
const byte r[8]={B00111100,B01000010,B01000010,B01111100,B01010000,B01001000,B01000100,B01000100};
const byte s[8]={B00111100,B01000010,B01000000,B00111100,B00000010,B00000010,B01000010,B00111100};
const byte t[8]={B01111100,B00010000,B00010000,B00010000,B00010000,B00010000,B00010000,B00010000};
const byte u[8]={B01000010,B01000010,B01000010,B01000010,B01000010,B01000010,B01000010,B00111100};
const byte v[8]={B01000010,B01000010,B01000010,B01000010,B01000010,B01000010,B00100100,B00011000};
const byte w[8]={B01000010,B01000010,B01000010,B01000010,B01000010,B01011010,B01100110,B01000010};
const byte x[8]={B01000010,B01000010,B00100100,B00011000,B00011000,B00100100,B01000010,B01000010};
const byte y[8]={B01000100,B01000100,B00101000,B00010000,B00010000,B00010000,B00010000,B00010000};
const byte z[8]={B01111110,B00000100,B00001000,B00010000,B00100000,B01000000,B01000000,B01111110};
const byte* alphabet[26] = {a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z};

void display_letter(const byte* letter)
{
  lc.setRow(0,0,letter[0]);
  lc.setRow(0,1,letter[1]);
  lc.setRow(0,2,letter[2]);
  lc.setRow(0,3,letter[3]);
  lc.setRow(0,4,letter[4]);
  lc.setRow(0,5,letter[5]);
  lc.setRow(0,6,letter[6]);
  lc.setRow(0,7,letter[7]);
}
//
//void drawFaces(){
//    for (int i = 0; i < 26; i++) {
//        display_letter(alphabet[i]);
//        delay(delaytime);
//    }
//}

void setup() {
  Serial.begin(115200);
  lc.shutdown(0,false);
  lc.setIntensity(0,8);
  lc.clearDisplay(0);

  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);
  Serial.print(F("Ready to receive IR signals of protocols: "));
  printActiveIRProtocols(&Serial);
  Serial.println(F("at pin " STR(IR_RECEIVE_PIN)));
  
}


void loop(){
  if (IrReceiver.decode()) {
    if (IrReceiver.decodedIRData.protocol == UNKNOWN)
    {
        Serial.println(F("Received noise or an unknown (or not yet enabled) protocol"));
        // We have an unknown protocol here, print extended info
        IrReceiver.printIRResultRawFormatted(&Serial, true);
        IrReceiver.resume(); // Do it here, to preserve raw data for printing with printIRResultRawFormatted()
    } else {
        IrReceiver.resume(); // Early enable receiving of the next IR frame
        IrReceiver.printIRResultShort(&Serial);
        IrReceiver.printIRSendUsage(&Serial);
    }
    Serial.println();

    /*
     * Finally, check the received data and perform actions according to the received command
     */
    if (IrReceiver.decodedIRData.command == 0x0)
    {
      display_letter(a);
    } else if (IrReceiver.decodedIRData.command == 0x1)
    {
        display_letter(b);
    }
  }
}
