################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Add inputs and outputs from these tool invocations to the build variables 
CFG_SRCS += \
../httpgetCC3100.cfg 

CMD_SRCS += \
../EK_TM4C129EXL.cmd 

C_SRCS += \
../EK_TM4C129EXL.c \
../httpgetCC3100.c \
../sockets.c 

GEN_CMDS += \
./configPkg/linker.cmd 

GEN_FILES += \
./configPkg/linker.cmd \
./configPkg/compiler.opt 

GEN_MISC_DIRS += \
./configPkg/ 

C_DEPS += \
./EK_TM4C129EXL.d \
./httpgetCC3100.d \
./sockets.d 

GEN_OPTS += \
./configPkg/compiler.opt 

OBJS += \
./EK_TM4C129EXL.obj \
./httpgetCC3100.obj \
./sockets.obj 

GEN_MISC_DIRS__QUOTED += \
"configPkg\" 

OBJS__QUOTED += \
"EK_TM4C129EXL.obj" \
"httpgetCC3100.obj" \
"sockets.obj" 

C_DEPS__QUOTED += \
"EK_TM4C129EXL.d" \
"httpgetCC3100.d" \
"sockets.d" 

GEN_FILES__QUOTED += \
"configPkg\linker.cmd" \
"configPkg\compiler.opt" 

C_SRCS__QUOTED += \
"../EK_TM4C129EXL.c" \
"../httpgetCC3100.c" \
"../sockets.c" 


