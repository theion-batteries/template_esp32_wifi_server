/**
 * @file cnt_motion.h
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2022-09-28
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once
#include <Arduino.h>
#include <map>
 /************ Interface cnt motion **********/

struct arduinoSerial
{

    std::map<String, String> commands{ {"up","$H\n"}, {"down", "X-150\n"}, {"id","$X\n"}, };
    int rxPin = 16;
    int txPin = 17;
    long baudrate = 115200;
    arduinoSerial() = default;
    arduinoSerial(long baudrate, int rxPin, int txPin) : baudrate(baudrate), rxPin(rxPin), txPin(txPin)
    {
        Serial2.begin(baudrate, SERIAL_8N1, rxPin, txPin);
    }
    void attach()
    {
        Serial2.begin(baudrate, SERIAL_8N1, rxPin, txPin);
    }
    void executeCmd(String cmd)
    {
        Serial2.println(commands[cmd]);
        Serial.println("command ");
        Serial.print(commands[cmd]);
        Serial.println("sent to arduino");
        if (Serial2.available())
        {
            auto response = Serial2.readString();
             Serial.println("arduino reply: ");
            Serial.print(response);
        }
        else Serial.println("error arduino not responding");

    }
};

class Icnt_motion
{
public:
    Icnt_motion() = default;
    virtual void move_up() = 0;
    virtual void move_down() = 0;
    virtual void unlock() = 0;
    virtual ~Icnt_motion() = default;
};
class cnt_motion : public Icnt_motion
{
private:
    arduinoSerial ArduinoInterface;
public:
    cnt_motion();
    virtual void move_up();
    virtual void move_down();
    virtual void unlock();
    virtual ~cnt_motion() = default;
};
