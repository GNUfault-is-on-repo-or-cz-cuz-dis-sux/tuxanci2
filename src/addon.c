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

#include <gtk/gtk.h>
#include <lauxlib.h>
#include <lua.h>
#include <lualib.h>
#include <threads.h>
#include <stdlib.h>
#include <string.h>

/// @brief Structure to pass data to our Lua thread
typedef struct {
    char* filename;
} LuaThreadArgs;

/// @brief Worker function for the Lua thread
int run_lua_script(void* data) {
    LuaThreadArgs* args = (LuaThreadArgs*)data;
    
    if (args->filename == NULL) {
        free(args);
        return -1;
    }

    lua_State* L = luaL_newstate();
    luaL_openlibs(L);

    if (luaL_dofile(L, args->filename) != LUA_OK) {
        const char* error = lua_tostring(L, -1);
        fprintf(stderr, "Lua Error: %s\n", error);
    }

    lua_close(L);
    
    g_free(args->filename);
    free(args);
    return 0;
}

/// @brief Init addon system
void addonInit(void) {
    gtk_init_check(NULL, NULL);
}

/// @brief Open add-on picker
void addonPick(void) {
    GtkWidget* dialog;
    GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_OPEN;

    dialog = gtk_file_chooser_dialog_new("Open Add-on", NULL, action, 
                                         "_Cancel", GTK_RESPONSE_CANCEL, 
                                         "_Open", GTK_RESPONSE_ACCEPT, NULL);

    GtkFileFilter* filter = gtk_file_filter_new();
    gtk_file_filter_set_name(filter, "Lua scripts");
    gtk_file_filter_add_pattern(filter, "*.lua");
    gtk_file_chooser_add_filter(GTK_FILE_CHOOSER(dialog), filter);

    if (gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT) {
        char* filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));

        LuaThreadArgs* args = malloc(sizeof(LuaThreadArgs));
        args->filename = filename;

        thrd_t thread_id;
        if (thrd_create(&thread_id, run_lua_script, args) == thrd_success) {
            thrd_detach(thread_id);
        } else {
            g_free(filename);
            free(args);
        }
    }

    gtk_widget_destroy(dialog);

    while (gtk_events_pending()) {
        gtk_main_iteration();
    }
}