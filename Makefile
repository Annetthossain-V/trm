.suffix:

override OUTPUT = trm

CXX = g++

CXXFLAGS := -O0 -march=native -mtune=native -fstack-protector -fno-plt -flto -msse4.2 -pipe -ffunction-sections -std=c++23 -fPIE -g -pthread -finline-functions -fstack-check -fdata-sections
LDFLAGS := -Wl,-O2 -Wl,--as-needed -Wl,--gc-sections -Wl,-z,relro,-z,now -g -flto -pthread #


override SRCFILES := $(shell find -L src/ -type f 2>/dev/null | LC_ALL=C sort)
override CXXFILES := $(filter %.cc,$(SRCFILES))

override OBJ := $(addprefix target/obj/,$(CXXFILES:.cc=.cc.o))
override HEADER_DEPS := $(addprefix target/obj/,$(CFILES:.cc=.cc.d))

.PHONY: all
all: target/bin/$(OUTPUT)

target/bin/$(OUTPUT): Makefile $(OBJ)
		mkdir -p "$(dir $@)"
		$(CXX) $(LDFLAGS) $(OBJ) -o target/bin/$(OUTPUT)

target/obj/%.cc.o: %.cc Makefile
		mkdir -p "$(dir $@)"
		$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY: clean
clean:
		rm -rf obj bin target
