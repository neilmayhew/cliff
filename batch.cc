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

#define	reg	register

#include	<stdio.h>
#include	<math.h>
#include	"pi.h"

#define	G	9.80665

#define	DEGREES( R )	( (R) / pi * 180.0 )

double	compute(), dist();
double	atof();

int	eopt;
int	popt;
float	pval;

int
main( argc , argv )
	int	argc;
	char	*argv[];
	{
	extern	int	optind;
	extern	char	*optarg;
	int	c;
	reg	float	h, v;
	float	vs, ve, vi;
	float	hs, he, hi;

	while ( (c = getopt( argc , argv , "ep:" )) != EOF )
		{
		switch ( c )
			{
		case 'p':	/* Check perturbations */
			popt++;
			pval = atof( optarg );
			break;
		case 'e':	/* Check for algebra errors */
			eopt++;
			break;
			}
		}

	for(;;)
		{
		if ( !getrange( "v" , &vs , &ve , &vi ) )
			break;
		if ( !getrange( "h" , &hs , &he , &hi ) )
			break;

		putchar( '\n' );

		for ( v = vs ; v < ve ; v += vi )
			for ( h = hs ; h < he ; h += hi )
				compute( v , h );

		putchar( '\n' );
		}

	exit( 0 );
	}

int
getrange( item , s , e , i )
	char	*item;
	float	*s, *e, *i;
	{
	char	buf[100];

	for(;;)
		{
		fprintf( stderr, "Enter range of %s: start [end [increment]] ",
			item );

		if ( !gets( buf ) )
			return( 0 );

		switch ( sscanf( buf , "%f%f%f" , s , e , i ) )
			{
		case EOF:
		case 0:
			return( 0 );

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
			fputs( "too many items specified\n" , stderr );
			continue;
			}

		if ( *s == *e )
			{
			fputs( "start = end\n" , stderr );
			continue;
			}
		if ( *i == 0.0 )
			{
			fputs( "zero increment\n" , stderr );
			continue;
			}
		if ( *s < *e && *i < 0.0 || *s > *e && *i > 0.0 )
			{
			fputs( "increment has wrong sign\n" , stderr );
			continue;
			}

		return( 1 );
		}
	}

double
compute( v , h )
	float	v, h;
	{
	double	temp, s, c, p, d;

	temp = 0.5 / ( 1.0 + G * h / (v * v) );

	s = sqrt( temp );
	p = asin( s );

	c = sqrt( 1.0 - temp );
	d = v * v * c / ( G * s );

	printf( "v =% -7.5g  h =% -7.5g  p =% -7.5g  d =% -7.5g\n" ,
		v , h , DEGREES( p ) , d );

	if ( eopt )
		{
		double	D;
		D = dist( p , v , h );
		if ( fabs( D - d ) > 1.e-4 )
			printf( "Error: D =% -7.5g\n" , D );
		}

	if ( popt )
		{
		double	pert1, pert2;
		pert1 = d - dist( p * (1. + pval) , v , h );
		pert2 = d - dist( p * (1. - pval) , v , h );
		if ( pert1 < 0 || pert2 < 0 )
			printf( "Not maximal: p+ =% -7.5g  p- =% -7.5g\n" ,
				pert1 , pert2 );
		}

	return( p );
	}

double
dist( p , v , h )
	float	p, v, h;
	{
	double	c, s;

	s = sin( p );
	c = cos( p );

	return( v * v * c / G * ( s + sqrt( s * s + 2. * G * h / v / v ) ) );
	}
