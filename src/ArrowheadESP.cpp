//
// Created by Szvetlin Tanyi <szvetlin@aitia.ai> on 2020. 04. 06.
//

#include "ArrowheadESP.h"

// #######################################
// Constructors
// #######################################

ArrowheadESP::ArrowheadESP() {
    debugPrintln("ArrowheadESP Default Constructor");
}

ArrowheadESPFS& ArrowheadESP::getArrowheadESPFS() {
    return arrowheadEspFs;
}

bool ArrowheadESP::setupWiFi() {
    if(!getArrowheadESPFS().getNetInfo().ssid || !getArrowheadESPFS().getNetInfo().password) {
        return false;
    }
    delay(10);
    // We start by connecting to a WiFi network
    debugPrintln(String("Connecting to ") + getArrowheadESPFS().getNetInfo().ssid);
    WiFi.mode(WIFI_STA);
    WiFi.begin(getArrowheadESPFS().getNetInfo().ssid, getArrowheadESPFS().getNetInfo().password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    debugPrintln("");
    debugPrintln("WiFi connected");
    debugPrint("IP address: ");
    debugPrintln(WiFi.localIP());

    return true;
}

bool ArrowheadESP::begin(){
    debugPrintln("ArrowheadESP - Begin");
    setupWiFi();

    return true;
}