
/**
 * @file cnt_controller.h
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2022-09-28
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once
#include "cnt_motion.h"
#include "cnt_dispenser.h"
#include <memory>

 /************ Interface cnt controller **********/
class Icnt_controller
{

public:
    Icnt_controller() = default;
    virtual void unlock() = 0;
    virtual void move_down() = 0;
    virtual void move_up() = 0;
    virtual void vibrate() = 0;
    virtual void turn_on() = 0;
    virtual void turn_off() = 0;
    virtual void set_dur()= 0;
    virtual void set_duration(u_int duration) = 0;
    virtual void getArg(String arg)= 0;
    virtual ~Icnt_controller() = default;
};

class cnt_controller : public Icnt_controller
{
private:
    std::shared_ptr<Icnt_dispenser> dispenserPtr;
    std::shared_ptr<Icnt_motion> motionPtr;
    String Intarg;
    //Icnt_dispenser* dispenserPtr;
    //Icnt_motion* motionPtr

public:
    cnt_controller();
    virtual void unlock();
    virtual void move_down();
    virtual void move_up();
    virtual void vibrate();
    virtual void turn_on();
    virtual void turn_off();
    virtual void set_dur();
    virtual void set_duration(u_int duration);
    virtual void getArg(String Extarg);

    virtual ~cnt_controller();
};