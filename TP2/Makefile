all: isa.o alu.o memoria.o main.o
	@gcc isa.o alu.o memoria.o main.o -o exe
	@rm -r *.o
isa.o: isa.c
	@gcc isa.c -c
alu.o: alu.c
	@gcc alu.c -c
memoria.o: memoria.c
	@gcc memoria.c -c
main.o: main.c
	@gcc main.c -c
run:
	@./exe
