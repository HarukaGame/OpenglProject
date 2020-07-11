#include "quad_index.h"
const float PolygonQuadIndex::vertices[] = {
	-0.5f,	0.5f,	0.0f,	0.0f,	0.0f,	1.0f,	0.0f,	0.0f,
	-0.5f,	-0.5f,	0.0f,	0.0f,	0.0f,	1.0f,	0.0f,	1.0f,
	0.5f,	0.5f,	0.0f,	0.0f,	0.0f,	1.0f,	1.0f,	0.0f,
	0.5f,	-0.5f,	0.0f,	0.0f,	0.0f,	1.0f,	1.0f,	1.0f,
};

const unsigned int PolygonQuadIndex::indeces[] = {
	0,1,2,3
};

const unsigned int PolygonQuadIndex::verticesNum = 32;

