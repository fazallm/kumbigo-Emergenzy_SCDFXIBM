//FOR DPS 310 PRESSURE SENSOR
#include <ifx_dps310.h>
const float sea_press = 1013.25; // DECLARING SEA LEVEL PRSSURE AS CONSTANT
int alttitude = 0;         // the sensor value
int minimumalttitude = 100000;        // minimum sensor value (changes after calibration)
int maximumalttitude = 0;           // maximum sensor value(changes after calibration)

 // FOR EMERGRNCY BUTTON
int buttonState = 0; // FOR EMERGENCY BUTTON
const int buttonPin = 4; //DIGITAL PIN 4 DECLARED AS EMERGENCY PI

// FOR HEARTBEAT SENSOR
int pulsePin = 0;                 // Pulse Sensor purple wire connected to analog pin 0
unsigned long previousMillis = 0;        // will store last time pulse sensor sensed
const long interval = 5000;           // interval at which pulse should be sensed
// Volatile Variables, used in the interrupt service routine!
volatile int BPM;                   // int that holds raw Analog in 0. updated every 2mS
volatile int Signal;                // holds the incoming raw data
volatile int IBI = 600;             // int that holds the time interval between beats! Must be seeded!
volatile boolean Pulse = false;     // "True" when User's live heartbeat is detected. "False" when not a "live beat".
volatile boolean QS = false;        // becomes true when Arduoino finds a beat.

// FOR BLYNK APP
#define BLYNK_USE_DIRECT_CONNECT
#include <SoftwareSerial.h>
SoftwareSerial DebugSerial(2, 3); // RX, TX FOR HC05 BLUETOOTH MODULES
#define BLYNK_PRINT DebugSerial
#include <BlynkSimpleSerialBLE.h>
 // You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "YourAuthToken";  // GIVE YOUR BLYNK TOKEN HERE

void setup(){
pinMode(buttonPin, INPUT); //emergency pi declared as input
  Serial.begin(9600);             
  interruptSetup();                 // sets up to read Pulse Sensor signal every 2mS
   // IF YOU ARE POWERING The Pulse Sensor AT VOLTAGE LESS THAN THE BOARD VOLTAGE,
   // UN-COMMENT THE NEXT LINE AND APPLY THAT VOLTAGE TO THE A-REF PIN
  analogReference(3.3); //the voltage given to heartbeat sensor 
   while (!Serial);
  Wire.begin();


  //Call begin to initialize ifxDps310
  //The parameter 0x76 is the bus address. The default address is 0x77 and does not need to be given.
  ifxDps310.begin(Wire, 0x76);
  //Use the commented line below instead of the one above to use the default I2C address.
  //if you are using the Pressure 3 click Board, you need 0x76
  //ifxDps310.begin(&Wire);
  
  // IMPORTANT NOTE
  //If you face the issue that the DPS310 indicates a temperature around 60 C although it should be around 20 C (room temperature), you might have got an IC with a fuse bit problem
  //Call the following function directly after begin() to resolve this issue (needs only be called once after startup)
  //ifxDps310.correctTemp();

  Serial.println("Init complete!");
    calibration(); //calling calibration function beacause we cant fix a altitude because it varies every were
                   //so we calibrate the maximum altitude and minimum altitude for 3 seconds

      DebugSerial.begin(9600);

  // Blynk will work through Serial
  // 9600 is for HC-06. For HC-05 default speed is 38400
  // Do not read or write this serial manually in your sketch
  
  Blynk.begin(Serial, auth);
}


