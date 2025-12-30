.suffix:

override OUTPUT = trm

CXX = g++
CXXFLAG := -O0 -march=native -mtune=native -fstack-protector -fno-plt -flto -msse4.2 -pipe -Wall -Wextra -ffunction-sections
LDFLAG := -flto  -Wl,-O2 -Wl,--gc-sections -Wl,--as-needed -Wl,-z,relro,-z,now 


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
