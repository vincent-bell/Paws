default:
	gcc Paws/main.c Paws/operations.c Paws/files.c Paws/interpreter.c Paws/wcompiler.c Paws/lcompiler.c -o paws.exe -IPaws/include -Wall -Wextra
