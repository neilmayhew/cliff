
#	$Id: Makefile,v 1.3 2008-04-08 03:22:56 mayhewn Exp $
#
#	Makefile for cliff application
#
#	Neil Mayhew - 2008-04-07

CFLAGS = -g -O3 -Wall

all: cliff

test: cliff test-data.txt
	./cliff -ep 1e-3 <test-data.txt

clean:
	$(RM) *.[od] cliff
