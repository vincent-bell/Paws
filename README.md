<h1 align="center">Paws Programming Language</h1>
<p align="center" width="100%">
    <img width="33%" src="https://i.gyazo.com/8fedf7ab7c7014fd20a8b07d85834bbe.png">
</p>

### Paws aims to be a user-friendly, easy to learn, high-level programming langauge which offers the ability to both compile and interpret your scripts.  
### The langauge will be written mostly in C and hopes to support both Windows and Linux users. The shell interface currently being designed for Paws will be written in Python.

## Building the Executable to Run Paws
Make sure you have gcc installed so that you can run `make` inside this repository.  

Remember that the `Makefile` builds *paws.exe* so you can't run ./paws before making it with the gcc compiler.  

## Commands  
Once you have built *paws.exe* you can run `./paws` and you should get a response like `Usage: ./paws action args -flags`  

	./paws simulate path/to/input.iasm -d (optional debugging flag)
	./paws compile path/to/input.iasm -o path/to/output.c

**What does the simulate command do?**  
The program simulator built into Paws currently takes some input file (.iasm) and attempts to run the code inside it using a virtual stack.

**What does the compile command do?**  
The compiler built into Paws currently takes some input file (.iasm) and compiles it to C (.c)

## Examples  
If you need a reference for writing programs in the paws programming language refer to the examples folder [here](https://github.com/vincent-bell/Paws-Programming-Language/tree/main/examples)

## Assembly Instruction Set
	LOAD_INT (int value)
	~ Loads a signed 32 bit signed integer onto the stack.

	ADDH (void)
	~ Pops two values from the top of the stack and adds them together. The result of this addition is then pushed onto the stack.

	SUBH (void)
	~ Pops two values from the top of the stack and subtracts them. The result of this subtraction is then pushed onto the stack.

	MULH (void)
	~ Pops two values from the top of the stack and multiplies them together. The result of this multiplication is then pushed onto the stack.

	DUMP (void)
	~ Pops the value at the top of the stack and prints it to stdout.

	ERROR (int errid)
	~ Raises an error which should print a message if the error code is recognized. The behaviour following this message will depend on the error code.
