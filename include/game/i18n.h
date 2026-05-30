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
 * @file i18n.h
 * @brief Internationalization
 */

#ifndef I18N_H
#define I18N_H

#include <libintl.h>

/// @brief Mark strings for translation
#define _(String) gettext(String)

/// @brief Mark strings for translation that are not immediately needed
#define N_(String) (String)

void i18nInit(void);

#endif // I18N_H
