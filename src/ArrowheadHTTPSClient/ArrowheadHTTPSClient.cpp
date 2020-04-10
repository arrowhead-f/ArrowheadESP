//
// Created by Szvetlin Tanyi on 2020. 04. 09..
//

#include "ArrowheadHTTPSClient.h"

// #######################################
// Constructors
// #######################################

ArrowheadHTTPSClient::ArrowheadHTTPSClient() {
    debugPrintln("ArrowheadHTTPSClient Default Constructor");
}

// #######################################
// Public functions
// #######################################

WiFiClientSecure& ArrowheadHTTPSClient::getWiFiClientSecure() {
    return _wiFiClientSecure;
}