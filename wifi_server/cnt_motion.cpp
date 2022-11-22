#include "cnt_motion.h"

cnt_motion::cnt_motion()
{
    Serial.println("creating cnt motion interface");
    ArduinoInterface.attach();
    //ArduinoInterface.executeCmd("id");

}

void cnt_motion::move_down()
{
    Serial.println("arduino move down requested");
    ArduinoInterface.executeCmd("down");

}


void cnt_motion::move_up()
{
    Serial.println("arduino move up requested");

    ArduinoInterface.executeCmd("up");

}

void cnt_motion::unlock()
{
 Serial.println("arduino unlock requested");
    ArduinoInterface.executeCmd("id");
}