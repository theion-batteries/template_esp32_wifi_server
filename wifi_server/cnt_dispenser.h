/**
 * @file cnt_dispenser.h
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2022-09-28
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once
#include "Configs.h"
#include "th_dac_mcp4922.h"
#include "th_sin_wave_dac.h"
#include "firm_vibration_control_module.h"

 /************ Interface cnt dispense **********/

class Icnt_dispenser
{

public:
    Icnt_dispenser() = default;
    virtual void vibrate() = 0;
    virtual void turn_on() = 0;
    virtual void turn_off() = 0;
    virtual void set_duration(u_int duration) = 0;
    virtual ~Icnt_dispenser() = default;
};

class cnt_dispenser : public Icnt_dispenser
{
private:
    Dac_mcp4922 dac_obj;
    Sin_wave_dac sin_obj;

public:
    cnt_dispenser();
    virtual void vibrate();
    virtual void turn_on();
    virtual void turn_off();
    virtual void set_duration(u_int duration);
    virtual ~cnt_dispenser() = default;
};
