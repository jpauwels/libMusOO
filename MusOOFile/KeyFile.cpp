//============================================================================
/**
	Implementation file for KeyFile.h
	
	@author		Johan Pauwels
	@date		20100401
*/
//============================================================================

// Includes
#include "MusOOFile/KeyFile.h"

using namespace MusOO;

KeyFile::KeyFile(const bool inPitchSpelled) 
: m_FileHasChanged(false), m_PitchSpelled(inPitchSpelled)
{
}

KeyFile::~KeyFile()
{
}

void KeyFile::open(const std::string& inFileName)
{
    if (!m_PitchSpelled)
    {
        for (TimedKeySequence::iterator it = m_TimedKeys.begin(); it != m_TimedKeys.end(); ++it)
        {
            it->label().ignoreSpelling();
        }
    }
}

const TimedKeySequence& KeyFile::readAll()
{
	return m_TimedKeys;
}

const TimedKeySequence KeyFile::readRange(double inStartTime, double inEndTime)
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
	TimedKeySequence::const_iterator it = m_TimedKeys.begin();
	while (it != m_TimedKeys.end() && it->offset() <= inStartTime)
	{
		++it;
	}
	//add range
	TimedKeySequence theKeysRange;
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

void KeyFile::writeAll(TimedKeySequence& inTimedKeys)
{
	m_TimedKeys = inTimedKeys;
	m_FileHasChanged = true;
}

bool KeyFile::isEmpty() const
{
	return m_TimedKeys.empty();
}
