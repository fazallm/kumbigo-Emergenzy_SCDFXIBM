
// Include Libraries
#include "Arduino.h"
#include "pulse-sensor-arduino.h"
#include "Wire.h"
#include "SPI.h"
#include "Adafruit_SSD1306.h"
#include "Adafruit_GFX.h"
#include "Button.h"
#include "SpeakerStereo3W.h"


// Pin Definitions
#define HEARTPULSE_PIN_SIG	A0
#define MQ135_5V_PIN_AOUT	A1
#define MQ2_5V_PIN_AOUT	A2
#define OLED128X64_PIN_RST	5
#define OLED128X64_PIN_DC	4
#define OLED128X64_PIN_CS	2
#define PUSHBUTTON_1_PIN_2	7
#define PUSHBUTTON_2_PIN_2	8
#define LEDARCADEBUTTON_PIN_BUTTON_SIG	6
#define LEDARCADEBUTTON_PIN_LED_VCC	3
#define STEREOSPEAKER_1_PIN_POS	9
#define STEREOSPEAKER_2_PIN_POS	10



// Global variables and defines
unsigned int StereoSpeaker_1HoorayLength          = 6;                                                      // amount of notes in melody
unsigned int StereoSpeaker_1HoorayMelody[]        = {NOTE_C4, NOTE_E4, NOTE_G4, NOTE_C5, NOTE_G4, NOTE_C5}; // list of notes. List length must match HoorayLength!
unsigned int StereoSpeaker_1HoorayNoteDurations[] = {8      , 8      , 8      , 4      , 8      , 4      }; // note durations; 4 = quarter note, 8 = eighth note, etc. List length must match HoorayLength!
unsigned int StereoSpeaker_2HoorayLength          = 6;                                                      // amount of notes in melody
unsigned int StereoSpeaker_2HoorayMelody[]        = {NOTE_C4, NOTE_E4, NOTE_G4, NOTE_C5, NOTE_G4, NOTE_C5}; // list of notes. List length must match HoorayLength!
unsigned int StereoSpeaker_2HoorayNoteDurations[] = {8      , 8      , 8      , 4      , 8      , 4      }; // note durations; 4 = quarter note, 8 = eighth note, etc. List length must match HoorayLength!
// object initialization
PulseSensor heartpulse;
#define SSD1306_LCDHEIGHT 64
Adafruit_SSD1306 oLed128x64(OLED128X64_PIN_DC, OLED128X64_PIN_RST, OLED128X64_PIN_CS);
Button pushButton_1(PUSHBUTTON_1_PIN_2);
Button pushButton_2(PUSHBUTTON_2_PIN_2);
SpeakerStereo3W StereoSpeaker_1(STEREOSPEAKER_1_PIN_POS);
SpeakerStereo3W StereoSpeaker_2(STEREOSPEAKER_2_PIN_POS);


// define vars for testing menu
const int timeout = 10000;       //define timeout of 10 sec
char menuOption = 0;
long time0;

// Setup the essentials for your circuit to work. It runs first every time your circuit is powered with electricity.
void setup() 
{
    // Setup Serial which is useful for debugging
    // Use the Serial Monitor to view printed messages
    Serial.begin(9600);
    while (!Serial) ; // wait for serial port to connect. Needed for native USB
    Serial.println("start");
    
    heartpulse.begin(HEARTPULSE_PIN_SIG);
    oLed128x64.begin(SSD1306_SWITCHCAPVCC);  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
    oLed128x64.clearDisplay(); // Clear the buffer.
    oLed128x64.display();
    pushButton_1.init();
    pushButton_2.init();
    menuOption = menu();
    
}

