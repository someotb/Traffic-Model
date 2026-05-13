#!/bin/bash
cd cpp/build && cmake .. && cmake --build . -j &&
./main config.txt && clear && cd ../../python && python main.py
