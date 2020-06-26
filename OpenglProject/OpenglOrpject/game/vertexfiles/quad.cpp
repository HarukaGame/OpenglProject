#include "quad.h"
const int PolygonQuad::vertexNum = 6;
const int PolygonQuad::elementNum = 8;
const int PolygonQuad::dateNum = 48;
const float PolygonQuad::verticex[] = {
	-0.5f,	0.5f,	0.0f,	0.0f,	0.0f,	1.0f,	0.0f,	0.0f,
	-0.5f,	-0.5f,	0.0f,	0.0f,	0.0f,	1.0f,	0.0f,	1.0f,
	0.5f,	0.5f,	0.0f,	0.0f,	0.0f,	1.0f,	1.0f,	0.0f,

	0.5f,	-0.5f,	0.0f,	0.0f,	0.0f,	1.0f,	1.0f,	1.0f,
	0.5f,	0.5f,	0.0f,	0.0f,	0.0f,	1.0f,	1.0f,	0.0f,
	-0.5f,	-0.5f,	0.0f,	0.0f,	0.0f,	1.0f,	0.0f,	1.0f,
};

const float PolygonQuad::normals[108] = {
	0.0f	,1.0f,	0.0f,
	0.0f	,1.0f,	0.0f,
	0.0f	,1.0f,	0.0f,

	0.0f	,1.0f,	0.0f,
	0.0f	,1.0f,	0.0f,
	0.0f	,1.0f,	0.0f,

	0.0f	,0.0f,	1.0f,
	0.0f	,0.0f,	1.0f,
	0.0f	,0.0f,	1.0f,

	0.0f	,0.0f,	1.0f,
	0.0f	,0.0f,	1.0f,
	0.0f	,0.0f,	1.0f,

	1.0f	,0.0f,	0.0f,
	1.0f	,0.0f,	0.0f,
	1.0f	,0.0f,	0.0f,

	1.0f	,0.0f,	0.0f,
	1.0f	,0.0f,	0.0f,
	1.0f	,0.0f,	0.0f,

	0.0f	,0.0f,	-1.0f,
	0.0f	,0.0f,	-1.0f,
	0.0f	,0.0f,	-1.0f,

	0.0f	,0.0f,	-1.0f,
	0.0f	,0.0f,	-1.0f,
	0.0f	,0.0f,	-1.0f,

	-1.0f	,0.0f,	0.0f,
	-1.0f	,0.0f,	0.0f,
	-1.0f	,0.0f,	0.0f,

	-1.0f	,0.0f,	0.0f,
	-1.0f	,0.0f,	0.0f,
	-1.0f	,0.0f,	0.0f,

	0.0f	,-1.0f,	0.0f,
	0.0f	,-1.0f,	0.0f,
	0.0f	,-1.0f,	0.0f,

	0.0f	,-1.0f,	0.0f,
	0.0f	,-1.0f,	0.0f,
	0.0f	,-1.0f,	0.0f


};


