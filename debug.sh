#!/bin/env bash

make clean; make DEBUG=1
openocd -f interface/stlink-dap.cfg -f target/stm8s003.cfg -c "init" -c "reset halt" &
stm8-gdb output/respirator.elf --tui --ex "start"
pkill openocd
