/**
 * @file cnt_dispenser.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2022-09-28
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "cnt_dispenser.h"

cnt_dispenser::cnt_dispenser()
{
   Serial.println("creating cnt dispenser interface");

   dac_obj = Dac_mcp4922(0, CS_C, SCK_C, MOSI_C, EN_C, LATCH_C, EN_ACTIVE_C, LATCH_ACTIVE_C);
   sin_obj = Sin_wave_dac(&dac_obj, 100, 10);
}

void cnt_dispenser::vibrate()
{
   Serial.println("sin output requested");
   sin_obj.sin_output();
}

void cnt_dispenser::turn_on()
{
   Serial.print("dac turning on");
   sin_obj.dac_enable();
}
void cnt_dispenser::turn_off()
{
   sin_obj.dac_disable();

}
void cnt_dispenser::set_duration(u_int duration)
{
   Serial.println("setting duration  to: ");
   Serial.println(duration);
   sin_obj.set_duration(duration);
}