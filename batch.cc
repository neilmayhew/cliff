/*
 *	cliff.c
 *
 *	Compute angles of projection from cliffs
 *
 *	N J H Mayhew	06 Jun 85
 *
 *
 *	Let:
 *
 *		p be the angle of projection
 *		s be sin p
 *		c be cos p
 *
 *	Equations of motion:
 *
 *		x = v c t
 *		y = h + v s t - (1/2) g t*t
 *
 *	When p is optimal:
 *
 *		y = 0 and dy/dp = 0
 *
 *	Which gives rise to:
 *
 *		x = v*v c / g s
 *		y = 0
 *
 *	Solving this for s:
 *
 *		s*s = 1 / 2(1 + gh/v*v)
 */

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>

const double g = 9.80665;

inline double r2d(double r)
{
	return r / M_PI * 180.0;
}

int getrange(char* item, double* s, double* e, double* i);
double compute(double v, double h);
double dist(double p, double v, double h);

int eopt;
int popt;
double pval;

int main(int argc, char* argv[])
{
	int c;

	while ((c = getopt(argc, argv, "ep:")) != EOF)
	{
		switch (c)
		{
		case 'p': /* Check perturbations */
			popt++;
			pval = atof(optarg);
			break;
		case 'e': /* Check for algebra errors */
			eopt++;
			break;
		}
	}

	for (;;)
	{
		double h, v;
		double vs, ve, vi;
		double hs, he, hi;

		if (!getrange("v", &vs, &ve, &vi))
			break;
		if (!getrange("h", &hs, &he, &hi))
			break;

		putchar('\n');

		for (v = vs ; v < ve ; v += vi)
			for (h = hs ; h < he ; h += hi)
				compute(v, h);

		putchar('\n');
	}

	exit(0);
}

int getrange(char* item, double* s, double* e, double* i)
{
	for(;;)
	{
		char buf[100];

		fprintf(stderr, "Enter range of %s: start [end [increment]] ",
			item);

		if (!fgets(buf, sizeof(buf), stdin))
			return 0;

		switch (sscanf(buf, "%lf%lf%lf", s, e, i))
		{
		case EOF:
		case 0:
			return 0;

		case 1:
			*e = *s + 0.5;
			*i = 1.0;
			break;

		case 2:
			*i = (*e - *s) / 10.0;
			break;

		case 3:
			break;

		default:
			fputs("too many items specified\n", stderr);
			continue;
		}

		if (*s == *e)
		{
			fputs("start = end\n", stderr);
			continue;
		}
		if (*i == 0.0)
		{
			fputs("zero increment\n", stderr);
			continue;
		}
		if (*s < *e && *i < 0.0 || *s > *e && *i > 0.0)
		{
			fputs("increment has wrong sign\n", stderr);
			continue;
		}

		return 1;
	}
}

double compute(double v, double h)
{
	double temp, s, c, p, d;

	temp = 0.5 / (1.0 + g * h / (v * v));

	s = sqrt(temp);
	p = asin(s);

	c = sqrt(1.0 - temp);
	d = v * v * c / (g * s);

	printf("v =% -7.5g  h =% -7.5g  p =% -7.5g  d =% -7.5g\n",
		v, h, r2d(p), d);

	if (eopt)
	{
		double d1 = dist(p, v, h);
		if (fabs(d - d1) > 1.e-4)
			printf("Error: D =% -7.5g\n", d1);
	}

	if (popt)
	{
		double pert1 = d - dist(p * (1. + pval), v, h);
		double pert2 = d - dist(p * (1. - pval), v, h);
		if (pert1 < 0 || pert2 < 0)
			printf("Not maximal: p+ =% -7.5g  p- =% -7.5g\n",
				pert1, pert2);
	}

	return p;
}

double dist(double p, double v, double h)
{
	double c = cos(p);
	double s = sin(p);

	return v * v * c / g * (s + sqrt(s * s + 2. * g * h / v / v));
}