// Main logic of your circuit. It defines the interaction between the components you selected. After setup, it runs over and over again, in an eternal loop.
void loop() 
{
    
    
    if(menuOption == '1') {
    // Heart Rate Pulse Sensor - Test Code
    //Measure Heart Rate
    int heartpulseBPM = heartpulse.BPM;
    Serial.println(heartpulseBPM);
    if (heartpulse.QS == true) {
    Serial.println("PULSE");
    heartpulse.QS = false;
    }
    }
    else if(menuOption == '2')
    {
    // Disclaimer: The Hazardous Gas  Sensor - MQ-135 is in testing and/or doesn't have code, therefore it may be buggy. Please be kind and report any bugs you may find.
    }
    else if(menuOption == '3')
    {
    // Disclaimer: The Methane, Butane, LPG and Smoke Gas Sensor - MQ-2 is in testing and/or doesn't have code, therefore it may be buggy. Please be kind and report any bugs you may find.
    }
    else if(menuOption == '4') {
    // Monochrome 1.3 inch 128x64 OLED graphic display - Test Code
    oLed128x64.setTextSize(1);
    oLed128x64.setTextColor(WHITE);
    oLed128x64.setCursor(0, 10);
    oLed128x64.clearDisplay();
    oLed128x64.println("Circuito.io Rocks!");
    oLed128x64.display();
    delay(1);
    oLed128x64.startscrollright(0x00, 0x0F);
    delay(2000);
    oLed128x64.stopscroll();
    delay(1000);
    oLed128x64.startscrollleft(0x00, 0x0F);
    delay(2000);
    oLed128x64.stopscroll();
    }
    else if(menuOption == '5') {
    // Mini Pushbutton Switch #1 - Test Code
    //Read pushbutton state. 
    //if button is pressed function will return HIGH (1). if not function will return LOW (0). 
    //for debounce funtionality try also pushButton_1.onPress(), .onRelease() and .onChange().
    //if debounce is not working properly try changing 'debounceDelay' variable in Button.h
    bool pushButton_1Val = pushButton_1.read();
    Serial.print(F("Val: ")); Serial.println(pushButton_1Val);

    }
    else if(menuOption == '6') {
    // Mini Pushbutton Switch #2 - Test Code
    //Read pushbutton state. 
    //if button is pressed function will return HIGH (1). if not function will return LOW (0). 
    //for debounce funtionality try also pushButton_2.onPress(), .onRelease() and .onChange().
    //if debounce is not working properly try changing 'debounceDelay' variable in Button.h
    bool pushButton_2Val = pushButton_2.read();
    Serial.print(F("Val: ")); Serial.println(pushButton_2Val);

    }
    else if(menuOption == '7')
    {
    // Disclaimer: The Arcade Button with LED - 30mm Translucent Red is in testing and/or doesn't have code, therefore it may be buggy. Please be kind and report any bugs you may find.
    }
    else if(menuOption == '8') {
    // 3W Stereo Speaker #1 - Test Code
    // The Speaker will play the Hooray tune
    StereoSpeaker_1.playMelody(StereoSpeaker_1HoorayLength, StereoSpeaker_1HoorayMelody, StereoSpeaker_1HoorayNoteDurations); 
    delay(500);   
    }
    else if(menuOption == '9') {
    // 3W Stereo Speaker #2 - Test Code
    // The Speaker will play the Hooray tune
    StereoSpeaker_2.playMelody(StereoSpeaker_2HoorayLength, StereoSpeaker_2HoorayMelody, StereoSpeaker_2HoorayNoteDurations); 
    delay(500);   
    }
    
    if (millis() - time0 > timeout)
    {
        menuOption = menu();
    }
    
}



