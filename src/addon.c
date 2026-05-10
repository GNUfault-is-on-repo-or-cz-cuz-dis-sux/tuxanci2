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
 * @file lua.c
 * @brief Add-on system
 */

#include "files.h"
#include "raylib.h"
#include <gtk/gtk.h>
#include <lauxlib.h>
#include <lua.h>
#include <lualib.h>

/** @brief Init addon system */
void addonInit(void) {
    // GTK init
    gtk_init_check(NULL, NULL);
}

/** @brief Open add-on picker */
void addonPick(void) {
    // Lua init
    lua_State* L = luaL_newstate();
    luaL_openlibs(L);

    // lua_register(L, "functioninlua", functioninc);

    GtkWidget* dialog;
    GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_OPEN;
    char* filename = NULL;

    dialog = gtk_file_chooser_dialog_new("Open Add-on", NULL, action, "_Cancel",
                                         GTK_RESPONSE_CANCEL, "_Open",
                                         GTK_RESPONSE_ACCEPT, NULL);

    // Filter
    GtkFileFilter* filter = gtk_file_filter_new();
    gtk_file_filter_set_name(filter, "Lua scripts");
    gtk_file_filter_add_pattern(filter, "*.lua");
    gtk_file_chooser_add_filter(GTK_FILE_CHOOSER(dialog), filter);

    // Open the window
    if (gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT) {
        filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
    }

    // Destroy it
    gtk_widget_destroy(dialog);

    // Flush events
    while (gtk_events_pending()) {
        gtk_main_iteration();
    }

    // Run it
    luaL_dofile(L, filename);

    // Close it
    lua_close(L);
}
