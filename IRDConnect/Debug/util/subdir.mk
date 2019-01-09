################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../util/irdXML.cpp \
../util/util.cpp 

OBJS += \
./util/irdXML.o \
./util/util.o 

CPP_DEPS += \
./util/irdXML.d \
./util/util.d 


# Each subdirectory must supply rules for building sources it contributes
util/%.o: ../util/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


