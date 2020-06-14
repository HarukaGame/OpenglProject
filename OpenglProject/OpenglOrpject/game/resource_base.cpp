#include "resource_base.h"

void CResourceBase::RefCountUp() {
	m_resourceCounter++;
}

void CResourceBase::RefCountDown() {
	m_resourceCounter--;
}

bool CResourceBase::RefCountZero()const {
	return m_resourceCounter == 0;
}