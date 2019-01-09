# This is a generated file. Please do not edit.

.PHONY: all

COMMANDS := 	\
	    scd_cmd_1

all: $(COMMANDS)

scd_cmd_1:
	@echo begin generating scanner info for $@
	g++ -O0 -I "\home\vishist\IRDConnect\include" -E -P -v -dD specs.cpp
	@echo end generating scanner info for $@


