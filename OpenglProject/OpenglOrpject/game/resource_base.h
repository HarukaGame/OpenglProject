#pragma once

#ifndef __RESOURCE_BASE_H__
#define __RESOURCE_BASE_H__



class CResourceBase {
public:
	void RefCountUp();
	void RefCountDown();
	bool RefCountZero()const;

protected:
	int m_resourceCounter = 0;
};

#endif // !__RESOURCE_BASE_H__
