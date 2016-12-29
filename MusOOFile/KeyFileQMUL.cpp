//============================================================================
/**
	Implementation file for KeyFileQMUL.h
	
	@author		Johan Pauwels
	@date		20100401
*/
//============================================================================

// Includes
#include "MusOOFile/KeyFileQMUL.h"

using namespace MusOO;

KeyFileQMUL::KeyFileQMUL(const bool inPitchSpelled)
: KeyFile(inPitchSpelled)
{
}

KeyFileQMUL::KeyFileQMUL(std::string inFileName, const bool inPitchSpelled)
: KeyFile(inPitchSpelled)
{
	open(inFileName);
}

KeyFileQMUL::~KeyFileQMUL()
{
	close();
}

void KeyFileQMUL::open(const std::string& inFileName)
{
	m_FileHasChanged = false;
	m_File.open(inFileName);
	KeyQMULSequence theKeyQMs = m_File.readAll();
	m_TimedKeys.resize(theKeyQMs.size());
	for (size_t i = 0; i < theKeyQMs.size(); ++i)
	{
		m_TimedKeys[i] = theKeyQMs[i]; 
	}
    KeyFile::open(inFileName);
}

void KeyFileQMUL::close()
{
	if (m_FileHasChanged)
	{
		KeyQMULSequence theKeyQMULs(m_TimedKeys.size());
		for (size_t i = 0; i < theKeyQMULs.size(); ++i)
		{
			theKeyQMULs[i] = m_TimedKeys[i];
		}
		m_File.writeAll(theKeyQMULs);
	}
}
