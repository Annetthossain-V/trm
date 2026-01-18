.suffix:

override OUTPUT = trm

CXX = g++
LD = ld

CXXFLAGS := -O0 -march=native -mtune=native -fstack-protector -fno-plt -flto -msse4.2 -pipe -ffunction-sections -Isrc/ -std=c++23 -fPIE -g -pthread -finline-functions -fstack-check -fdata-sections
LDFLAGS := -Wl,-O2 -Wl,--as-needed -Wl,--gc-sections -Wl,-z,relro,-z,now -g -flto -pthread #


override SRCFILES := $(shell find -L src/ -type f 2>/dev/null | LC_ALL=C sort)
override CXXFILES := $(filter %.cc,$(SRCFILES))

override OBJ := $(addprefix target/obj/,$(CXXFILES:.cc=.cc.o))
override HEADER_DEPS := $(addprefix target/obj/,$(CFILES:.cc=.cc.d))

.PHONY: all
all: target/bin/$(OUTPUT)

target/bin/$(OUTPUT): GNUmakefile $(OBJ)
		mkdir -p "$(dir $@)"
		$(CXX) $(LDFLAGS) $(OBJ) -o $(OUTPUT)

target/obj/%.cc.o: %.cc GNUmakefile
		mkdir -p "$(dir $@)"
		$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY: clean
clean:
		rm -rf obj bin target
