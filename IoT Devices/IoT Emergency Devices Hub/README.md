# IoT Emergenzy Devices Hub

## Content

1. [Description](#description)
2. [Demo Video](#demo-video)
3. [Architecture](#architecture)
4. [Long Description](#long-description)
5. [Road Map](#road-map)
6. [Installation](#installation)
7. [Tests](#tests)
8. [Demo](#demo)
9. [Component](#component)

### Description

In order to understand the emergency situation better among elderly and other population and allow faster respond to handle the stituation we create IoT Emergenzy Devices Hub to complement the Wearable Emergenzy Band this device will be pace on user home / room. This hub will use arduino the same arduino nano ble sense as the hearth of the band. This arduino will add extra flamable gass and toxic gass/smoke detection sensor. It also have microphone, light led, light intensity to know the current situation of the user in case of emergency. In addition to that, this emergency button will have panic emergency button to activate emergency status and call 995 directly through bluetooth connection to user phone to be forwarded to SCDF Emergency Response Services

This Wearable Emergenzy Band will communicate to user phone using the improved my responder app using bluetooth signal

## Architecture

<image src='Architecture.JPG'>

## Demo Picture

<image src='iot devices hub.jpg'>
This is the prototype visualization of the IoT Emergenzy Devices Hub with speaker, smoke sensor, bluetooth, and panic button embedded in all in one devices

<image src='smoke emergency.JPG'>
This is the demo picture of emergenzy band in development state with wiring in breadboard development board.

## Hardware Sensor and Feature

<image src='arduino nano ble sense.JPG'>
The brain of our IoT Emergenzy Devices Hub is arduino nano ble sense. This devices have have microphone, light led, light intensity to know the current situation of the user in case of emergency.

for privacy matters, the data from the arduino nano is stored locally in users phone encrypted via built in bluetooth connection. So no one can have the access to the user data. Only by the time of emergency happen, the data will then be uploaded securely to SCDF ADMIN SERVER, user can request turn off some of the sensor

FIRST FEATURE: FIRE/SMOKE/DANGERAOUS GASS DETECTION
<image src='smokepicture.JPG'>
using the two extra smoke sensor, the arduino will detect the presence of toxic, flamable gass and smole. The presence of this gass of smoke will detect if fire hazard presence in the house above certain treshold. The arduino then send data to the phone to activate emergency status. The phone then collect with additional data of the environment, location and medical history then send to SCDF 995 services.

SECOND FEATURE: PANIC BUTTON
<image src='iot devices hub.jpg'>
This panic emergency button to activate will activate emergency status of cardiac arrest. The phone then collect with additional data of the environment, location and medical history then send to SCDF 995 services.

## Code

code is available in firmware folder
