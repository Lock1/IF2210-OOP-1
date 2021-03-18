# 13519214 - Makefile
# Self note : Don't forget -D_LINUX for every config.hpp used
all: engine main link cleanobject

partial: engine link

cleanobject:
	rm out/*.o

link:
	g++ -Wall -Wextra out/*.o -o out/engimon

engine:
	g++ -Wall -Wextra -D_LINUX -c src/engine.cpp -o out/engine.o >log/engine-linux-log.txt 2>&1

main:
	g++ -Wall -Wextra -c src/main.cpp -o out/main.o >log/main-linux-log.txt 2>&1
