/*
 * Tuxánci 2 - Successor to Tuxánci
 * Copyright (C) 2026  Connor Thomson
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

/**
 * @file watchdog.c
 * @brief Quits out of game and gives backtrace if game freezes
 */

#include <pthread.h>
#include <stdatomic.h>
#include <stdio.h>
#include <stdbool.h>
#include <signal.h>
#include <unistd.h>

#ifdef ENABLE_DEBUG
#   include <backtrace.h>
#endif // ENABLE_DEBUG

#ifndef ENABLE_SERVER
#   include "game/main.h"
#else
#   include "server/main.h"
#endif // ENABLE_SERVER

static _Atomic int watchdogHeartbeat = 0;
static atomic_bool watchdogRunning = true;
static const char *exePath = NULL;
static pthread_t mainThread;

static void sigtrapHandler(int sig) {
    (void)sig;
#ifdef ENABLE_DEBUG
    #ifndef ENABLE_SERVER
        struct backtrace_state *state = backtrace_create_state(exePath, 0, NULL, NULL);
        backtrace_print(state, 1, stderr);
    #endif // ENABLE_SERVER
#else
    fprintf(stderr, "!!!!!!!!! Backtrace disabled !!!!!!!!!\n");
#endif // ENABLE_DEBUG

    fprintf(stderr, "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");

#ifdef ENABLE_DEBUG
    fprintf(stderr, "\n");
#endif // ENABLE_DEBUG    
    mainDestroy();
}

static void *watchdogThread(void *arg) {
    (void)arg;
    int lastHeartbeat = 0;

    while (atomic_load(&watchdogRunning)) {
        usleep(1000000);
        int current = atomic_load(&watchdogHeartbeat);
        if (current == lastHeartbeat) {
#ifndef ENABLE_SERVER
            fprintf(stderr, "\n!!! Tuxánci 2 (client) has crashed !!!\n");
#else
            fprintf(stderr, "\n!!! Tuxánci 2 (server) has crashed !!!\n");
#endif // ENABLE_SERVER
            pthread_kill(mainThread, SIGUSR1);
            break;
        }
        lastHeartbeat = current;
    }
    return NULL;
}

void watchdogInit(const char *argv0) {
    exePath = argv0;
    mainThread = pthread_self();
    signal(SIGUSR1, sigtrapHandler);
    atomic_store(&watchdogHeartbeat, 1);
    pthread_t thread;
    pthread_create(&thread, NULL, watchdogThread, NULL);
    pthread_detach(thread);
}

void watchdogStop(void) {
    atomic_store(&watchdogRunning, false);
}

void watchdogUpdate(void) {
    atomic_fetch_add(&watchdogHeartbeat, 1);
}
