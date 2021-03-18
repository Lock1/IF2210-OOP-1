# 13519214 - Makefile
# Self note : Don't forget -D_LINUX for every config.hpp used
all: position entity tile map engine main link cleanobject

partial: engine link

cleanobject:
	rm out/*.o

link:
	@g++ -Wall -Wextra out/*.o -o out/engimon

engine:
	@g++ -Wall -Wextra -D_LINUX -c src/engine.cpp -o out/engine.o 2> log/engine-linux-log.txt || \
	cat log/engine-linux-log.txt

main:
	@g++ -Wall -Wextra -c src/main.cpp -o out/main.o 2> log/main-linux-log.txt || \
	cat log/main-linux-log.txt

position:
	@g++ -Wall -Wextra -c src/entities-source/position.cpp -o out/position.o 2> log/pos-linux-log.txt|| \
	cat log/pos-linux-log.txt

map:
	@g++ -Wall -Wextra -c src/entities-source/map.cpp -o out/map.o 2> log/map-linux-log.txt|| \
	cat log/map-linux-log.txt

tile:
	@g++ -Wall -Wextra -c src/entities-source/tile.cpp -o out/tile.o 2> log/tile-linux-log.txt|| \
	cat log/tile-linux-log.txt

entity:
	@g++ -Wall -Wextra -c src/entities-source/entity.cpp -o out/entity.o 2> log/entity-linux-log.txt|| \
	cat log/entity-linux-log.txt
