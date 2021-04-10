# SERVO is used to define which type of servo we want to build our project with.
SERVO ?=

# Project-specific variables
app_src_dir := \
    source
ifeq ($(SERVO),normal)
app_src_dir += source/servoController
else ifeq ($(SERVO),special)
app_src_dir += source/servoController_special
else
$(error SERVO variable not defined. Options are normal or special.)
endif

inc_dir := \
    include
CFLAGS := -Wall -Wextra

# External variables
TARGET ?= $(lastword $(subst /,$(space),$(shell pwd)))
BUILD_DIR = build

# Functions / "Constant" variables
getfiles = $(foreach DIR,$(1),$(wildcard $(DIR)/*$(2)))
comma:= ,
empty:=
space:= $(empty) $(empty)

# vpaths
vpath %.c $(app_src_dir) $(lib_src_dir)

# Source files
app_src_list := $(call getfiles,$(app_src_dir),.c)

# Object files
app_obj_list := $(addprefix $(BUILD_DIR)/,$(notdir $(app_src_list:.c=.o) ) )

# Include list
inc := $(addprefix -I,$(inc_dir))

# Dependecy lists
DEPFLAGS = -MT $@ -MMD -MP -MF $(BUILD_DIR)/$*.d
app_dep_list := $(app_obj_list:.o=.d)

# Library files
vpath %.d $(BUILD_DIR)

# Verbosity
VERBOSE ?= 1
ifeq ($(VERBOSE),0)
Q = @
else
Q = 
endif

.PHONY: all
all: $(BUILD_DIR)/$(TARGET).out

$(BUILD_DIR)/$(TARGET).out: $(app_obj_list)
	$(Q) $(CC) $(app_obj_list) $(inc) -o $@
	./$@
	
$(BUILD_DIR)/%.o: %.c %.d | $(BUILD_DIR)
	$(Q) $(CC) $(CFLAGS) $(DEPFLAGS) $(inc) -c $< -o $@
	
$(BUILD_DIR):
	$(Q) mkdir -p $@
	
.PHONY: help
help:
	$(info Makefile template for a simple out-of-source build with flattened output (i.e. all output files are placed in a single build folder called TARGET).)
	$(info - Run make or make all to build and run the executable.)
	$(info - Run make clean to remove all object and dependecy files from each of the build folders.)
	$(info - Run make purify to remove entire build folder.)
	$(info - Command line options:)
	$(info -- TARGET: String; Sets the name of the library, executable, and build folder. Default: folder name where this Makefile resides.)
	$(info -- VERBOSE: [0,1]; Setting to 0 quiets the output of make. Default: 1.)
	
.PHONY: print
print:
	@echo TARGET $(TARGET)
	@echo BUILD_DIR $(BUILD_DIR)
	@echo app_src_dir $(app_src_dir)
	@echo app_src_list $(app_src_list)
	@echo app_obj_list $(app_obj_list)
	@echo app_dep_list $(app_dep_list)
	@echo inc $(inc)
	
.PHONY: clean
clean:
	$(Q) $(RM) $(addsuffix *.o, $(shell ls -d build/*/) )
	$(Q) $(RM) $(addsuffix *.d, $(shell ls -d build/*/) )
	
.PHONY: purify
purify: 
	$(Q) $(RM) -r build
	
$(app_dep_list):
	
include $(wildcard $(app_dep_list) )