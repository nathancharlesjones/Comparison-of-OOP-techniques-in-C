# Source files common to all targets.
SRC_FILES := \
	source/main.c \
	source/CaffeinatedBeverage.c \
	source/Coffee.c \
	source/Tea.c

# Generate a list of .o files from the .c files. Prefix them with the build
# folder to output the files there. These variables are recursive because
# the variable BUILD_FOLDER isn't assigned until later in the Makefile.
SRC_OBJ_FILES = $(addprefix $(BUILD_FOLDER)/,$(SRC_FILES:.c=.o))

# List of include dirs. These are put into CFLAGS.
INCLUDE_DIRS := \
    include/

# Set the default compiler
CC := gcc

# The CFLAGS variable below is recursively expanded since the variable
# COMMON_FLAGS isn't defined until later in the Makefile.
CFLAGS = \
	$(COMMON_FLAGS)

# Prefix the include dirs with '-I' when passing them to the compiler
CFLAGS += $(addprefix -I,$(INCLUDE_DIRS))

# Compiler/assembler flags common to all builds and targets. COMMON_FLAGS is recursively
# expanded because it includes the variable for the first prerequisite ($<); the variable
# __FILENAME__ is defined here in order for it to be used by an implementation of assert.
COMMON_FLAGS = \
	-std=c11 \
    -Wall \
    -ffunction-sections \
    -fdata-sections

BUILD_FOLDER := build

# Generate the build tree (list of folders for all output files) based on
# the directory information from the list of objects. "sort" is used to
# remove duplicate files from the resulting list, not necessarily because
# the list needs to be sorted.
BUILD_TREE := $(sort $(dir $(SRC_OBJ_FILES)) $(dir $(ASM_OBJ_FILES)))

mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
current_dir := $(notdir $(patsubst %/,%,$(dir $(mkfile_path))))

# Default all rule will build the target, which here is an executable
all: $(BUILD_FOLDER)/$(current_dir).out
	$(BUILD_FOLDER)/$(current_dir).out

# The rule for building the target executable.
$(BUILD_FOLDER)/$(current_dir).out: $(SRC_OBJ_FILES) | $(BUILD_TREE)
	@echo Linking $(notdir $@)
	$(GCC_PREFIX)$(CC) $(LDFLAGS) $^ $(LDLIB_DIRS) $(LDLIBS) -o $@
	$(GCC_PREFIX)size $@

# The rule for compiling the SRC_FILES into OBJ_FILES
$(BUILD_FOLDER)/%.o: %.c | $(BUILD_TREE)
	@echo Compiling $(notdir $<)
	$(Q) $(GCC_PREFIX)$(CC) $(CFLAGS) -c $< -o $@

# Create the directory structure into which all build artifacts will be placed.
$(BUILD_TREE):
	$(Q) mkdir -p $@

# Since all our generated output is placed into the build folder, our clean rule
# is simple. Prefix the recipe line with '-' to not error if the build folder
# doesn't exist (the -f flag for rm also has this effect)
.PHONY: clean
clean:
	$(Q) $(RM) -r $(BUILD_FOLDER)/