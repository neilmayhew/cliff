/*
 *	cliffimg.cc
 *
 *	Render a cliff diagram to one of several image formats
 *
 *	Neil Mayhew - 2009-03-13
 *
 *	$Id: cliffimg.cc,v 1.4 2009-03-14 23:44:52 mayhewn Exp $
 */

#include "cliffcairo.h"

#include <cairomm/surface.h>

#include <iostream>
#include <string>
#include <libgen.h>

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		std::cerr << "Usage: "<<basename(argv[0])<<" FILE\n";
		return 1;
	}

	std::string filename(argv[1]);

	int size_x = 500;
	int size_y = 500;

	double velocity = 20.0;
	double height   = 50.0;

	if (filename.rfind('.') == filename.npos)
	{
		std::cerr << "Missing filename suffix: " << filename << "\n";
		return 2;
	}
	
	std::string suffix = filename.substr(filename.rfind('.') + 1);

	Cairo::RefPtr<Cairo::Surface> surface;

	if (suffix == "pdf")
		surface = Cairo::PdfSurface::create(filename, size_x, size_y);
	else if (suffix == "svg")
		surface = Cairo::SvgSurface::create(filename, size_x, size_y);
	else if (suffix == "ps")
		surface = Cairo::PsSurface::create(filename, size_x, size_y);
	else if (suffix == "png")
		surface = Cairo::ImageSurface::create(Cairo::FORMAT_RGB24, size_x, size_y);
	else
	{
		std::cerr << "Unknown filename suffix: " << suffix << "\n";
		return 2;
	}

	Cairo::RefPtr<Cairo::Context> context = Cairo::Context::create(surface);

	if (suffix == "png")
	{
	    context->rectangle(0, 0, size_x, size_y);
	    context->set_source_rgb(1.0, 1.0, 1.0);
	    context->fill();
	}

	render(context, velocity, height, size_x, size_y);

	if (suffix == "png")
		surface->write_to_png(filename);

	return 0;
}
