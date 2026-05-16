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
 * @file debug.c
 * @brief Debugging menu
 */

#ifdef ENABLE_DEBUG

#include "raylib.h"
#include "button.h"
#include "menu.h"
#include "i18n.h"
#include <stdio.h>

static Button stdout_testBtn;
static Button infloop_testBtn;

static void stdout_test(void) {
    int funnynumber = 42;
    printf("%d\n", funnynumber);
}

static void infloop_test(void) {
    while(1) {}
}

void menuSetupDebug(void) {
    stdout_testBtn = buttonCreate(_("Test stdout"), 130, 100, 130, 30);
    infloop_testBtn = buttonCreate(_("Inf loop test"), 130, 135, 130, 30);
}

void menuDrawDebug(void) {
    menuDraw(_("Debug"));
    
    buttonDraw(&stdout_testBtn);
    buttonDraw(&infloop_testBtn);
}

void menuUpdateDebug(void) {
    if (buttonPressed(&stdout_testBtn))
        stdout_test();

    if (buttonPressed(&infloop_testBtn))
        infloop_test();
}

#endif // ENABLE_DEBUG
