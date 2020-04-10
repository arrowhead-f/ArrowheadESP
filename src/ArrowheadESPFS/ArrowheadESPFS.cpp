//
// Created by Szvetlin Tanyi on 2020. 04. 06.
//

#include "ArrowheadESPFS.h"

// #######################################
// Constructors
// #######################################

ArrowheadESPFS::ArrowheadESPFS() {
    debugPrintln("ArrowheadESPFS Default Constructor");
    // Start the filesystem
    if (!SPIFFS.begin()) {
        debugPrintln("Failed to mount file system");
        return;
    } else {
        debugPrintln("File system mounted");
    }
}

// #######################################
// Private functions
// #######################################

bool ArrowheadESPFS::loadNetworkConfig(const char *fileName) {
    File networkConfig = loadFile(fileName);

    StaticJsonDocument <JSON_SIZE> doc;
    if (!deserializeJSONFromFile(networkConfig, &doc)) {
        return false;
    }

    if (validateConfig(&doc) != GOOD_CONFIG) {
        return false;
    }

    // copy the values into variables, so their value won't change if the doc is changed
    strlcpy(_ssid, doc["ssid"], sizeof(_ssid));
    strlcpy(_password, doc["password"], sizeof(_password));

    // assign value to the struct
    _networkData = {
            ssid: _ssid,
            password: _password
    };

    debugPrintln("Reading config file with values: ");
    debugPrintln(String("SSID: ") + _networkData.ssid);
    debugPrintln(String("Password: ") + _networkData.password);
    return true;
}

bool ArrowheadESPFS::loadSSLConfig(const char *fileName) {
    File sslConfig = loadFile(fileName);

    StaticJsonDocument<JSON_SIZE> doc;
    if(!deserializeJSONFromFile(sslConfig, &doc)) {
        return false;
    }

    if(validateSSLConfig(&doc) != GOOD_CONFIG) {
        return false;
    }

    if(doc.containsKey("insecure")){
        _insecure = atoi(doc["insecure"]);
    }

    // copy the values into variables, so their value won't change if the doc is changed
    strlcpy(_filenameCa, doc["filenameCa"], sizeof(_filenameCa));
    strlcpy(_filenamePk, doc["filenamePk"], sizeof(_filenamePk));
    strlcpy(_filenameCl, doc["filenameCl"], sizeof(_filenameCl));

    // assign value to the struct
    _sslData = {
            insecure : _insecure,
            filenameCa : _filenameCa,
            filenamePk : _filenamePk,
            filenameCl : _filenameCl
    };

    // load the certificates
    _ca = loadFile(_filenameCa);
    _pk = loadFile(_filenamePk);
    _cl = loadFile(_filenameCl);

    debugPrintln("Reading config file with values: ");
    debugPrintln(String("CA filename: ") + _sslData.filenameCa);
    debugPrintln(String("PK filename: ") + _sslData.filenamePk);
    debugPrintln(String("CL filename: ") + _sslData.filenameCl);
    debugPrintln(String("Insecure: ") + _sslData.insecure);
    return true;
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
    // could this be improved?
    return file;
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

int8_t ArrowheadESPFS::validateSSLConfig(JsonDocument *doc) {
    if(doc->size() == 0) {
        return NO_CONFIG;
    }

    if(!doc->containsKey("filenameCa") ||
       !doc->containsKey("filenamePk") ||
       !doc->containsKey("filenameCl")) {

        if(!doc->containsKey("filenameCa")) {
            debugPrintln("JSON - Missing filenameCa");
        }

        if(!doc->containsKey("filenamePk")) {
            debugPrintln("JSON - Missing filenamePk");
        }

        if(!doc->containsKey("filenameCl")) {
            debugPrintln("JSON - Missing filenameCl");
        }

        debugPrintln("SSL Config is incomplete");
        return INCOMPLETE;
    }

    debugPrintln("Config is good");
    return GOOD_CONFIG;
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

// #######################################
// Public functions
// #######################################

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

void ArrowheadESPFS::loadSSLConfigFile(const char *sslFileName) {
    bool sslConfigLoaded = false;
    debugPrintln(String("Trying to load ") + sslFileName);

    sslConfigLoaded = loadSSLConfig(sslFileName);

    if(!sslConfigLoaded) {
        debugPrintln("Could not load SSL config...");
    } else {
        debugPrintln("SSL Config loaded");
    }
}

netInfo ArrowheadESPFS::getNetInfo() {
    return _networkData;
}

sslInfo ArrowheadESPFS::getSSLInfo() {
    return _sslData;
}

File& ArrowheadESPFS::getCA() {
    return _ca;
}

File& ArrowheadESPFS::getPK() {
    return _pk;
}

File& ArrowheadESPFS::getCl() {
    return _cl;
}