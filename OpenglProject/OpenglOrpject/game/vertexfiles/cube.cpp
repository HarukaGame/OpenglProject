﻿#include "cube.h"
const int PolygonCube::vertexNum = 36;
const int PolygonCube::elementNum = 6;
const int PolygonCube::dateNum = 216;
const float PolygonCube::verticex[] = {
	-0.5f,	0.5f,	-0.5f,	0.0f,1.0f,0.0f,
	-0.5f,	0.5f,	0.5f,	0.0f,1.0f,0.0f,
	0.5f,	0.5f,	-0.5f,	0.0f,1.0f,0.0f,

	0.5f,	0.5f,	0.5f,	0.0f,1.0f,0.0f,
	0.5f,	0.5f,	-0.5f,	0.0f,1.0f,0.0f,
	-0.5f,	0.5f,	0.5f,	0.0f,1.0f,0.0f,

	-0.5f,	0.5f,	0.5f,	0.0f,0.0f,1.0f,
	-0.5f,	-0.5f,	0.5f,	0.0f,0.0f,1.0f,
	0.5f,	0.5f,	0.5f,	0.0f,0.0f,1.0f,

	0.5f,	-0.5f,	0.5f,	0.0f,0.0f,1.0f,
	0.5f,	0.5f,	0.5f,	0.0f,0.0f,1.0f,
	-0.5f,	-0.5f,	0.5f,	0.0f,0.0f,1.0f,

	0.5f,	0.5f,	0.5f,	1.0f,0.0f,0.0f,
	0.5f,	-0.5f,	0.5f,	1.0f,0.0f,0.0f,
	0.5f,	0.5f,	-0.5f,	1.0f,0.0f,0.0f,

	0.5f,	-0.5f,	-0.5f,	1.0f,0.0f,0.0f,
	0.5f,	0.5f,	-0.5f,	1.0f,0.0f,0.0f,
	0.5f,	-0.5f,	0.5f,	1.0f,0.0f,0.0f,

	0.5f,	0.5f,	-0.5f,	0.0f,0.0f,-1.0f,
	0.5f,	-0.5f,	-0.5f,	0.0f,0.0f,-1.0f,
	-0.5f,	0.5f,	-0.5f,	0.0f,0.0f,-1.0f,

	-0.5f,	-0.5f,	-0.5f,	0.0f,0.0f,-1.0f,
	-0.5f,	0.5f,	-0.5f,	0.0f,0.0f,-1.0f,
	0.5f,	-0.5f,	-0.5f,	0.0f,0.0f,-1.0f,

	-0.5f,	0.5f,	0.5f,	-1.0f,0.0f,0.0f,
	-0.5f,	0.5f,	-0.5f,	-1.0f,0.0f,0.0f,
	-0.5f,	-0.5f,	0.5f,	-1.0f,0.0f,0.0f,

	-0.5f,	-0.5f,	-0.5f,	-1.0f,0.0f,0.0f,
	-0.5f,	-0.5f,	0.5f,	-1.0f,0.0f,0.0f,
	-0.5f,	0.5f,	-0.5f,	-1.0f,0.0f,0.0f,

	-0.5f,	-0.5f,	0.5f,	0.0f,-1.0f,0.0f,
	-0.5f,	-0.5f,	-0.5f,	0.0f,-1.0f,0.0f,
	0.5f,	-0.5f,	0.5f,	0.0f,-1.0f,0.0f,

	0.5f,	-0.5f,	-0.5f,	0.0f,-1.0f,0.0f,
	0.5f,	-0.5f,	0.5f,	0.0f,-1.0f,0.0f,
	-0.5f,	-0.5f,	-0.5f,	0.0f,-1.0f,0.0f

};

const float PolygonCube::normals[108] = {
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


