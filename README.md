# Paws Programming Language
![alt text](https://previews.123rf.com/images/savo/savo1901/savo190100032/126589110-kontur-kinderhase-einfache-zeichnung-tier.jpg)
### Paws aims to be a user-friendly, easy to learn, high-level programming langauge which offers the ability to both compile and interpret your scripts.  
### The langauge will be written mostly in C and hopes to support  both Windows and Linux users. In the future this language may support MacOS as well but currently it does not.

## Usage
Make sure you have gcc installed so that you can run `make` inside this repository.  

Use `./paws examples/myfile.iasm` with your command shell from inside the directory where *paws.exe* is located.  

Remember that `Makefile` builds *paws.exe* so you can't run ./paws before making it with the gcc compiler.

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
