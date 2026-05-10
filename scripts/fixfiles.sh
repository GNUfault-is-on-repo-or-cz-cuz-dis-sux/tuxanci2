#!/bin/sh

TARGETS="src/* include/*"

# Go into the project's root directory
SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
cd "$SCRIPT_DIR/.." || exit 1

# Switch source files from DOS to UNIX format
dos2unix $TARGETS

# Now add a newline to all source files if they do not have it
for f in $TARGETS; do
    # Skip non-files
    [ -f "$f" ] || continue

    # Check if a file ends with a newline
    if [ -n "$(tail -c1 "$f")" ]; then
        # If not then add it
        echo >> "$f"
        echo "Added newline to: $f"
    else
        echo "$f already had a newline"
    fi
done

# Fix indentation
for f in $TARGETS; do
    [ -f "$f" ] || continue
    clang-format -i --style="{BasedOnStyle: llvm, IndentWidth: 4, ColumnLimit: 80, PointerAlignment: Left}" "$f"
    echo "Fixed indentation in $f"
done