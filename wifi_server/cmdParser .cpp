/**
 * @file cmdParser.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2022-09-28
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "cmdParser.h"


cmdParser::cmdParser()
{
    Serial.println("creating command parser");
    //Icnt_control = new cnt_controller();
    Icnt_control = static_cast<std::shared_ptr<Icnt_controller>>(std::make_shared<cnt_controller>());

}

void cmdParser::passArg(std::shared_ptr<Icnt_controller> ptrToObj, String arg)
{
    ptrToObj->getArg(arg);
}

void cmdParser::processCmd(String& cmd)
{
    if (cmd.isEmpty()) return;
    Serial.println("processing command: ");
    if (cmd.indexOf("=") > 0) // we have cmd with arg
    {
        arg = cmd.substring(cmd.indexOf("=") + 1, cmd.length());
        cmd = cmd.substring(0, cmd.indexOf("="));
        Serial.println("cmd: "); Serial.println(cmd);

        Serial.println("arg: "); Serial.println(arg);

        passArg(Icnt_control, arg);
    }
    for (auto iter_cmd : cmd_callbacks)
    {
        if (iter_cmd.first == cmd)
        {
            Serial.println("cmd found");
            Serial.println("invoking callback");
            cmd_callbacks[cmd](Icnt_control.get()); //run callback
        }
    }
}
