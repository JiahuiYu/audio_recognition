CINC    = -Iinclude
SRC     = src
BIN     = bin
CC      = g++ -Wall -O3 -Wno-unused-result $(CINC)

all: ${BIN}/build ${BIN}/recog

# Generates a compiler for an d_lang language,
${BIN}/build: $(SRC)/build.cpp $(SRC)/hash.cpp $(SRC)/fingerprint.cpp $(SRC)/wav.cpp $(SRC)/bmp.cpp
	mkdir -p ${BIN}
	$(CC) -o $(BIN)/build $(SRC)/build.cpp $(SRC)/hash.cpp $(SRC)/fingerprint.cpp $(SRC)/bmp.cpp $(SRC)/wav.cpp -ll -lm -lfftw3

${BIN}/recog: $(SRC)/recog.cpp $(SRC)/hash.cpp $(SRC)/fingerprint.cpp $(SRC)/wav.cpp $(SRC)/bmp.cpp
	mkdir -p ${BIN}
	$(CC) -o $(BIN)/recog $(SRC)/recog.cpp $(SRC)/hash.cpp $(SRC)/fingerprint.cpp $(SRC)/bmp.cpp $(SRC)/wav.cpp -ll -lm -lfftw3

clean:
	rm -f *.BAK *.o core *~* *.a 
	rm -f $(BIN)/build
	rm -f $(BIN)/recog
