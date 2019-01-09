################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../moneymkt/instrumentClassCd.cpp \
../moneymkt/intrumentTypeCd.cpp \
../moneymkt/moneyMkt.cpp 

OBJS += \
./moneymkt/instrumentClassCd.o \
./moneymkt/intrumentTypeCd.o \
./moneymkt/moneyMkt.o 

CPP_DEPS += \
./moneymkt/instrumentClassCd.d \
./moneymkt/intrumentTypeCd.d \
./moneymkt/moneyMkt.d 


# Each subdirectory must supply rules for building sources it contributes
moneymkt/%.o: ../moneymkt/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


