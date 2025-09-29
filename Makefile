# Build all programs for Signals lab
all: signal1 signal2 timer

signal1: signal1.c
	@echo "Compiling signal1..."
	gcc -Wall -Wextra -O2 signal1.c -o signal1

signal2: signal2.c
	@echo "Compiling signal2..."
	gcc -Wall -Wextra -O2 signal2.c -o signal2

timer: timer.c
	@echo "Compiling timer..."
	gcc -Wall -Wextra -O2 timer.c -o timer

clean:
	@echo "Cleaning..."
	rm -f signal1 signal2 timer