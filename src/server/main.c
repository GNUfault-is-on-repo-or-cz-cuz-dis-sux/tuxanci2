#include "core/arguments.h"
#include "core/watchdog.h"
#include <stdlib.h>

static void mainInit(const char *argv1) {
    watchdogInit(argv1);
}

static void mainUpdate(void) {
    watchdogUpdate();
    for(;;);
}

void mainDestroy(void) {
    exit(0);
}

int main(int argc, char *argv[]) {
    mainInit(argv[1]);
    
    while(1) {
        mainUpdate();
    }
}
