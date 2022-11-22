/**
 * @file cnt_server.h
 * @author sami dhiab(you@domain.com)
 * @brief interface webserver for cnt system
 * @version 0.1
 * @date 2022-09-28
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once
#include <WiFi.h>
#include "cmdParser.h"
#include <map>
#include <memory>
#include <functional>
#include <thread>
#include <iostream>
#include <future>
#include <vector>
#include <mutex>
class webServer
{
private:
    std::map<const char*, const char*> saved_wifis{ {"TheionEngineeringLab", "!2021BatLab1"}, {"Halal-wifi", "Halal-Wlan"}, };
    // Replace with your network credentials
    String ssid;
    String password;
    // Set web server port number 
    uint port = 8881;
    //IPAddress fix_ip= "192.168.0.204";

    WiFiClass wlan;
    WiFiServer server;
    WiFiClient client;
    String lastCmd;
    String lastClient;
    bool client_connected = false;
    std::atomic<bool> request_done = false;
    cmdParser parser;

public:

    // default 
    webServer();
    ~webServer() {
        //delete parser;
    }
    // constructor accepting ssid and password
    webServer(const char* ssid, const char* password, uint port) :ssid(ssid), password(password), port(port) {
        server = WiFiServer(port);
    }

    void init();
    // scan
    void scanNetwork();
    // connect
    void connect();
    // disconnect
    void disconnect();
    // listen for clients
    void listen();
    // parse req
    void parseRequest();
    // process cmd wrapper
    void processCmd();

};