//  Where the Magic Happens
void loop(){
    Blynk.run();

  long int temperature;
  long int pressure;
  int oversampling = 7;
  int ret;
  Serial.println();

  //lets the Dps310 perform a Single temperature measurement with the last (or standard) configuration
  //The result will be written to the paramerter temperature
  //ret = ifxDps310.measureTempOnce(temperature);
  //the commented line below does exactly the same as the one above, but you can also config the precision
  //oversampling can be a value from 0 to 7
  //the Dps 310 will perform 2^oversampling internal temperature measurements and combine them to one result with higher precision
  //measurements with higher precision take more time, consult datasheet for more information
  ret = ifxDps310.measureTempOnce(temperature, oversampling);

  if (ret != 0)
  {
    //Something went wrong.
    //Look at the library code for more information about return codes
    Serial.print("FAIL! ret = ");
    Serial.println(ret);
  }
  else
  {
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println(" degrees of Celsius");
  }
  if(temperature > 40) //                       CHEcking body temperatrue
  {                                             //you should degin the case as per the sensor touches the skin else there is no use for this checking
    Serial.println("temperature rise");
  Blynk.email("your_email@mail.com", "subject :temperature rise is noticed ", "your randma/grandpa 's temperature has increased beyond normal value"); // provide your email id
  }

  //Pressure measurement behaves like temperature measurement
  //ret = ifxDps310.measurePressureOnce(pressure);
  ret = ifxDps310.measurePressureOnce(pressure, oversampling);
  if (ret != 0)
  {
    //Something went wrong.
    //Look at the library code for more information about return codes
    Serial.print("FAIL! ret = ");
    Serial.println(ret);
  }
  else
  {
    Serial.print("Pressure: ");
    Serial.print(pressure);
    Serial.println(" Pascal");
  }

  float getaltitude=(((pow((sea_press/(pressure)), 1/5.257) - 1.0)*(temperature +273.15)))/0.0065; //hypsometric formula to covert presure and temperature of a region to altitude
 
 Serial.print(getaltitude);  //print the obtained altitude
 
    if(alttitude < (maximumalttitude - .5)) //if calibrated MAXIMUM alttitude is 3M. IF a SUDDEN FALL OCCURS WHCIH IS LESS THAN 2.5M (maximumalttitude - .5)  THEN WE CAN ASSUME A FALL OCCURS
    {                                       // we take a diiference of .5 meter decrement as falling situation. you can change as per your need
                                            // if you need to send the BPM rate coreesponding to this time you can add it in the email option
     Serial.println("alttitude drop");
  Blynk.email("your_email@mail.com", "subject :alttitude drop occurs ", "your randma/grandpa 's mAY fall down and required assistance"); // provide your email id
    }
    
    if(alttitude  > (maximumalttitude + 1)) //if calibrated MAXIMUM alttitude is 3M IF a rise occurs more than 1 METER  which means cmlimbing up 
   
    { 

Serial.println("alttitude rise");
  Blynk.email("your_email@mail.com", "subject :alttitude rise occurs ", "your randma/grandpa 's climbing up a ladder or something "); // provide your email id
   
    }

   
    
 unsigned long currentMillis = millis();
 if (currentMillis - previousMillis >= interval) // sense heart beat at every 5 second intervel you can change as per your need
 {
  
    while (millis() < (currentMillis + 3000)) // calibration time you can change it as per your need
   {
   
  if (QS == true){     // A Heartbeat Was Found
                       // BPM and IBI have been Determined
                       // Quantified Self "QS" true when arduino finds a heartbeat
   
       
        QS = false;                      // reset the Quantified Self flag for next time
  }}
  Serial.println(" . ");
Serial.println(BPM);
Serial.println("  .");
  //delay(20); //  take a break
  unsigned long currentMillis = millis();
   previousMillis = currentMillis;
  
}
 buttonState = digitalRead(buttonPin); //reading emergency button state
 
   if (buttonState == HIGH) //CHECKING THE EMERGENCY BUTTON STATE
   {
 
  Serial.println("emergency button pressed"); 
  //if pressed emergency email is sending 
  Blynk.email("your_email@mail.com", "subject :emergency case ", "your grandma/grandpa has pressed emergency button he/she need assistance now immediate"); // provide your email id
  }
  
if (BPM<60 || BPM>80) // CHECKING BLOOD PRESSURE
 {  Serial.println("drastic change in blood pressure");
  Blynk.email("your_email@mail.com", "subject :need immediate attenion", "drastic change in blood prssure has been sensed please provide immediate assistance"); // provide your email id
  //you can also include the BPM rate along with the mail if you need
}
} 

void calibration() //we canot fix a height because its changes with location so we calibrate the HEIGHT for 3 seconds
{
   while (millis() < 3000) // calibration time you can change it as per your need
   {

 long int temperature;
  long int pressure;
  int oversampling = 7;
  int ret;
   ret = ifxDps310.measureTempOnce(temperature, oversampling);
  ret = ifxDps310.measurePressureOnce(pressure, oversampling);

    float getaltitude=(((pow((sea_press/(pressure/10)), 1/5.257) - 1.0)*(temperature +273.15)))/0.0065; //hypsometric formula
    alttitude = getaltitude;

    // record the maximum altitude value
    if (alttitude > maximumalttitude) {
      maximumalttitude = alttitude;
    }

    // record the minimum altitue value
    if (alttitude < minimumalttitude) {
      minimumalttitude = alttitude;
    }
    }   Serial.println("");
    Serial.print(maximumalttitude);
    Serial.print(" -- maximumalttitude");
     Serial.println("");
      Serial.print(minimumalttitude);
    Serial.print("  --minimumalttitude");
    Serial.println("");
    
}

//THIS ARE INTERPTS CODE FOR PULSE SENSOR

