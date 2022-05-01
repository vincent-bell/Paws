# Paws Programming Language
![alt text](https://previews.123rf.com/images/savo/savo1901/savo190100032/126589110-kontur-kinderhase-einfache-zeichnung-tier.jpg)
### Paws aims to be a user-friendly, easy to learn, high-level programming langauge which offers the ability to both compile and interpret your scripts.  
### The langauge will be written mostly in C and hopes to support  both Windows and Linux users. In the future this language may support MacOS as well but currently it does not.

## Functions Available in main.c
	interpret_program(tuple program[], int total_ops)
`Interprets a sequence of assembly operations.`

## Types Available in main.c
	struct tuple { values[5], size_t size }

## Assembly Instruction Set
	LOAD_FAST(signed int value)
`Loads a signed 32 bit integer directly onto the stack.`  

	S232_ADDH(void)
`Pops two values from the top of the stack and adds them together. The result is then loaded onto the stack.`  

	S232_SUBH(void)
`Pops two values from the top of the stack and subtracts them. The result is then loaded onto the stack.`  

	S232_MULH(void)
`Pops two values from the top of the stack and multiplies theem together. The result is then loaded onto the stack.`  

	OUTPUT64(void)
`Pops the value at the top of the stack and prints it to stdout.`
