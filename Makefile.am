
#	automake file for the cliff visualizer
#
#	Neil Mayhew - 2008-05-04
#
#	$Id: Makefile.am,v 1.5 2008-05-06 13:22:35 mayhewn Exp $

noinst_PROGRAMS = cliff batch

cliff_SOURCES = \
	cliffwidget.h cliffwidget.cc \
	cliffwindow.h cliffwindow.cc \
	main.cc

cliff_CPPFLAGS = @GTKMM_CFLAGS@
cliff_LDFLAGS = @GTKMM_LIBS@

batch_SOURCES = batch.cc

batch_test: $(top_builddir)/batch $(top_srcdir)/test-data.txt
	$(top_builddir)/batch -ep 1e-3 <$(top_srcdir)/test-data.txt
