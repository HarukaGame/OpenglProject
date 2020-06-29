#include "ui.h"
const int PolygonUI::vertexNum = 6;
const int PolygonUI::elementNum = 8;
const int PolygonUI::dateNum = 48;
const float PolygonUI::verticex[] = {
	-0.5f,	0.5f,	0.0f,	0.0f,	0.0f,	1.0f,	0.0f,	0.0f,
	-0.5f,	-0.5f,	0.0f,	0.0f,	0.0f,	1.0f,	0.0f,	1.0f,
	0.5f,	0.5f,	0.0f,	0.0f,	0.0f,	1.0f,	1.0f,	0.0f,

	0.5f,	-0.5f,	0.0f,	0.0f,	0.0f,	1.0f,	1.0f,	1.0f,
	0.5f,	0.5f,	0.0f,	0.0f,	0.0f,	1.0f,	1.0f,	0.0f,
	-0.5f,	-0.5f,	0.0f,	0.0f,	0.0f,	1.0f,	0.0f,	1.0f,
};

const float PolygonUI::normals[108] = {
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


