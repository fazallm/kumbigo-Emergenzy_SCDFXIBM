# Emergenzy!
This Repository is KumbiGo solution for **SCDF X IBM - Lifesavers' Innovation Challenge: Call For Code 2020**

## Content
1. [Description](#description)
2. [Demo Video](#demo-video)
3. [Architecture](#architecture)
4. [Long Description](#long-description)
5. [Road Map](#road-map)
6. [Installation](#installation)
7. [Live Demo](#live-demo)
8. [Component](#component)

## Description
KumbiGo will solve a problem about creating a system to have better understanding of emergency situation and create a preventive analytics tool. As Singapore coming toward an aging population, there will be many vurnerable citizens to emergency accident, such as cardiac attack, fall, and fire. Our team proposed a solution of combined IoT and mobile applications to have fast and preventive emergency situation. Our team also create an analytics tool for SCDF Officer so SCDF could have better resource allocation and preventive countermeasures.

## Demo Video
[![Emergenzy!](http://img.youtube.com/vi/68Q8o2LnBG0/0.jpg)](http://www.youtube.com/watch?v=68Q8o2LnBG0)

## Architecture

Emergenzy use additional IoT devices to improve data acquisition for current *myResponder* application. We implement smart bracelet named [Wearable Emergenzy Band](https://github.com/fazallm/kumbigo-Emergenzy_SCDFXIBM/tree/master/IoT%20Devices/Wearable%20Band) and multi [Hub Devices](https://github.com/fazallm/kumbigo-Emergenzy_SCDFXIBM/tree/master/IoT%20Devices/IoT%20Emergency%20Devices%20Hub) that allows user to give input to *myResponder* application in more flexible and user-friendly.


<image src="Wearable.jpeg">

After user press button or sensor sense some threat, it will send notification to user's phone. Phone will send request to central service and send command to closest CFR available.


<image src="Flow Diagram.png">

Beside for the application needs, data stored in Cloudant also will be used for analytics. 

<image src="Tableu.png">

## Long Description
You can access complete description via [this page](https://github.com/fazallm/kumbigo-Emergenzy_SCDFXIBM/tree/master/Long%20Description)

## Road Map

<image src="Roadmap.jpeg">

## Installation

This tutorial will allow you to run the backend.

Install docker from [link](https://docs.docker.com/get-docker/)

Then open terminal in this folder and run this command

```
cd backend
docker build . -t cfr-emergency
docker run -p 8080:8080 cfr-emergency
```

The service will run and connect to Cloudant automatically. You can open by using [localhost:8080](localhost:8080)

## Live Demo
[![Emergenzy Application Demo](http://img.youtube.com/vi/ug4csLX9RF4/0.jpg)](http://www.youtube.com/watch?v=ug4csLX9RF4)

<a href="http://www.youtube.com/watch?feature=player_embedded&v=llO5we8W9-M
" target="_blank"><img src="http://img.youtube.com/vi/llO5we8W9-M/0.jpg" 
alt="Visual Analytics Tools" width="240" height="180"/></a>

## Component
1. IBM Cloudant as database for our application.
2. IBM Push Notification service
3. Python Flask as web framework
4. Docker for containerize the application
5. Firebase Cloud Messaging and Apple Push Notification Service
6. React Native for mobile app development
7. Arduino Uno BLE-Sense for IoT devices development
8. IBM Analytics for Data Analytic Tools.