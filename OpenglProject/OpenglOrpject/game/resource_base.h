#pragma once

#ifndef __RESOURCE_BASE_H__
#define __RESOURCE_BASE_H__

#include "hash.h"

class CResourceBase {
public:
	void RefCountUp();
	void RefCountDown();
	bool RefCountZero()const;

	void SetHash(const hash _hash);
	hash GetHash()const;
protected:
	hash m_hash = 0;
	int m_resourceCounter = 0;
};

#endif // !__RESOURCE_BASE_H__
