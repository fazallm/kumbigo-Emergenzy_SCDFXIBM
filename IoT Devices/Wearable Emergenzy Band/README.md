# Wearable Emergenzy Band

## Content

1. [Description](#description)
2. [Architecture](#architecture)
3. [Demo](#demo)
4. [Hardware Sensor and Feature](#hardware-sensor-and-feature)
5. [Code](#code)

## Description

In order to understand the emergency situation better among elderly and other population and allow faster respond to handle the stituation we create Wearable Emergency Band. This band will use arduino nano ble sense as the hearth of the band.

In addition to that, this emergency band will detect if user have cardiac arrest by detect the hearth pulse of the user using heart pulse sensor. This Wearable Emergenzy Band will communicate to user phone using the improved my responder app using bluetooth signal

## Architecture

<image src='Architecture.JPG'>

## Demo

<image src='emergenzy band.JPG'>
This is the prototype visualization of the Emergency Bands

<image src='arm band.JPG'>
This is the demo picture of emergenzy band in development state with wiring in breadboard development board.

## Hardware Sensor and Feature

<image src='arduino nano ble sense.JPG'>
The most important hardware for our emergenzy band is arduino nano ble sense. This arduino have 9 axis inertial sensor and barometric sensor to detect sudden drop of altitude indicating the user have fall from standing. It also have microphone, light led, light intensity to know the current situation of the user in case of emergency.

for privacy matters, the data from the arduino nano is stored locally in users phone encrypted via built in bluetooth connection. So no one can have the access to the user data. Only by the time of emergency happen, the data will then be uploaded securely to SCDF ADMIN SERVER, user can request turn off some of the sensor

FIRST FEATURE: FALL DETECTION
<image src='preassure drop.JPG'>
using the arduino preassure sensor and the 9 axis inertial sensor, the user phone will use the data to determine the user has accidental fall. The sudden drop in preassure / altitude with sudden acceleration detected from fall impact would only mean the user has accidental fall. The arduino then send data to the phone to activate emergency status. The phone then collect with additional data of the environment, location and medical history then send to SCDF 995 services.

SECOND FEATURE: CARDIAC ARREST
<image src='pulse sensor.jpg'>
using the arduino preassure sensor and the 9 axis inertial sensor, the user phone will use the data to determine the user has accidental fall. from the cardiac arrest. Other than that the arduino also will check the hearth pulse rate using arduino pulse sensor. Here's the example graph result from the arduino.

<image src='pulse sensor graph.jpg'>
When user experiencing accidental fall and lost of hearth pulse the arduino will activate emergency status of cardiac arrest. The phone then collect with additional data of the environment, location and medical history then send to SCDF 995 services.

## Code

code is available in firmware folder
