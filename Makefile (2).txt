.SILENT:
.PHONY: clean main test tar

TARFILE=CP4_group34.tar.gz

main: bin/actor_db
	./bin/actor_db

test: bin/test-bst bin/test-actordb bin/test-heap
	./bin/test-bst
	./bin/test-actordb
	./bin/test-heap

bin/actor_db: obj/main.o obj/parser.o obj/heap.o obj/bst.o obj/actor.o obj/actor_db.o obj/bst.o
	mkdir -p bin
	g++ -Wall -Werror obj/main.o obj/parser.o obj/heap.o obj/bst.o obj/actor.o obj/actor_db.o obj/bst.o -o bin/actor_db

obj/main.o:	src/main.cpp
	mkdir -p obj
	g++ -Wall -Werror -c src/main.cpp -o obj/main.o

obj/actor.o: src/actor.h src/actor.cpp
	mkdir -p obj
	g++ -Wall -Werror -c src/actor.cpp -o obj/actor.o

obj/actor_db.o: src/actor_db.h src/actor_db.cpp
	mkdir -p obj
	g++ -Wall -Werror -c src/actor_db.cpp -o obj/actor_db.o

obj/bst.o: src/bst.h src/bst.cpp
	mkdir -p obj
	g++ -Wall -Werror -c src/bst.cpp -o obj/bst.o

obj/heap.o: src/heap.h src/heap.cpp
	mkdir -p obj
	g++ -Wall -Werror -c src/heap.cpp -o obj/heap.o

obj/parser.o: src/Parser.h src/Parser.cpp
	mkdir -p obj
	g++ -Wall -Werror -c src/Parser.cpp -o obj/parser.o

obj/test_bst.o: tests/bst.cpp
	mkdir -p obj
	g++ -Wall -Werror -c tests/bst.cpp -o obj/test_bst.o

obj/test_actor_db.o: tests/actor_db.cpp
	mkdir -p obj
	g++ -Wall -Werror -c tests/actor_db.cpp -o obj/test_actor_db.o

obj/test_heap.o: tests/heap.cpp
	mkdir -p obj
	g++ -Wall -Werror -c tests/heap.cpp -o obj/test_heap.o

clean: 
	rm -rf obj bin

tar:	clean
	tar cvvf $(TARFILE) .
	gzip $(TARFILE)

bin/test-bst: obj/test_bst.o obj/heap.o obj/actor.o obj/actor_db.o obj/bst.o
	mkdir -p bin
	g++ -Wall -Werror obj/test_bst.o obj/heap.o obj/actor.o obj/actor_db.o obj/bst.o -o bin/test-bst

bin/test-actordb: obj/test_actor_db.o obj/heap.o obj/actor.o obj/actor_db.o obj/bst.o
	mkdir -p bin
	g++ -Wall -Werror obj/test_actor_db.o obj/heap.o obj/actor.o obj/actor_db.o obj/bst.o -o bin/test-actordb

bin/test-heap: obj/test_heap.o obj/heap.o obj/actor.o obj/actor_db.o obj/bst.o
	mkdir -p bin
	g++ -Wall -Werror obj/test_heap.o obj/heap.o obj/actor.o obj/actor_db.o obj/bst.o -o bin/test-heap
