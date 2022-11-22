/**
 * @file cmdParser.h
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
#include <functional>
#include "cnt_controller.h"
#include <thread>
#include <iostream>
#include <future>
#include <vector>
#include <mutex>
class cmdParser
{
private:
    std::shared_ptr<Icnt_controller> Icnt_control; 
    using fnCmd = std::function<void(Icnt_controller*)>;
    std::map < String, fnCmd > cmd_callbacks =
    {
        std::make_pair("move_down", std::mem_fn(&Icnt_controller::move_down)),
        std::make_pair("move_up", std::mem_fn(&Icnt_controller::move_up)),
        std::make_pair("vibrate", std::mem_fn(&Icnt_controller::vibrate)),
        std::make_pair("turn_on", std::mem_fn(&Icnt_controller::turn_on)),
        std::make_pair("turn_off", std::mem_fn(&Icnt_controller::turn_off)),
        std::make_pair("set_duration", std::mem_fn(&Icnt_controller::set_dur)),
        std::make_pair("unlock", std::mem_fn(&Icnt_controller::unlock))
    
    };
    String arg;
public:
    cmdParser();
    void processCmd( String& cmd);
    void passArg(std::shared_ptr<Icnt_controller> ptrToObj, String arg);
    ~cmdParser()
    {
        //delete Icnt_control;
    }
    void testCallTask()
    {
        Serial.println("call cmd parser from task");
    }
};