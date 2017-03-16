################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/MassSpringScene.cpp \
../src/PendulumScene.cpp \
../src/PhysicsMass.cpp \
../src/PhysicsObject.cpp \
../src/PhysicsSpring.cpp \
../src/Scene.cpp \
../src/SceneShader.cpp \
../src/Shader.cpp \
../src/main.cpp 

OBJS += \
./src/MassSpringScene.o \
./src/PendulumScene.o \
./src/PhysicsMass.o \
./src/PhysicsObject.o \
./src/PhysicsSpring.o \
./src/Scene.o \
./src/SceneShader.o \
./src/Shader.o \
./src/main.o 

CPP_DEPS += \
./src/MassSpringScene.d \
./src/PendulumScene.d \
./src/PhysicsMass.d \
./src/PhysicsObject.d \
./src/PhysicsSpring.d \
./src/Scene.d \
./src/SceneShader.d \
./src/Shader.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/ugd/bemayer/CPSC587/A3/libraries/trimesh/include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


