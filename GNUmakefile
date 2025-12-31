.suffix:

override OUTPUT = trm

CXX = c++
CXXFLAG := -O0 -march=native -mtune=native -fstack-protector -fno-plt -flto -msse4.2 -pipe -ffunction-sections -I/home/annetthossain/include/ -Isrc/ -std=c++23 -fPIE -g
LDFLAG := -flto  -Wl,-O2 -Wl,--as-needed -Wl,--gc-sections -Wl,-z,relro,-z,now -g


override SRCFILES := $(shell find -L src/ -type f 2>/dev/null | LC_ALL=C sort)
override CXXFILES := $(filter %.cxx,$(SRCFILES))

override OBJ := $(addprefix obj/,$(CXXFILES:.cxx=.cxx.o))
override HEADER_DEPS := $(addprefix obj/,$(CXXFILES:.cxx=.cxx.d))

.PHONY: all 
all: bin/$(OUTPUT)

bin/$(OUTPUT): GNUmakefile $(OBJ)
		mkdir -p "$(dir $@)"
		$(CXX) $(LDFLAG) $(OBJ) -o $@

obj/%.cxx.o: %.cxx GNUmakefile
		mkdir -p "$(dir $@)"
		$(CXX) $(CXXFLAG) -c $< -o $@

.PHONY: clean
clean:
		rm -rf obj bin
