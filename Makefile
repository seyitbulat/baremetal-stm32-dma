CC = arm-none-eabi-gcc
MACH = cortex-m4

CFLAGS = -c -mcpu=$(MACH) -mthumb -Wall -O0 -g
LDFLAGS = -nostdlib -T linker.ld -Wl,-Map=program.map
OBJCOPY = arm-none-eabi-objcopy

all: build/program.bin

build/startup.o: src/startup.c
	mkdir -p build
	$(CC) $(CFLAGS) -o build/startup.o src/startup.c


build/main.o: src/main.c
	mkdir -p build
	$(CC) $(CFLAGS) -o build/main.o src/main.c

build/program.elf: build/main.o build/startup.o
	$(CC) $(LDFLAGS) -o build/program.elf build/main.o build/startup.o

build/program.bin: build/program.elf
	$(OBJCOPY) -O binary build/program.elf build/program.bin

clean:
	rm -rf build