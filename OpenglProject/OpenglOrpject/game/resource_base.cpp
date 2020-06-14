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

void CResourceBase::SetHash(const hash _hash)
{
	m_hash = _hash;
}

hash CResourceBase::GetHash() const
{
	return m_hash;
}
