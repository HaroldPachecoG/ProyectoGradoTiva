################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
%.obj: ../%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccs1011/ccs/tools/compiler/ti-cgt-arm_20.2.3.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="C:/Users/HAROLD/workspace_v10/httpgetCC3100_EK_TM4C129EXL_TI" --include_path="C:/ti/tirtos_tivac_2_16_00_08/products/tidrivers_tivac_2_16_00_08/packages/ti/mw/wifi/cc3x00" --include_path="C:/ti/tirtos_tivac_2_16_00_08/products/tidrivers_tivac_2_16_00_08/packages/ti/mw/wifi/cc3x00/oslib" --include_path="C:/ti/tirtos_tivac_2_16_00_08/products/tidrivers_tivac_2_16_00_08/packages/ti/mw/wifi/cc3x00/simplelink/include" --include_path="C:/Users/HAROLD/workspace_v10/httpgetCC3100_EK_TM4C129EXL_TI" --include_path="C:/ti/tirtos_tivac_2_16_00_08/products/TivaWare_C_Series-2.1.1.71b" --include_path="C:/ti/tirtos_tivac_2_16_00_08/products/bios_6_45_01_29/packages/ti/sysbios/posix" --include_path="C:/ti/ccs1011/ccs/tools/compiler/ti-cgt-arm_20.2.3.LTS/include" --define=ccs="ccs" --define=PART_TM4C129ENCPDT --define=NET_SL --define=ccs --define=TIVAWARE -g --gcc --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --abi=eabi --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

build-1141729215:
	@$(MAKE) --no-print-directory -Onone -f subdir_rules.mk build-1141729215-inproc

build-1141729215-inproc: ../httpgetCC3100.cfg
	@echo 'Building file: "$<"'
	@echo 'Invoking: XDCtools'
	"C:/ti/xdctools_3_32_00_06_core/xs" --xdcpath="C:/ti/tirtos_tivac_2_16_00_08/packages;C:/ti/tirtos_tivac_2_16_00_08/products/tidrivers_tivac_2_16_00_08/packages;C:/ti/tirtos_tivac_2_16_00_08/products/bios_6_45_01_29/packages;C:/ti/tirtos_tivac_2_16_00_08/products/ndk_2_25_00_09/packages;C:/ti/tirtos_tivac_2_16_00_08/products/uia_2_00_05_50/packages;C:/ti/tirtos_tivac_2_16_00_08/products/ns_1_11_00_10/packages;" xdc.tools.configuro -o configPkg -t ti.targets.arm.elf.M4F -p ti.platforms.tiva:TM4C129ENCPDT -r release -c "C:/ti/ccs1011/ccs/tools/compiler/ti-cgt-arm_20.2.3.LTS" --compileOptions "-mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path=\"C:/Users/HAROLD/workspace_v10/httpgetCC3100_EK_TM4C129EXL_TI\" --include_path=\"C:/ti/tirtos_tivac_2_16_00_08/products/tidrivers_tivac_2_16_00_08/packages/ti/mw/wifi/cc3x00\" --include_path=\"C:/ti/tirtos_tivac_2_16_00_08/products/tidrivers_tivac_2_16_00_08/packages/ti/mw/wifi/cc3x00/oslib\" --include_path=\"C:/ti/tirtos_tivac_2_16_00_08/products/tidrivers_tivac_2_16_00_08/packages/ti/mw/wifi/cc3x00/simplelink/include\" --include_path=\"C:/Users/HAROLD/workspace_v10/httpgetCC3100_EK_TM4C129EXL_TI\" --include_path=\"C:/ti/tirtos_tivac_2_16_00_08/products/TivaWare_C_Series-2.1.1.71b\" --include_path=\"C:/ti/tirtos_tivac_2_16_00_08/products/bios_6_45_01_29/packages/ti/sysbios/posix\" --include_path=\"C:/ti/ccs1011/ccs/tools/compiler/ti-cgt-arm_20.2.3.LTS/include\" --define=ccs=\"ccs\" --define=PART_TM4C129ENCPDT --define=NET_SL --define=ccs --define=TIVAWARE -g --gcc --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --abi=eabi  " "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

configPkg/linker.cmd: build-1141729215 ../httpgetCC3100.cfg
configPkg/compiler.opt: build-1141729215
configPkg/: build-1141729215


