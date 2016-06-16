
#	autoconf file for the cliff visualizer
#
#	Neil Mayhew - 2008-05-04
#
#	$Id: configure.ac,v 1.4 2009-03-19 01:45:21 mayhewn Exp $

AC_INIT([cliff], [0.1], [neil_mayhew@users.sourceforge.net])
AC_CONFIG_HEADERS([config.h])

AM_INIT_AUTOMAKE(foreign)
AM_MAINTAINER_MODE

AC_PROG_CXX

PKG_CHECK_MODULES([GTKMM], [gtkmm-3.0 >= 3.0.0])
PKG_CHECK_MODULES([CAIROMM], [cairomm-1.0 >= 1.6.0])

AC_CONFIG_FILES([Makefile])
AC_OUTPUT