volatile int rate[10];                    // array to hold last ten IBI values
volatile unsigned long sampleCounter = 0;          // used to determine pulse timing
volatile unsigned long lastBeatTime = 0;           // used to find IBI
volatile int P =512;                      // used to find peak in pulse wave, seeded
volatile int T = 512;                     // used to find trough in pulse wave, seeded
volatile int thresh = 530;                // used to find instant moment of heart beat, seeded
volatile int amp = 0;                   // used to hold amplitude of pulse waveform, seeded
volatile boolean firstBeat = true;        // used to seed rate array so we startup with reasonable BPM
volatile boolean secondBeat = false;      // used to seed rate array so we startup with reasonable BPM


void interruptSetup(){  // CHECK OUT THE Timer_Interrupt_Notes TAB FOR MORE ON INTERRUPTS 
  // Initializes Timer2 to throw an interrupt every 2mS.
  TCCR2A = 0x02;     // DISABLE PWM ON DIGITAL PINS 3 AND 11, AND GO INTO CTC MODE
  TCCR2B = 0x06;     // DON'T FORCE COMPARE, 256 PRESCALER
  OCR2A = 0X7C;      // SET THE TOP OF THE COUNT TO 124 FOR 500Hz SAMPLE RATE
  TIMSK2 = 0x02;     // ENABLE INTERRUPT ON MATCH BETWEEN TIMER2 AND OCR2A
  sei();             // MAKE SURE GLOBAL INTERRUPTS ARE ENABLED
}


// THIS IS THE TIMER 2 INTERRUPT SERVICE ROUTINE.
// Timer 2 makes sure that we take a reading every 2 miliseconds
ISR(TIMER2_COMPA_vect){                         // triggered when Timer2 counts to 124
  cli();                                      // disable interrupts while we do this
  Signal = analogRead(pulsePin);              // read the Pulse Sensor
  sampleCounter += 2;                         // keep track of the time in mS with this variable
  int N = sampleCounter - lastBeatTime;       // monitor the time since the last beat to avoid noise

    //  find the peak and trough of the pulse wave
  if(Signal < thresh && N > (IBI/5)*3){       // avoid dichrotic noise by waiting 3/5 of last IBI
    if (Signal < T){                        // T is the trough
      T = Signal;                         // keep track of lowest point in pulse wave
    }
  }

  if(Signal > thresh && Signal > P){          // thresh condition helps avoid noise
    P = Signal;                             // P is the peak
  }                                        // keep track of highest point in pulse wave

  //  NOW IT'S TIME TO LOOK FOR THE HEART BEAT
  // signal surges up in value every time there is a pulse
  if (N > 250){                                   // avoid high frequency noise
    if ( (Signal > thresh) && (Pulse == false) && (N > (IBI/5)*3) ){
      Pulse = true;                               // set the Pulse flag when we think there is a pulse
      
      IBI = sampleCounter - lastBeatTime;         // measure time between beats in mS
      lastBeatTime = sampleCounter;               // keep track of time for next pulse

      if(secondBeat){                        // if this is the second beat, if secondBeat == TRUE
        secondBeat = false;                  // clear secondBeat flag
        for(int i=0; i<=9; i++){             // seed the running total to get a realisitic BPM at startup
          rate[i] = IBI;
        }
      }

      if(firstBeat){                         // if it's the first time we found a beat, if firstBeat == TRUE
        firstBeat = false;                   // clear firstBeat flag
        secondBeat = true;                   // set the second beat flag
        sei();                               // enable interrupts again
        return;                              // IBI value is unreliable so discard it
      }


      // keep a running total of the last 10 IBI values
      word runningTotal = 0;                  // clear the runningTotal variable

      for(int i=0; i<=8; i++){                // shift data in the rate array
        rate[i] = rate[i+1];                  // and drop the oldest IBI value
        runningTotal += rate[i];              // add up the 9 oldest IBI values
      }

      rate[9] = IBI;                          // add the latest IBI to the rate array
      runningTotal += rate[9];                // add the latest IBI to runningTotal
      runningTotal /= 10;                     // average the last 10 IBI values
      BPM = 60000/runningTotal;               // how many beats can fit into a minute? that's BPM!
      QS = true;                              // set Quantified Self flag
      // QS FLAG IS NOT CLEARED INSIDE THIS ISR
    }
  }

  if (Signal < thresh && Pulse == true){   // when the values are going down, the beat is over
  
    Pulse = false;                         // reset the Pulse flag so we can do it again
    amp = P - T;                           // get amplitude of the pulse wave
    thresh = amp/2 + T;                    // set thresh at 50% of the amplitude
    P = thresh;                            // reset these for next time
    T = thresh;
  }

  if (N > 2500){                           // if 2.5 seconds go by without a beat
    thresh = 530;                          // set thresh default
    P = 512;                               // set P default
    T = 512;                               // set T default
    lastBeatTime = sampleCounter;          // bring the lastBeatTime up to date
    firstBeat = true;                      // set these to avoid noise
    secondBeat = false;                    // when we get the heartbeat back
  }

  sei();                                   // enable interrupts when youre done!
}// end isr




