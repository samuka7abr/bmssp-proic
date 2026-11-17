CXX      := g++
CXXFLAGS := -std=c++17 -O2 -Wall -Wextra

SRC := $(X)/sol.cpp
IN  := $(X)/IO/i.txt
EXP := $(X)/IO/o.txt
BIN := build/$(X)

ifneq ($(filter run test,$(MAKECMDGOALS)),)
  ifeq ($(X),)
    $(error informe o exercicio, ex: make $(firstword $(MAKECMDGOALS)) X=1100)
  endif
endif

.PHONY: run test clean

# make run X=1100  -> compila e roda com IO/i.txt na entrada
run: $(BIN)
	./$(BIN) < $(IN)

# make test X=1100 -> compila, roda e compara a saida com IO/o.txt
test: $(BIN)
	./$(BIN) < $(IN) | diff -u --color=auto $(EXP) - && echo "OK: $(X)"

$(BIN): $(SRC)
	@mkdir -p build
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	rm -rf build
