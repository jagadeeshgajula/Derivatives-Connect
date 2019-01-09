################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include weekday/subdir.mk
-include weekday/Debug/subdir.mk
-include vol/Debug/subdir.mk
-include vol/subdir.mk
-include util/subdir.mk
-include util/Debug/subdir.mk
-include tradeticket/subdir.mk
-include tradeticket/Debug/subdir.mk
-include timeunit/subdir.mk
-include timeunit/Debug/subdir.mk
-include string/subdir.mk
-include string/Debug/subdir.mk
-include roundingconv/subdir.mk
-include roundingconv/Debug/subdir.mk
-include rolldayconv/subdir.mk
-include rolldayconv/Debug/subdir.mk
-include period/subdir.mk
-include period/Debug/subdir.mk
-include moneymkt/subdir.mk
-include moneymkt/Debug/subdir.mk
-include money/subdir.mk
-include money/Debug/subdir.mk
-include marchingconv/subdir.mk
-include marchingconv/Debug/subdir.mk
-include include/subdir.mk
-include genSchedule/subdir.mk
-include genSchedule/Debug/subdir.mk
-include genSchedule/Debug/.metadata/.plugins/org.eclipse.cdt.make.core/subdir.mk
-include frequency/subdir.mk
-include frequency/Debug/subdir.mk
-include errors/subdir.mk
-include errors/Debug/subdir.mk
-include daycountconv/subdir.mk
-include daycountconv/Debug/subdir.mk
-include date/subdir.mk
-include date/Debug/subdir.mk
-include dataformat/subdir.mk
-include dataformat/Debug/subdir.mk
-include curve/subdir.mk
-include curve/Debug/subdir.mk
-include currency/subdir.mk
-include currency/Debug/subdir.mk
-include calendar/subdir.mk
-include calendar/Debug/subdir.mk
-include busdayconv/subdir.mk
-include busdayconv/Debug/subdir.mk
-include .metadata/.plugins/org.eclipse.cdt.make.core/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: IRDConnect

# Tool invocations
IRDConnect: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: GCC C++ Linker'
	g++  -o"IRDConnect" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(C++_DEPS)$(C_DEPS)$(CC_DEPS)$(CPP_DEPS)$(EXECUTABLES)$(CXX_DEPS)$(C_UPPER_DEPS) IRDConnect
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
