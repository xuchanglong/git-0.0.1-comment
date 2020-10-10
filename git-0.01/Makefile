CFLAGS=-g
CC=gcc
RELEASE_PATH=../release

PROG=update-cache show-diff init-db write-tree read-tree commit-tree cat-file

all: $(PROG)

install: $(PROG)
	install $(PROG) $(HOME)/bin/

LIBS= -lssl -lcrypto -lz

init-db: init-db.o
	$(CC) $(CFLAGS) -o $(RELEASE_PATH)/$@ $^ $(LIBS)

update-cache: update-cache.o read-cache.o
	$(CC) $(CFLAGS) -o $(RELEASE_PATH)/$@ $^ $(LIBS)

show-diff: show-diff.o read-cache.o
	$(CC) $(CFLAGS) -o $(RELEASE_PATH)/$@ $^ $(LIBS)

write-tree: write-tree.o read-cache.o
	$(CC) $(CFLAGS) -o $(RELEASE_PATH)/$@ $^ $(LIBS)

read-tree: read-tree.o read-cache.o
	$(CC) $(CFLAGS) -o $(RELEASE_PATH)/$@ $^ $(LIBS)

commit-tree: commit-tree.o read-cache.o
	$(CC) $(CFLAGS) -o $(RELEASE_PATH)/$@ $^ $(LIBS)

cat-file: cat-file.o read-cache.o
	$(CC) $(CFLAGS) -o $(RELEASE_PATH)/$@ $^ $(LIBS)

read-cache.o: cache.h
show-diff.o: cache.h

clean_obj:
	rm -f *.o

clean:
	rm -f *.o $(RELEASE_PATH)/*
