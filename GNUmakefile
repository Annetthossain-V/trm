.suffix:

override OUTPUT = trm

CXX = g++

CXXFLAGS := -O0 -march=native -mtune=native -fstack-protector -fno-plt -flto -msse4.2 -pipe -ffunction-sections -Isrc/ -std=gnu++23 -fPIE -g -pthread -finline-functions
LDFLAGS := -Wl,-O2 -Wl,--as-needed -Wl,--gc-sections -Wl,-z,relro,-z,now -g -flto -pthread


override SRCFILES := $(shell find -L src/ -type f 2>/dev/null | LC_ALL=C sort)
override CXXFILES := $(filter %.cxx,$(SRCFILES))

override OBJ := $(addprefix target/obj/,$(CXXFILES:.cxx=.cxx.o))
override HEADER_DEPS := $(addprefix target/obj/,$(CFILES:.cxx=.cxx.d))

.PHONY: all
all: target/bin/$(OUTPUT)

target/bin/$(OUTPUT): GNUmakefile $(OBJ)
		mkdir -p "$(dir $@)"
		$(CC) $(LDFLAGS) $(OBJ) -o $@

target/obj/%.cxx.o: %.cxx GNUmakefile
		mkdir -p "$(dir $@)"
		$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY: clean
clean:
		rm -rf obj bin target
