# Automatic Data Streaming Pipeline

## Description

Currently *myResponder* use manual operator for receiving report and direct CFR into reported scene. This is very not efficient and may limit SCDF capacity when multiple cases happened at the same time. It may create long queue of request and harm severe cases.

To automate this event and improve time consumed for each case, we create data pipeline so data from reporter will go into CFR phone automatically so it doesn't need to go through SCDF operator.

## Implementation

<image src="../Flow Diagram.png">

First, data and request from reporter will be send to IBM cloud where are multiple services are working. Service will receive the location of reporter and access GoogleMaps API to retrieve location of closest devices available and fetch CFR identity from Cloudant. Then service will send location of reporter to CFR's devices using push notification through FCM or APNS.

It will notify CFR and they will directly go to reporter location and don't have to wait for reporter.

### Current Implementation

For Current solution, we change google maps API with postal code data, and replace push notification with HTTP Streaming pipeline.

<image src="Sample.png">

For reporter device, it will keep sending data by pulling the trigger(smart Bracelet, Multihub, or Button in app) to backend services providing gender, major event that happened and location.

It will be streamed into stream-db where service will put all reporting data.

The difference located on CFR devices. To make sure that there is no missed report, CFR device will always keep requesting cases happened in their location. If there are no cases, it will return no data. But once case is available, it will return reporter location and details so CFR will go directly into reporter.

Once CFR accept the request, service will change status of the cases into 'inactive' in stream-db.

<image src="Use Case Diagram.png">

### Further Improvement

In the future, we will change the system to implement the first diagram where we implement Push Notification, use google maps api and integrate with firebase and APNS to send notification to devices.