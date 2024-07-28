#!/bin/bash

g++ -Iinclude src/main.cpp -lsfml-graphics -lsfml-system -lsfml-window -o out

# Check if the compilation was successful
if [ $? -eq 0 ]; then
    echo "Compilation successful. Running the binary..."
    ./out
else
    echo "Compilation failed. Not running the binary."
fi