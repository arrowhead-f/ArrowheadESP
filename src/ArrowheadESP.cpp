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

bool ArrowheadESP::setupCertificates() {
    // By default 'pool.ntp.org' is used with 60 seconds update interval and
    // no offset
    NTPClient timeClient(ntpUDP);
    timeClient.begin();
    while (!timeClient.update()) {
        timeClient.forceUpdate();
    }
    getWiFiClientSecure().setX509Time(timeClient.getEpochTime());
    getWiFiClientSecure().setTimeout(5000);
    getWiFiClientSecure().setBufferSizes(512,512);

    if(getArrowheadESPFS().getSSLInfo().insecure){
        getWiFiClientSecure().setInsecure();
        debugPrintln("Disabled CA verification");
    }

    if(getWiFiClientSecure().loadCACert(getArrowheadESPFS().getCA())){
        debugPrintln("CA cert loaded");
    } else {
        debugPrintln("CA cert failed");
    }

    delay(1000);

    if(getWiFiClientSecure().loadCertificate(getArrowheadESPFS().getCl())){
        debugPrintln("Client cert loaded");
    } else {
        debugPrintln("Client cert failed");
    }

    delay(1000);

    if(getWiFiClientSecure().loadPrivateKey(getArrowheadESPFS().getPK())){
        debugPrintln("Private key loaded");
    } else {
        debugPrintln("Private key failed");
    }

    delay(1000);
}

WiFiClientSecure& ArrowheadESP::getWiFiClientSecure() {
    return _wiFiClientSecure;
}

bool ArrowheadESP::begin(){
    debugPrintln("ArrowheadESP - Begin");
    setupWiFi();
    delay(1000);
    setupCertificates();

    return true;
}

int ArrowheadESP::loop() {
    // TODO
}