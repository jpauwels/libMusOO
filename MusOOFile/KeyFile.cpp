//============================================================================
/**
	Implementation file for KeyFile.h
	
	@author		Johan Pauwels
	@date		20100401
*/
//============================================================================

// Includes
#include "KeyFile.h"

KeyFile::KeyFile() 
: m_FileHasChanged(false)
{
}

KeyFile::~KeyFile()
{
}

const KeySequence& KeyFile::readAll()
{
	return m_TimedKeys;
}

const KeySequence KeyFile::readRange(double inStartTime, double inEndTime)
{
	//range check
	if (!m_TimedKeys.empty() && inStartTime < m_TimedKeys.front().onset())
	{
		inStartTime = m_TimedKeys.front().onset();
	}
	if (inEndTime <= inStartTime || (!m_TimedKeys.empty() && inEndTime > m_TimedKeys.back().offset()))
	{
		inEndTime = m_TimedKeys.back().offset();
	}
	//find first label in range
	KeySequence::const_iterator it = m_TimedKeys.begin();
	while (it != m_TimedKeys.end() && it->offset() <= inStartTime)
	{
		++it;
	}
	//add range
	KeySequence theKeysRange;
	while (it != m_TimedKeys.end() && it->onset() < inEndTime)
	{
		theKeysRange.push_back(*it);
		++it;
	}
	//update times of extrema
	if (!theKeysRange.empty())
	{
		theKeysRange.front().onset() = inStartTime;
		theKeysRange.back().offset() = inEndTime;
	}
	return theKeysRange;
}

void KeyFile::writeAll(KeySequence& inTimedKeys)
{
	m_TimedKeys = inTimedKeys;
	m_FileHasChanged = true;
}

bool KeyFile::isEmpty() const
{
	return m_TimedKeys.empty();
}