// Menu function for selecting the components to be tested
// Follow serial monitor for instrcutions
char menu()
{

    Serial.println(F("\nWhich component would you like to test?"));
    Serial.println(F("(1) Heart Rate Pulse Sensor"));
    Serial.println(F("(2) Hazardous Gas  Sensor - MQ-135"));
    Serial.println(F("(3) Methane, Butane, LPG and Smoke Gas Sensor - MQ-2"));
    Serial.println(F("(4) Monochrome 1.3 inch 128x64 OLED graphic display"));
    Serial.println(F("(5) Mini Pushbutton Switch #1"));
    Serial.println(F("(6) Mini Pushbutton Switch #2"));
    Serial.println(F("(7) Arcade Button with LED - 30mm Translucent Red"));
    Serial.println(F("(8) 3W Stereo Speaker #1"));
    Serial.println(F("(9) 3W Stereo Speaker #2"));
    Serial.println(F("(menu) send anything else or press on board reset button\n"));
    while (!Serial.available());

    // Read data from serial monitor if received
    while (Serial.available()) 
    {
        char c = Serial.read();
        if (isAlphaNumeric(c)) 
        {   
            
            if(c == '1') 
    			Serial.println(F("Now Testing Heart Rate Pulse Sensor"));
    		else if(c == '2') 
    			Serial.println(F("Now Testing Hazardous Gas  Sensor - MQ-135 - note that this component doesn't have a test code"));
    		else if(c == '3') 
    			Serial.println(F("Now Testing Methane, Butane, LPG and Smoke Gas Sensor - MQ-2 - note that this component doesn't have a test code"));
    		else if(c == '4') 
    			Serial.println(F("Now Testing Monochrome 1.3 inch 128x64 OLED graphic display"));
    		else if(c == '5') 
    			Serial.println(F("Now Testing Mini Pushbutton Switch #1"));
    		else if(c == '6') 
    			Serial.println(F("Now Testing Mini Pushbutton Switch #2"));
    		else if(c == '7') 
    			Serial.println(F("Now Testing Arcade Button with LED - 30mm Translucent Red - note that this component doesn't have a test code"));
    		else if(c == '8') 
    			Serial.println(F("Now Testing 3W Stereo Speaker #1"));
    		else if(c == '9') 
    			Serial.println(F("Now Testing 3W Stereo Speaker #2"));
            else
            {
                Serial.println(F("illegal input!"));
                return 0;
            }
            time0 = millis();
            return c;
        }
    }
}

/*******************************************************

*    Circuito.io is an automatic generator of schematics and code for off
*    the shelf hardware combinations.

*    Copyright (C) 2016 Roboplan Technologies Ltd.

*    This program is free software: you can redistribute it and/or modify
*    it under the terms of the GNU General Public License as published by
*    the Free Software Foundation, either version 3 of the License, or
*    (at your option) any later version.

*    This program is distributed in the hope that it will be useful,
*    but WITHOUT ANY WARRANTY; without even the implied warranty of
*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*    GNU General Public License for more details.

*    You should have received a copy of the GNU General Public License
*    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*    In addition, and without limitation, to the disclaimers of warranties 
*    stated above and in the GNU General Public License version 3 (or any 
*    later version), Roboplan Technologies Ltd. ("Roboplan") offers this 
*    program subject to the following warranty disclaimers and by using 
*    this program you acknowledge and agree to the following:
*    THIS PROGRAM IS PROVIDED ON AN "AS IS" AND "AS AVAILABLE" BASIS, AND 
*    WITHOUT WARRANTIES OF ANY KIND EITHER EXPRESS OR IMPLIED.  ROBOPLAN 
*    HEREBY DISCLAIMS ALL WARRANTIES, EXPRESS OR IMPLIED, INCLUDING BUT 
*    NOT LIMITED TO IMPLIED WARRANTIES OF MERCHANTABILITY, TITLE, FITNESS 
*    FOR A PARTICULAR PURPOSE, NON-INFRINGEMENT, AND THOSE ARISING BY 
*    STATUTE OR FROM A COURSE OF DEALING OR USAGE OF TRADE. 
*    YOUR RELIANCE ON, OR USE OF THIS PROGRAM IS AT YOUR SOLE RISK.
*    ROBOPLAN DOES NOT GUARANTEE THAT THE PROGRAM WILL BE FREE OF, OR NOT 
*    SUSCEPTIBLE TO, BUGS, SECURITY BREACHES, OR VIRUSES. ROBOPLAN DOES 
*    NOT WARRANT THAT YOUR USE OF THE PROGRAM, INCLUDING PURSUANT TO 
*    SCHEMATICS, INSTRUCTIONS OR RECOMMENDATIONS OF ROBOPLAN, WILL BE SAFE 
*    FOR PERSONAL USE OR FOR PRODUCTION OR COMMERCIAL USE, WILL NOT 
*    VIOLATE ANY THIRD PARTY RIGHTS, WILL PROVIDE THE INTENDED OR DESIRED
*    RESULTS, OR OPERATE AS YOU INTENDED OR AS MAY BE INDICATED BY ROBOPLAN. 
*    YOU HEREBY WAIVE, AGREE NOT TO ASSERT AGAINST, AND RELEASE ROBOPLAN, 
*    ITS LICENSORS AND AFFILIATES FROM, ANY CLAIMS IN CONNECTION WITH ANY OF 
*    THE ABOVE. 
********************************************************/