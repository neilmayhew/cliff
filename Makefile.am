
#	automake file for the cliff visualizer
#
#	Neil Mayhew - 2008-05-04
#
#	$Id: Makefile.am,v 1.3 2008-05-06 04:49:17 mayhewn Exp $

noinst_PROGRAMS = cliff batch

cliff_SOURCES = \
	cliffwidget.h cliffwidget.cc \
	cliffwindow.h cliffwindow.cc \
	main.cc

cliff_INCLUDES = @GTKMM_CFLAGS@
cliff_LIBS = @GTKMM_LIBS@

batch_SOURCES = batch.cc

batch_test: $(top_builddir)/batch $(top_srcdir)/batchtest-data.txt
	$(top_builddir)/batch -ep 1e-3 <$(top_srcdir)/test-data.txt
