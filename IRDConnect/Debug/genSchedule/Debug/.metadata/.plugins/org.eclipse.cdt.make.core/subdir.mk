################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../genSchedule/Debug/.metadata/.plugins/org.eclipse.cdt.make.core/specs.cpp 

C_SRCS += \
../genSchedule/Debug/.metadata/.plugins/org.eclipse.cdt.make.core/specs.c 

OBJS += \
./genSchedule/Debug/.metadata/.plugins/org.eclipse.cdt.make.core/specs.o 

C_DEPS += \
./genSchedule/Debug/.metadata/.plugins/org.eclipse.cdt.make.core/specs.d 

CPP_DEPS += \
./genSchedule/Debug/.metadata/.plugins/org.eclipse.cdt.make.core/specs.d 


# Each subdirectory must supply rules for building sources it contributes
genSchedule/Debug/.metadata/.plugins/org.eclipse.cdt.make.core/%.o: ../genSchedule/Debug/.metadata/.plugins/org.eclipse.cdt.make.core/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

genSchedule/Debug/.metadata/.plugins/org.eclipse.cdt.make.core/%.o: ../genSchedule/Debug/.metadata/.plugins/org.eclipse.cdt.make.core/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


