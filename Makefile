
#	$Id: Makefile,v 1.4 2008-04-08 04:33:16 mayhewn Exp $
#
#	Makefile for cliff application
#
#	Neil Mayhew - 2008-04-07

CXXFLAGS = -g -O3 -Wall

all: cliff

test: cliff test-data.txt
	./cliff -ep 1e-3 <test-data.txt

clean:
	$(RM) *.[od] cliff
