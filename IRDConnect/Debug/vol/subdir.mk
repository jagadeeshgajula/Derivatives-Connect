################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../vol/BlackPricer.cpp 

OBJS += \
./vol/BlackPricer.o 

CPP_DEPS += \
./vol/BlackPricer.d 


# Each subdirectory must supply rules for building sources it contributes
vol/%.o: ../vol/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


