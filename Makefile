CC = gcc
FILES = src/main.c src/lexer/lexer.c
BIN = solusc
CFLAGS = -Wall
LLVM = `llvm-config --cflags --ldflags --libs core`

$(BIN):
	$(CC) $(FILES) -o $(BIN) $(CFLAGS)

clean:
	rm $(BIN)

run: 
	make
	./$(BIN)
