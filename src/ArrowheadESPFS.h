//
// Created by Szvetlin Tanyi on 2020. 04. 06.
//

#ifndef ARROWHEADESP_ARROWHEADESPFS_H
#define ARROWHEADESP_ARROWHEADESPFS_H

#ifdef ESP32
#include "SPIFFS.h"
#endif

// Library includes
#include "FS.h"
#include <ArduinoJson.h>

// Header includes
#include "Util.h"

// Datastructures
#include "dataStructures.h"

const uint16_t JSON_SIZE = 512;

enum validateStates {
    NO_CONFIG, CONFIG_TOO_BIG, CANNOT_PARSE, INCOMPLETE, GOOD_CONFIG
};

class ArrowheadESPFS {
private:
    netInfo _networkData;
    sslInfo _sslData;

    bool loadNetworkConfig(const char *fileName);
    bool loadSSLConfig(const char *fileName);

    File loadFile(const char *fileName);

    int8_t validateConfig(JsonDocument *doc);
    int8_t validateSSLConfig(JsonDocument *doc);

    bool deserializeJSONFromFile(File file, JsonDocument *doc);

    char _ssid[32];
    char _password[32];
    int _insecure = 0;
    char _filenameCa[32];
    char _filenamePk[32];
    char _filenameCl[32];

public:
    ArrowheadESPFS();

    void loadConfigFile(const char *configFileName);
    void loadSSLConfigFile(const char *sslFileName);

    netInfo getNetInfo();
    sslInfo getSSLInfo();
};


#endif //ARROWHEADESP_ARROWHEADESPFS_H
