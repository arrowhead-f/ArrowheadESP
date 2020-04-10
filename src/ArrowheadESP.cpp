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

// #######################################
// Private functions
// #######################################

bool ArrowheadESP::setupWiFi() {
    // We have to check that everything is available before proceeding
    if(!getArrowheadESPFS().getNetInfo().ssid || !getArrowheadESPFS().getNetInfo().password) {
        return false;
    }
    delay(10);
    // We start by connecting to a WiFi network
    debugPrintln(String("Connecting to ") + getArrowheadESPFS().getNetInfo().ssid);
    // WiFi in Station mode
    WiFi.mode(WIFI_STA);
    // Initiate the WiFi connection
    WiFi.begin(getArrowheadESPFS().getNetInfo().ssid, getArrowheadESPFS().getNetInfo().password);

    // Wait until not connected
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
    // Set up the NTPClient. It's constructor needs an UDP client. If somebody has a better solution then declaring it here, let me know.

    // By default 'pool.ntp.org' is used with 60 seconds update interval and
    // no offset
    NTPClient timeClient(_ntpUDP);
    timeClient.begin();
    while (!timeClient.update()) {
        timeClient.forceUpdate();
    }
    // Set the proper time for Certificate validation
    getArrowheadHTTPSClient().getWiFiClientSecure().setX509Time(timeClient.getEpochTime());
    // Setting the request timeout
    getArrowheadHTTPSClient().getWiFiClientSecure().setTimeout(5000);
    // Setting the buffer sizes
    getArrowheadHTTPSClient().getWiFiClientSecure().setBufferSizes(512,512);

    // Disable X509 Certificate verification
    if(getArrowheadESPFS().getSSLInfo().insecure){
        getArrowheadHTTPSClient().getWiFiClientSecure().setInsecure();
        debugPrintln("Disabled CA verification");
    }

    // Load CA certificate
    if(getArrowheadHTTPSClient().getWiFiClientSecure().loadCACert(getArrowheadESPFS().getCA())){
        debugPrintln("CA cert loaded");
    } else {
        debugPrintln("CA cert failed");
    }
    delay(1000);

    // Load Client certificate
    if(getArrowheadHTTPSClient().getWiFiClientSecure().loadCertificate(getArrowheadESPFS().getCl())){
        debugPrintln("Client cert loaded");
    } else {
        debugPrintln("Client cert failed");
    }
    delay(1000);

    // Load Private key
    if(getArrowheadHTTPSClient().getWiFiClientSecure().loadPrivateKey(getArrowheadESPFS().getPK())){
        debugPrintln("Private key loaded");
    } else {
        debugPrintln("Private key failed");
    }
    delay(1000);
}

// #######################################
// Public functions
// #######################################

ArrowheadESPFS& ArrowheadESP::getArrowheadESPFS() {
    return _arrowheadEspFs;
}

ArrowheadHTTPSClient& ArrowheadESP::getArrowheadHTTPSClient() {
    return _httpsClient;
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