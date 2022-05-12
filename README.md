# Paws Programming Language
![alt text](https://i.gyazo.com/5473c574147282351870b0be55dbff8c.png)
### Paws aims to be a user-friendly, easy to learn, high-level programming langauge which offers the ability to both compile and interpret your scripts.  
### The langauge will be written mostly in C and hopes to support  both Windows and Linux users. In the future this language may support MacOS as well but currently it does not.

## Building the Executable to Run Paws
Make sure you have gcc installed so that you can run `make` inside this repository.  

Remember that the `Makefile` builds *paws.exe* so you can't run ./paws before making it with the gcc compiler.  

## Commands  
Once you have built *paws.exe* you can run `./paws` and you should get a response like `Usage: ./paws action args -flags`  

	./paws simulate path/to/myfile.iasm -d (optional debugging mode)
	./paws lcompile path/to/myfile.iasm -o path/to/myassembly.asm
	./paws wcompile path/to/myfile.iasm -o path/to/myprogram.c

**What does the simulate command do?**  
The program simulator built into Paws currently takes some input file (.iasm), interprets the file and outputs some result.  

**What does the compile command do?**  
The Linux compiler built into Paws currently takes some input file (.iasm) and compiles it to x86_64 assembly (.asm)    
The Windows compiler built into Paws currently takes some input file (.iasm) and compiles it to C (.c)

## Examples  
If you need a reference for writing programs in the paws programming language refer to the examples folder [here](https://github.com/vincent-bell/Paws-Programming-Language/tree/main/examples)

## Assembly Instruction Set
	LOAD_FAST (signed int value)
	~ Loads a signed 32 bit integer directly onto the stack.

	S232_ADDH (void)
	~ Pops two values from the top of the stack and adds them together. The result is then loaded onto the stack.

	S232_SUBH (void)
	~ Pops two values from the top of the stack and subtracts them. The result is then loaded onto the stack.

	S232_MULH (void)
	~ Pops two values from the top of the stack and multiplies theem together. The result is then loaded onto the stack.

	OUTPUT64 (void)
	~ Pops the value at the top of the stack and prints it to stdout.

	IVT_ERROR (int errid)
	~ Raises an error which prints a message if the error code is recognized. The program then terminates with exit status 1.
