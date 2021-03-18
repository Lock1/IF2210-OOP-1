# 13519214 - Makefile
# Self note : Don't forget -D_LINUX
all:
	@g++ -Wall -Wextra -D_LINUX src/*.cpp src/entities-source/*.cpp -o out/engimon 2> log/gpp-log.txt || \
	cat log/gpp-log.txt

windows:
	@g++ -Wall -Wextra -D_LINUX src/*.cpp src/entities-source/*.cpp -o out/engimon 2> log/gpp-windows-log.txt || \
	cat log/gpp-windows-log.txt

clean:
	rm out/*
