################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: genSchedule

dependents:
	-cd F:/git/risk-engine/IRDConnect/tradeticket/Debug && $(MAKE) clean all
	-cd F:/git/risk-engine/IRDConnect/dataformat/Debug && $(MAKE) clean all
	-cd F:/git/risk-engine/IRDConnect/date/Debug && $(MAKE) clean all
	-cd F:/git/risk-engine/IRDConnect/errors/Debug && $(MAKE) clean all
	-cd F:/git/risk-engine/IRDConnect/string/Debug && $(MAKE) clean all

# Tool invocations
genSchedule: $(OBJS) $(USER_OBJS) F:/git/risk-engine/IRDConnect/tradeticket/Debug/libtradeticket.so F:/git/risk-engine/IRDConnect/dataformat/Debug/libdataformat.so F:/git/risk-engine/IRDConnect/date/Debug/libdate.so F:/git/risk-engine/IRDConnect/errors/Debug/liberrors.so F:/git/risk-engine/IRDConnect/string/Debug/libstring.so
	@echo 'Building target: $@'
	@echo 'Invoking: GCC C++ Linker'
	g++ -L/home/vishist/IRDConnect/lib -L/usr/lib -o"genSchedule" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(CC_DEPS)$(C++_DEPS)$(EXECUTABLES)$(C_UPPER_DEPS)$(CXX_DEPS)$(OBJS)$(CPP_DEPS)$(C_DEPS) genSchedule
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:
F:/git/risk-engine/IRDConnect/tradeticket/Debug/libtradeticket.so:
F:/git/risk-engine/IRDConnect/dataformat/Debug/libdataformat.so:
F:/git/risk-engine/IRDConnect/date/Debug/libdate.so:
F:/git/risk-engine/IRDConnect/errors/Debug/liberrors.so:
F:/git/risk-engine/IRDConnect/string/Debug/libstring.so:

-include ../makefile.targets
