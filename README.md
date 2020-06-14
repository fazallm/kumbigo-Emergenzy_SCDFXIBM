# Hybrid Solution
This is Description of our project

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
Halo Bro

## Demo Video

## Architecture

After user press button or sensor sense some threat, it will send notification to user's phone. Phone will send request to central service and retireve data of closest user available.

Central Service create and send notification using push notification service that connected to Firebase Central Management(FCM) for android or APNS for ios before it go to corresponding CFR.

<image src="Flow Diagram.png">

CFR and elder reporting data also will be used to  Cloudant to store CFR and 

<image src="Tableu.png">

## Long Description
You can access complete description via [this page](https://github.com/fazallm/kumbigo-Emergenzy_SCDFXIBM/tree/master/Long%20Description)

## Road Map

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

## Tests

## Demo
[![Magneto](http://img.youtube.com/vi/nhab1EWRwF8/0.jpg)](http://www.youtube.com/watch?v=nhab1EWRwF8)

## Component

