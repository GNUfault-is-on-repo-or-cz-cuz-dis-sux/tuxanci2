# Coding conventions
This is mainly for C and C header files.

## Indentation
- For braces use One True Brace style.
- For indentation use 4 spaces.
- Please indent switch() statments too.
- Files should end with a `\n`.

## C standard
Always use strict C99 with POSIX extensions are allowed but no GNU extensions.

## File naming
Use "snake_case" for filenames.

## Header ifndef/define's
Always use the filename but in "SCREAMING_SNAKE_CASE".

## Function names
For function names, always use "camelCase".

## Standard library
Never use the libc, only use it if raylib really does not have it. If it is something that would make sense to put in raylib, please make a pull request on the raylib-tuxanci2 repo at https://repo.or.cz/raylib-tuxanci2.git following raylib's coding conventions.

## Comments
Use single line comments and multi-line comments respectively.

## Line length
Every line should be at most 80 character.

## Header
Every C and C header file should start with this
```
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
```
NOTE: Replace my name (Connor Thomson) with yours if you created the file, and replace the year if it is not correct.

## Final notes
Run the `scripts/fixfiles.sh` script to fix some of the things you might miss.

If you get a `bash: ./scripts/fixfiles.sh: Permission denied` error, run
```
chmod +x cripts/fixfiles.sh
```
and run the script again.