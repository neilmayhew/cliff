/*
 *	main.cc
 *
 *	Main program for cliff visualizer
 *
 *	Neil Mayhew - 2007-12-08
 *
 *	$Id: main.cc,v 1.1 2008-05-05 03:44:25 mayhewn Exp $
 */

#include <gtkmm/main.h>
#include "cliffwindow.h"

int main(int argc, char *argv[])
{
	Gtk::Main kit(argc, argv);

	CliffWindow window;
	Gtk::Main::run(window);

	return 0;
}
