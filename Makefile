
#	$Id: Makefile,v 1.2 2008-04-08 03:17:58 mayhewn Exp $
#
#	Makefile for cliff application
#
#	Neil Mayhew - 2008-04-07

CFLAGS = -g -O3 -Wall

all: cliff

test: cliff
	./cliff -ep 1e-3 <test-data.txt

clean:
	$(RM) *.[od] cliff
