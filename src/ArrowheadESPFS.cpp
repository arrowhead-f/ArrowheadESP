//
// Created by Szvetlin Tanyi on 2020. 04. 06.
//

#include "ArrowheadESPFS.h"

ArrowheadESPFS::ArrowheadESPFS() {
    debugPrintln("ArrowheadESPFS Default Constructor");
    if (!SPIFFS.begin()) {
        debugPrintln("Failed to mount file system");
        return;
    } else {
        debugPrintln("File system mounted");
    }

}

void ArrowheadESPFS::loadConfigFile(const char *configFileName) {
    bool configLoaded = false;
    debugPrintln(String("Trying to load ") + configFileName);

    configLoaded = loadNetworkConfig(configFileName);

    if (!configLoaded) {
        debugPrintln("Could not load config...");
    } else {
        debugPrintln("Config loaded");
    }
}

bool ArrowheadESPFS::loadNetworkConfig(const char *fileName) {
    File networkConfig = loadFile(fileName);
    StaticJsonDocument <JSON_SIZE> doc;
    if (!deserializeJSONFromFile(networkConfig, &doc)) {
        return false;
    }

    if (validateConfig(&doc) != GOOD_CONFIG) {
        return false;
    }

    _networkData = {
            ssid: doc["ssid"],
            password: doc["password"]
    };

    debugPrintln("Reading config file with values: ");
    debugPrintln(String("SSID: ") + _networkData.ssid);
    debugPrintln(String("Password: ") + _networkData.password);
    return true;
}

bool ArrowheadESPFS::deserializeJSONFromFile(File file, JsonDocument *doc) {
    size_t size = file.size();
    debugPrintln(String("JSON File Size: ") + size);
    if (size > JSON_SIZE) {
        debugPrintln("JSON File too large - returning false");
        return false;
    }

    DeserializationError error = deserializeJson(*doc, file);
    if (error && size != 0) {
        debugPrintln("JSON File corrupt/could not be deserialized - returning false");
        return false;
    }

    debugPrintln("JSON File successfully parsed");
    return true;
}

int8_t ArrowheadESPFS::validateConfig(JsonDocument *doc) {
    if (doc->size() == 0) {
        return NO_CONFIG;
    }

    if (!doc->containsKey("ssid") || !doc->containsKey("password")) {
        if (!doc->containsKey("ssid")) {
            debugPrintln("JSON - Missing ssid!");
        }
        if (!doc->containsKey("password")) {
            debugPrintln("JSON - Missing password!");
        }

        debugPrintln("Config is incomplete");

        return INCOMPLETE;
    }

    debugPrintln("Config is good");
    return GOOD_CONFIG;
}

File ArrowheadESPFS::loadFile(const char *fileName) {
    debugPrintln(String("Opening file: ") + fileName);
    //open the file as read only
    File file = SPIFFS.open(String("/") + fileName, "r");

    //check to make sure, opening was possible
    if (!file) {
        debugPrintln(String("Failed to open ") + fileName);
        file.close();
    } else {
        debugPrintln(String("Successfully opened ") + fileName);
    }
    return file;
}

netInfo ArrowheadESPFS::getNetInfo() {
    return _networkData;
}