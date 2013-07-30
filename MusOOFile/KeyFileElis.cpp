//============================================================================
/**
	Implementation file for KeyFileElis.h
	
	@author		Johan Pauwels
	@date		20100401
*/
//============================================================================

// Includes
#include "KeyFileElis.h"

KeyFileElis::KeyFileElis(const bool inPitchSpelled)
: KeyFile(inPitchSpelled)
{
}

KeyFileElis::KeyFileElis(std::string inFileName, const bool inPitchSpelled)
: KeyFile(inPitchSpelled)
{
	open(inFileName);
}

KeyFileElis::~KeyFileElis()
{
	close();
}

void KeyFileElis::open(const std::string& inFileName)
{
	m_FileHasChanged = false;
	m_File.open(inFileName);
	KeyElisSequence theKeyEliss = m_File.readAll();
	m_TimedKeys.resize(theKeyEliss.size());
	for (size_t i = 0; i < theKeyEliss.size(); ++i)
	{
		m_TimedKeys[i] = theKeyEliss[i]; 
	}
    KeyFile::open(inFileName);
}

void KeyFileElis::close()
{
	if (m_FileHasChanged)
	{
		KeyElisSequence theKeyEliss(m_TimedKeys.size());
		for (size_t i = 0; i < theKeyEliss.size(); ++i)
		{
			theKeyEliss[i] = m_TimedKeys[i]; 
		}
		m_File.writeAll(theKeyEliss);
	}
}
