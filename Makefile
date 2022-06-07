default:
	gcc Paws/main.c Paws/operations.c Paws/interpreter.c Paws/compiler.c Paws/files.c -o paws.exe -IPaws/include -Wall -Wextra
