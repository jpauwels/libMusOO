//============================================================================
/**
	Implementation file for KeyFileQM.h
	
	@author		Johan Pauwels
	@date		20100401
*/
//============================================================================

// Includes
#include "MusOOFile/KeyFileQM.h"

using namespace MusOO;

KeyFileQM::KeyFileQM(const bool inPitchSpelled)
: KeyFile(inPitchSpelled)
{
}

KeyFileQM::KeyFileQM(std::string inFileName, const bool inPitchSpelled)
: KeyFile(inPitchSpelled)
{
	open(inFileName);
}

KeyFileQM::~KeyFileQM()
{
	close();
}

void KeyFileQM::open(const std::string& inFileName)
{
	m_FileHasChanged = false;
	m_File.open(inFileName);
	KeyQMSequence theKeyQMs = m_File.readAll();
	m_TimedKeys.resize(theKeyQMs.size());
	for (size_t i = 0; i < theKeyQMs.size(); ++i)
	{
		m_TimedKeys[i] = theKeyQMs[i]; 
	}
    KeyFile::open(inFileName);
}

void KeyFileQM::close()
{
	if (m_FileHasChanged)
	{
		KeyQMSequence theKeyQMs(m_TimedKeys.size());
		for (size_t i = 0; i < theKeyQMs.size(); ++i)
		{
			theKeyQMs[i] = m_TimedKeys[i]; 
		}
		m_File.writeAll(theKeyQMs);
	}
}
