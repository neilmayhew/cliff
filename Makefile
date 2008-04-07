CFLAGS = -g -O3 -Wall

all: cliff

test: cliff
	./cliff -ep 1e-3 <test-data.txt

clean:
	$(RM) *.[od] cliff
