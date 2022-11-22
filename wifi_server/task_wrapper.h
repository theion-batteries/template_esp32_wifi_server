#pragma once
#include <Arduino.h>

class TaskBase {
public:
  xTaskHandle handle;
  ~TaskBase() {
#if INCLUDE_vTaskDelete
    vTaskDelete(handle);
#endif
    return;
  }
};
class Task : public TaskBase {
public:
  Task(char const*name, void (*taskfun)(void *), unsigned portBASE_TYPE priority,
       unsigned portSHORT stackDepth=configMINIMAL_STACK_SIZE) {
    xTaskCreate(taskfun, (signed char*)name, stackDepth, this, priority, &handle);
  }
};
class TaskClass : public TaskBase {
public:
  TaskClass(char const*name, unsigned portBASE_TYPE priority,
           unsigned portSHORT stackDepth=configMINIMAL_STACK_SIZE) {
    xTaskCreate(&taskfun, (signed char*)name, stackDepth, this, priority, &handle);
  }
  virtual void task() = 0;
  static void taskfun(void* parm) {
    static_cast<TaskClass *>(parm)->task();
#if INCLUDE_vTaskDelete
    xTaskDelete(handle);
#else
    while(1)
      vTaskDelay(10000);
#endif
  }
};
