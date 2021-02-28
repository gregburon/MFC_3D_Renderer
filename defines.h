

/**********************************************************/
/*                                                        */
/*   Three Dimensional Transformation                     */
/*   datatype Definitions                                 */
/*                                                        */
/**********************************************************/

#ifndef DEFINES_H
#define DEFINES_H


struct point
{
	double _x;
	double _y;
	double _z;
	double _h;
};

struct point_uvn
{
	double _u;
	double _v;
	double _n;
	double _h;
};

struct facet
{
	int    _color;
	int    _corner1;
	int    _corner2;
	int    _corner3;
	double _distance_to_observer;
};

struct point_light_distance
{
	double  _distance;
};

const int X = 0;
const int Y = 1;
const int Z = 2;
const int H = 3;

const int WIREFRAME          = 0;
const int WIREFRAME_DEPTHCUE = 1;
const int WIREFRAME_BACKFACE = 2;
const int PAINTERS           = 3;
const int PAINTERS_TRACED    = 4;
const int GOURAUD_SHADING    = 5;
const int PHONG_SHADING      = 6;

const int PARALLEL    = 0;
const int PERSPECTIVE = 1;

const int WORLD_MATRIX     = 0;
const int MODELING_MATRIX  = 1;
const int SHEAR_MATRIX     = 2;
const int PROJECTION_MATRIX = 3;

const int BLUE_PLASTIC    = 0;
const int BRASS           = 1;
const int BRONZE          = 2;
const int CHROME          = 3;
const int COPPER          = 4;
const int GOLD            = 5;
const int PEWTER          = 6;
const int SILVER          = 7;
const int POLISHED_SILVER = 8;

const int LIGHT           = 100;

const int NUM_MATERIALS   = 15;

const int MAX_LIGHTS      = 5;
const double PI = 3.14159;

const int  AXIS_LENGTH   = 25;
const int  POSITIVE      = 1;
const int  NEGATIVE      = -1;

const double POINT_A     = 1.0;
const double POINT_B     = 2.0;
const double POINT_C     = 3.0;

const double d0          = 0.15;

#endif


