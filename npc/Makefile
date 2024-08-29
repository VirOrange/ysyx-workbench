TOPNAME = top
NXDC_FILES = constr/top.nxdc
INC_PATH ?=

VERILATOR = verilator
VERILATOR_CFLAGS += -MMD -- build -cc \
		    -03 --x assign fast --x initial fast --noassert
BUILD = ./build
OBJ_DIR = $(BUILD_DIR)/$(TOPNAME)

default : $(BIN)

$(shell mkdir -p $(BUILD_DIR))

VSRC = $(wildcard ./vsrc/top.v)
CSRC = $(wildcard ./csrc1/sim_main.cpp)



all:
	@echo "Write this Makefile by your self."

sim:
	$(call git_commit, "sim RTL") # DO NOT REMOVE THIS LINE!!!
	@echo "Write this Makefile by your self."
	verilator -Wno-fatal $(VSRC) $(CSRC) --top-module top --cc --trace --exe
	make -C obj_dir -f Vtop.mk Vtop
	./obj_dir/Vtop

include ../Makefile
include $(NVBOARD_HOME)/scripts/nvboard.mk
 .PHONY:clean
clean:
	rm -rf obj_dir wave.vcd
