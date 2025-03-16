PRJSRC = $(wildcard *.cpp *.c)
CFILES = $(filter %.c, $(PRJSRC))
CPPFILES = $(filter %.cpp, $(PRJSRC))
OBJDEP = $(CFILES:.c=.o) $(CPPFILES:.cpp=.o)
TARGET = libprojetInf1900.a
MCU = atmega324pa
INC=
CFLAGS = -I. -I/usr/include/simavr -MMD $(INC) -g -mmcu=$(MCU) -O$(OPTLEVEL) \
	-std=c++14 -fpack-struct -fshort-enums \
	-funsigned-bitfields -funsigned-char \
	-Wall -fno-threadsafe-statics
CXXFLAGS=-fno-exceptions
CC = avr-gcc
CCLIB = avr-ar
all: $(TARGET)

$(TARGET): $(OBJDEP)
	$(CCLIB) crs $(TARGET) $(OBJDEP)

%.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS)

%.o: %.cpp
	$(CC) -c $< -o $@ $(CXXFLAGS) $(CFLAGS)

.PHONY: clean

clean:
	rm -f *.o *.a *.d

