################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
LD_SRCS += \
../src/lscript.ld 

CPP_SRCS += \
../src/Candy.cpp \
../src/Enemy.cpp \
../src/GameLogic.cpp \
../src/Player.cpp \
../src/entity.cpp \
../src/main.cpp 

OBJS += \
./src/Candy.o \
./src/Enemy.o \
./src/GameLogic.o \
./src/Player.o \
./src/entity.o \
./src/main.o 

CPP_DEPS += \
./src/Candy.d \
./src/Enemy.d \
./src/GameLogic.d \
./src/Player.d \
./src/entity.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: MicroBlaze g++ compiler'
	mb-g++ -Wall -O0 -g3 -c -fmessage-length=0 -MT"$@" -ID:/Programming/VivadoProjects/FullGame_1/export/FullGame_1/sw/FullGame_1/standalone_domain/bspinclude/include -mlittle-endian -mcpu=v11.0 -mxl-soft-mul -Wl,--no-relax -ffunction-sections -fdata-sections -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


