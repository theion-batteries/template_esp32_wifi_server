#include "cnt_controller.h"

cnt_controller::cnt_controller()
{
    Serial.println("creating cnt controller interface");
    dispenserPtr = static_cast<std::shared_ptr<Icnt_dispenser>>(std::make_shared<cnt_dispenser>());
    motionPtr = static_cast<std::shared_ptr<Icnt_motion>>(std::make_shared<cnt_motion>());
    //dispenserPtr = new cnt_dispenser();
    //motionPtr = new cnt_motion();
}

void cnt_controller::move_down()
{
    // Debug
    Serial.println("move down called");
    motionPtr->move_down();
}

void cnt_controller::move_up()
{
    Serial.println("move up called");
    motionPtr->move_up();
}

void cnt_controller::vibrate()
{
    Serial.println("vibrate called");

    dispenserPtr->vibrate();
}

void cnt_controller::turn_on()
{
    dispenserPtr->turn_on();
}

void cnt_controller::turn_off()
{
    dispenserPtr->turn_off();
}

void cnt_controller::set_duration(u_int duration)
{
    dispenserPtr->set_duration(duration);
}

void cnt_controller::set_dur()
{
    Serial.println("set duration called");
    Serial.println("with arg: ");
    auto argInt = Intarg.toInt();
    Serial.println(Intarg);
    set_duration(argInt);

}


void cnt_controller::unlock()
{
    Serial.println("unlock called");
    motionPtr->unlock();
}

void cnt_controller::getArg(String Extarg)
{
    Intarg = Extarg;
    Serial.println("setting internal arg to: ");
    Serial.println(Intarg);


}







cnt_controller:: ~cnt_controller()
{

    //delete motionPtr;
    //delete dispenserPtr;
}