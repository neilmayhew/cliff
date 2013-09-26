
#	automake file for the cliff visualizer
#
#	Neil Mayhew - 2008-05-04
#
#	$Id: Makefile.am,v 1.9 2009-03-19 01:45:21 mayhewn Exp $

noinst_PROGRAMS = cliff cliffimg batch

cliff_SOURCES = \
	cliffcairo.h  cliffcairo.cc \
	cliffwidget.h cliffwidget.cc \
	cliffwindow.h cliffwindow.cc \
	main.cc

cliff_CPPFLAGS = @GTKMM_CFLAGS@
cliff_LDADD    = @GTKMM_LIBS@

cliffimg_SOURCES = \
	cliffcairo.h cliffcairo.cc \
	cliffimg.cc

cliffimg_CPPFLAGS = @CAIROMM_CFLAGS@
cliffimg_LDADD    = @CAIROMM_LIBS@

batch_SOURCES = batch.cc

batch_test: $(top_builddir)/batch $(top_srcdir)/test-data.txt
	$(top_builddir)/batch -ep 1e-3 <$(top_srcdir)/test-data.txt
