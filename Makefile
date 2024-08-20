# Makefile

# Variables
SRC = $(filename)
OBJ = $(basename $(SRC))

# Compile target
$(OBJ): $(SRC)
	/usr/bin/gcc -fdiagnostics-color=always -g $(SRC) -o $(OBJ) -lm

# Clean target
clean:
	rm -f $(OBJ)

