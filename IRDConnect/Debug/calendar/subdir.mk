################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../calendar/calendar.cpp \
../calendar/calendarUtil.cpp \
../calendar/compositeCalendar.cpp \
../calendar/simpleCalendar.cpp 

OBJS += \
./calendar/calendar.o \
./calendar/calendarUtil.o \
./calendar/compositeCalendar.o \
./calendar/simpleCalendar.o 

CPP_DEPS += \
./calendar/calendar.d \
./calendar/calendarUtil.d \
./calendar/compositeCalendar.d \
./calendar/simpleCalendar.d 


# Each subdirectory must supply rules for building sources it contributes
calendar/%.o: ../calendar/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


