/*
 *	cliffsvg.cc
 *
 *	Render a cliff diagram to SVG
 *
 *	Neil Mayhew - 2009-03-13
 *
 *	$Id: cliffimg.cc,v 1.1 2009-03-14 02:58:06 mayhewn Exp $
 */

#include "cliffcairo.h"

#include <cairomm/surface.h>

int main(int argc, char const* argv[])
{
	Cairo::RefPtr<Cairo::SvgSurface> svg = Cairo::SvgSurface::create(
		argv[1], 500, 500);	 

	Cairo::RefPtr<Cairo::Context> cr = Cairo::Context::create(svg);

	render(cr, 20, 50, 500, 500);

	return 0;
}
