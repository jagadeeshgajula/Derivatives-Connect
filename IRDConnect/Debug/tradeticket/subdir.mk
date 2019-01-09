################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../tradeticket/SwapTicket.cpp \
../tradeticket/additionalPayments.cpp \
../tradeticket/amortSchedule.cpp \
../tradeticket/assetSwaps.cpp \
../tradeticket/bond.cpp \
../tradeticket/bondFuture.cpp \
../tradeticket/bondFutureOption.cpp \
../tradeticket/capFloorTicket.cpp \
../tradeticket/compSchedule.cpp \
../tradeticket/externalSystemTrades.cpp \
../tradeticket/fXReset.cpp \
../tradeticket/fixingRates.cpp \
../tradeticket/fraTicket.cpp \
../tradeticket/mmFuture.cpp \
../tradeticket/mmFutureOption.cpp \
../tradeticket/optionSchedule.cpp \
../tradeticket/paySchedule.cpp \
../tradeticket/premiums.cpp \
../tradeticket/resetSchedule.cpp \
../tradeticket/revalRates.cpp \
../tradeticket/rightToTerminate.cpp \
../tradeticket/salesCredit.cpp \
../tradeticket/stubResets.cpp \
../tradeticket/swapLeg.cpp \
../tradeticket/swapOption.cpp \
../tradeticket/tradeMargin.cpp \
../tradeticket/tradeModificationReasons.cpp \
../tradeticket/tradeTicket.cpp 

OBJS += \
./tradeticket/SwapTicket.o \
./tradeticket/additionalPayments.o \
./tradeticket/amortSchedule.o \
./tradeticket/assetSwaps.o \
./tradeticket/bond.o \
./tradeticket/bondFuture.o \
./tradeticket/bondFutureOption.o \
./tradeticket/capFloorTicket.o \
./tradeticket/compSchedule.o \
./tradeticket/externalSystemTrades.o \
./tradeticket/fXReset.o \
./tradeticket/fixingRates.o \
./tradeticket/fraTicket.o \
./tradeticket/mmFuture.o \
./tradeticket/mmFutureOption.o \
./tradeticket/optionSchedule.o \
./tradeticket/paySchedule.o \
./tradeticket/premiums.o \
./tradeticket/resetSchedule.o \
./tradeticket/revalRates.o \
./tradeticket/rightToTerminate.o \
./tradeticket/salesCredit.o \
./tradeticket/stubResets.o \
./tradeticket/swapLeg.o \
./tradeticket/swapOption.o \
./tradeticket/tradeMargin.o \
./tradeticket/tradeModificationReasons.o \
./tradeticket/tradeTicket.o 

CPP_DEPS += \
./tradeticket/SwapTicket.d \
./tradeticket/additionalPayments.d \
./tradeticket/amortSchedule.d \
./tradeticket/assetSwaps.d \
./tradeticket/bond.d \
./tradeticket/bondFuture.d \
./tradeticket/bondFutureOption.d \
./tradeticket/capFloorTicket.d \
./tradeticket/compSchedule.d \
./tradeticket/externalSystemTrades.d \
./tradeticket/fXReset.d \
./tradeticket/fixingRates.d \
./tradeticket/fraTicket.d \
./tradeticket/mmFuture.d \
./tradeticket/mmFutureOption.d \
./tradeticket/optionSchedule.d \
./tradeticket/paySchedule.d \
./tradeticket/premiums.d \
./tradeticket/resetSchedule.d \
./tradeticket/revalRates.d \
./tradeticket/rightToTerminate.d \
./tradeticket/salesCredit.d \
./tradeticket/stubResets.d \
./tradeticket/swapLeg.d \
./tradeticket/swapOption.d \
./tradeticket/tradeMargin.d \
./tradeticket/tradeModificationReasons.d \
./tradeticket/tradeTicket.d 


# Each subdirectory must supply rules for building sources it contributes
tradeticket/%.o: ../tradeticket/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


