.suffix:

override OUTPUT = trm

CC = cc

CFLAGS := -O0 -march=native -mtune=native -fstack-protector -fno-plt -flto -msse4.2 -pipe -ffunction-sections -Isrc/ -std=gnu23 -fPIE -g -pthread -finline-functions -masm=intel
LDFLAGS := -Wl,-O2 -Wl,--as-needed -Wl,--gc-sections -Wl,-z,relro,-z,now -g -flto -pthread


override SRCFILES := $(shell find -L src/ -type f 2>/dev/null | LC_ALL=C sort)
override CFILES := $(filter %.c,$(SRCFILES))

override OBJ := $(addprefix obj/,$(CFILES:.c=.c.o))
override HEADER_DEPS := $(addprefix obj/,$(CFILES:.c=.c.d))

.PHONY: all 
all: bin/$(OUTPUT)

bin/$(OUTPUT): GNUmakefile $(OBJ)
		mkdir -p "$(dir $@)"
		$(CC) $(LDFLAGS) $(OBJ) -o $@

obj/%.c.o: %.c GNUmakefile
		mkdir -p "$(dir $@)"
		$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
		rm -rf obj bin
