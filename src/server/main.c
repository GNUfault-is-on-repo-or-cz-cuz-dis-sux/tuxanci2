#include "core/arguments.h"
#include "core/watchdog.h"
#include "core/server.h"
#include <stdlib.h>

static void mainInit(const char *argv1) {
    watchdogInit(argv1);
    serverInit(2201);
}

static void mainUpdate(void) {
    watchdogUpdate();
    serverUpdate();
}

void mainDestroy(void) {
    serverDestroy();
    exit(0);
}

int main(int argc, char *argv[]) {
    mainInit(argv[1]);
    
    while(1) {
        mainUpdate();
    }
}
