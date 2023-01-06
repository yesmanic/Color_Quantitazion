all: compile

compile:
	@gcc -o quantize *.c -I . -lm -lpng
