default:
	g++ Paws/main.cpp Paws/operations.cpp Paws/interpreter.cpp Paws/compiler.cpp Paws/files.cpp -o paws.exe -IPaws/include -Wall -Wextra
