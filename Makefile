#######################################
# project specific definitions
MCU=atmega8
TARGET=ch
F_CPU=7372800UL

# application defintions (verbose, debug, etc.)
#DEFINITIONS=-DUART_LOG
#DEFINITIONS=-DUART_ENABLED

#######################################
# libraries to be linked
#LIBRARIES=eeprom uart adc onewire
#LIBRARIES=uart onewire

#######################################
# directories
SRC=src
OBJ=obj

#######################################
# programming ports
PARPORT=/dev/parport0
SERIALPORT=/dev/ttyS0

#######################################
# Compiler flag to set the C Standard level.
# c89   - "ANSI" C
# gnu89 - c89 plus GCC extensions
# c99   - ISO C99 standard (not yet fully implemented)
# gnu99 - c99 plus GCC extensions
CSTANDARD= -std=gnu99

#######################################
# flags
COMMON= -mmcu=$(MCU)
CFLAGS= $(COMMON)
CFLAGS+= -DF_CPU=$(F_CPU)
CFLAGS+= -Wall -Wstrict-prototypes -mcall-prologues
#CFLAGS+= -g
CFLAGS+= -Os
CFLAGS+= $(CSTANDARD)
CFLAGS+= $(DEFINITIONS)

#######################################
# Linker flags
LDFLAGS= $(COMMON)
LDFLAGS+= -Wl,--gc-sections
# workarounds for Gentoo BUG 147155:
# run #ln -s /usr/i686-pc-linux-gnu/avr/lib/ldscripts /usr/avr/lib/ldscripts
# OR
LDFLAGS+= -T /usr/lib/binutils/avr/2.21/ldscripts/avr5.x
#LDFLAGS+= -T /usr/i486-pc-linux-gnu/avr/lib/ldscripts

#######################################
# programs
CC=avr-gcc
OBJCOPY=avr-objcopy
AR=ar
RM=rm
MKDIR=mkdir
SIZEM=avr-size-mcu.sh

#######################################
# Fuses

# Frequency range 3.0 - 8.0 MHz
CKSEL=111
CKOPT=1
# Crystal oscillator, fast rising power
SUT=10

######################################
SOURCES=$(wildcard $(SRC)/*.c)
HEADERS:=$(wildcard $(SRC)/*.h)
OBJECTS=$(patsubst $(SRC)/%,$(OBJ)/%,$(patsubst %.c,%.o,$(wildcard $(SRC)/*.c)))


# rules

all: sizebefore testprint createdir $(TARGET).hex sizeafter

HEXSIZE = $(SIZEM) $(TARGET).hex

sizebefore:
	@if [ -f $(TARGET).hex ]; then echo; echo "Size before:"; $(HEXSIZE); echo; fi

sizeafter:
	@if [ -f $(TARGET).hex ]; then echo; echo "Size after:"; $(HEXSIZE); echo; fi

testprint:
	@echo "SOURCES: $(SOURCES)"
	@echo "HEADERS: $(HEADERS)"
	@echo "OBJECTS: $(OBJECTS)"

createdir:
	$(MKDIR) -p $(OBJ)


.PHONY : $(TARGET)
.PHONY : load
.PHONY : clean
.PHONY : re

$(TARGET): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $(OBJ)/$(TARGET)


# compiles all source files
$(OBJ)/%.o: $(SRC)/%.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@


$(TARGET).hex : $(TARGET)
	$(OBJCOPY) -R .eeprom -O ihex $(OBJ)/$(TARGET) $(TARGET).hex 


load: load_ser
# you need to erase first before loading the program.
# load (program) the software into the flash:
load_par: $(TARGET).hex
	uisp -dlpt=$(PARPORT) --erase  -dprog=dapa
	uisp -dlpt=$(PARPORT) --upload if=$(TARGET).hex -dprog=dapa -v=3 --hash=32

load_ser: $(TARGET).hex
	uisp -dlpt=$(SERIALPORT) --erase  -dprog=dasa
	uisp -dlpt=$(SERIALPORT) --upload if=$(TARGET).hex -dprog=dasa -v=3 --hash=32 --verify


clean:
	$(RM) -rf *.map *.hex $(OBJ)

re: clean all
