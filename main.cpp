#include <iostream>
#include "start_screen.h"
#include "app_container.h"

int main() {
    App_Container container;
    Start_Screen startScreen(&container);
    return 0;
}
