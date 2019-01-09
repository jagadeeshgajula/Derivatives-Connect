# This is a generated file. Please do not edit.

.PHONY: all

COMMANDS := 	\
	    scd_cmd_2

all: $(COMMANDS)

scd_cmd_2:
	@echo begin generating scanner info for $@
	g++ -O0 -I "F:\home\vishist\IRDConnect\include" -E -P -v -dD specs.cpp
	@echo end generating scanner info for $@


