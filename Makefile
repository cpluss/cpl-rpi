# Build script of the kernel, mostly incorporated from RPI C Tutorial
# at osdev wiki

# build environment
PREFIX ?= $(HOME)/.yagarto
ARM    ?= $(PREFIX)/bin/arm-none-eabi

# source files
SRC_ASM := $(wildcard src/*.S)
SRC_C   := $(wildcard src/*.c)
# their (future) object-files
OBJS    := $(patsubst %.S,%.o,$(SRC_ASM))
OBJS    += $(patsubst %.c,%.o,$(SRC_C))
OBJS    := $(patsubst src/%,bin/objs/%,$(OBJS))

# build flags
DEPENDFLAGS := -MD -MP
INCLUDES    := -I src
BASEFLAGS   := -O2 -fpic -pedantic -pedantic-errors -nostdlib
BASEFLAGS   += -nostartfiles -ffreestanding -nodefaultlibs
BASEFLAGS   += -fno-builtin -fomit-frame-pointer -mcpu=arm1176jzf-s
WARNFLAGS   := -Wall -Wextra -Wshadow -Wcast-align -Wwrite-strings
WARNFLAGS   += -Wredundant-decls -Winline
WARNFLAGS   += -Wno-attributes -Wno-deprecated-declarations
WARNFLAGS   += -Wno-div-by-zero -Wno-endif-labels -Wfloat-equal
WARNFLAGS   += -Wformat=2 -Wno-format-extra-args -Winit-self
WARNFLAGS   += -Winvalid-pch -Wmissing-format-attribute
WARNFLAGS   += -Wmissing-include-dirs -Wno-multichar
WARNFLAGS   += -Wredundant-decls -Wshadow
WARNFLAGS   += -Wno-sign-compare -Wswitch -Wsystem-headers -Wundef
WARNFLAGS   += -Wno-pragmas -Wno-unused-but-set-parameter
WARNFLAGS   += -Wno-unused-but-set-variable -Wno-unused-result
WARNFLAGS   += -Wwrite-strings -Wdisabled-optimization -Wpointer-arith
WARNFLAGS   += -Werror
ASFLAGS     := $(INCLUDES) $(DEPENDFLAGS) -D__ASSEMBLY__
CFLAGS      := $(INCLUDES) $(DEPENDFLAGS) $(BASEFLAGS) #$(WARNFLAGS)
CFLAGS      += -std=gnu99

# build rules
.PHONY: all clean directories

all: bin/kernel.img

bin/kernel.elf: $(OBJS) link-arm-eabi.ld
	@echo Linking kernel.elf
	@$(ARM)-ld $(OBJS) -Tlink-arm-eabi.ld -o $@

bin/kernel.img: bin/kernel.elf
	@echo Linking kernel.img
	@$(ARM)-objcopy bin/kernel.elf -O binary bin/kernel.img

# clean binaries
clean:
	@echo Cleaning ...
	@rm -rf bin
	@mkdir -p bin/objs

# create directories needed to compile
directories:
	@echo Creating directories ...
	@mkdir -p bin/objs

# C compile
bin/objs/%.o: src/%.c Makefile
	@echo CC $<
	$(ARM)-gcc $(CFLAGS) -c $< -o $@

# Assembly compile
bin/objs/%.o: src/%.S Makefile
	@echo AS $<
	@$(ARM)-gcc $(ASFLAGS) -c $< -o $@
