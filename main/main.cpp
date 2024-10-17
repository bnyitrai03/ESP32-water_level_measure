#include "sdkconfig.h"
#include <iostream>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "main.h"

void HelloCMake::run(int i)
{
    std::cout << "Hello World from C++ "<< i << '\n';
    vTaskDelay(pdMS_TO_TICKS(1000));

}

void run_main(){
    HelloCMake App;
    int i = 0;

    while (true)
    {
        App.run(i);
        i++;
    }    
}

extern "C" void app_main(void)
{
    run_main();
}