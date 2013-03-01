################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Tp_CPlayerInfo.cpp \
../src/Tp_CRobotMaker.cpp \
../src/Tp_MainProcess.cpp 

C_SRCS += \
../src/Tp_CStandrdIO.c 

OBJS += \
./src/Tp_CPlayerInfo.o \
./src/Tp_CRobotMaker.o \
./src/Tp_CStandrdIO.o \
./src/Tp_MainProcess.o 

C_DEPS += \
./src/Tp_CStandrdIO.d 

CPP_DEPS += \
./src/Tp_CPlayerInfo.d \
./src/Tp_CRobotMaker.d \
./src/Tp_MainProcess.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


