################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../marchingconv/immDates.cpp \
../marchingconv/marchingConv.cpp 

OBJS += \
./marchingconv/immDates.o \
./marchingconv/marchingConv.o 

CPP_DEPS += \
./marchingconv/immDates.d \
./marchingconv/marchingConv.d 


# Each subdirectory must supply rules for building sources it contributes
marchingconv/%.o: ../marchingconv/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


