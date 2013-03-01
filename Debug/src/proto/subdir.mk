################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/proto/Tp_ProtobufInclude.cpp 

CC_SRCS += \
../src/proto/ProtoTest1.pb.cc \
../src/proto/lm.helloworld.pb.cc 

OBJS += \
./src/proto/ProtoTest1.pb.o \
./src/proto/Tp_ProtobufInclude.o \
./src/proto/lm.helloworld.pb.o 

CC_DEPS += \
./src/proto/ProtoTest1.pb.d \
./src/proto/lm.helloworld.pb.d 

CPP_DEPS += \
./src/proto/Tp_ProtobufInclude.d 


# Each subdirectory must supply rules for building sources it contributes
src/proto/%.o: ../src/proto/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/proto/%.o: ../src/proto/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


