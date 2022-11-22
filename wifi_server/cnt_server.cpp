#include "cnt_server.h"

webServer::webServer() {

    Serial.begin(115200);
    Serial.println("creating web server");
    server = WiFiServer(port);
}
void webServer::init()
{
    Serial.begin(115200);
    server = WiFiServer(port);
}
void webServer::scanNetwork()
{
    // if the ssid and pass are passed to constructor, ignore scan
    if (!ssid.isEmpty() && !password.isEmpty()) return;
    int n = wlan.scanNetworks();
    Serial.println("scanning network available: ");
    bool found = false;
    // iterate wifis
    for (int i = 0;i < n; i++)
    {
        Serial.println(wlan.SSID(i));
        for (auto saved : saved_wifis)
        {
            if (wlan.SSID(i) == saved.first)
            {
                Serial.println("found saved wifi: ");
                Serial.println("-------------------");
                Serial.println(saved.first);
                Serial.println("-------------------");

                ssid = saved.first;
                password = saved.second;
                found = true;
                break;
            }
        }
        if (found) break;
    }
}
void webServer::connect()
{
    // Set your Static IP address
    IPAddress local_IP(192, 168, 0, 204);
    // Set your Gateway IP address
    IPAddress gateway(192, 168, 0, 1);

    IPAddress subnet(255, 255, 255, 0);

    // Configures static IP address
    if (!wlan.config(local_IP, gateway, subnet)) {
        Serial.println("STA Failed to configure");
    }
    // Connect to Wi-Fi network with SSID and password
    Serial.print("Connecting to ");
    Serial.println(ssid);
    wlan.begin(ssid.c_str(), password.c_str());
    while (wlan.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    // Print local IP address and start web wlan
    Serial.println("");
    Serial.println("wlan connected.");
    Serial.println("IP address: ");
    Serial.println(wlan.localIP());
    Serial.println("port: ");
    Serial.println(port);
    server.begin();
}
void webServer::disconnect()
{
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
    client_connected = false;
}
void webServer::listen()
{
    if (client = server.available()) // once new client availble
    {
        Serial.println("New Client connected ..");          // print a message out in the serial port
        Serial.println(client.remoteIP());
        Serial.println(client.remotePort());
        lastClient = static_cast<String>(client.remoteIP());
        client_connected = true;
    }
}

void webServer::parseRequest()
{
    while (client.connected())
    {
        while (client.available()) //if there's bytes to read from the client,
        {
            Serial.println("incoming data");
            auto cmd = client.readString();
            Serial.println(cmd);
            lastCmd = cmd;
            // create thread and process the cmd inside it : ref to this obj
           // auto request = std::async(&webServer::processCmd, std::ref(* this));
            std::thread cmdParserThread(&webServer::processCmd, std::ref(*this));
            cmdParserThread.detach();
            //task.wait();
            // inform cient if done
            if (request_done.load()) // if request 
            {
                client.println("ok!");
                break;
            }
            else
            {
                client.println("err!");
                break;
            }
        }
    }

}

void webServer::processCmd()
{
    Serial.println("new thread executed");
    std::cout << std::this_thread::get_id() << std::endl;
    auto task = std::async([this]() {
        parser.processCmd(lastCmd);
        });

    //parser.processCmd(lastCmd);

    request_done = true;
}
