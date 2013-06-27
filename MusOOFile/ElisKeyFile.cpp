//============================================================================
/**
	Implementation file for ElisKeyFile.h
	
	@author		Johan Pauwels
	@date		20100401
*/
//============================================================================

// Includes
#include "ElisKeyFile.h"

ElisKeyFile::ElisKeyFile(const bool inPitchSpelled)
: KeyFile(inPitchSpelled)
{
}

ElisKeyFile::ElisKeyFile(std::string inFileName, const bool inPitchSpelled)
: KeyFile(inPitchSpelled)
{
	open(inFileName);
}

ElisKeyFile::~ElisKeyFile()
{
	close();
}

void ElisKeyFile::open(const std::string& inFileName)
{
	m_FileHasChanged = false;
	m_File.open(inFileName);
	ElisKeySequence theElisKeys = m_File.readAll();
	m_TimedKeys.resize(theElisKeys.size());
	for (size_t i = 0; i < theElisKeys.size(); ++i)
	{
		m_TimedKeys[i] = theElisKeys[i]; 
	}
    KeyFile::open(inFileName);
}

void ElisKeyFile::close()
{
	if (m_FileHasChanged)
	{
		ElisKeySequence theElisKeys(m_TimedKeys.size());
		for (size_t i = 0; i < theElisKeys.size(); ++i)
		{
			theElisKeys[i] = m_TimedKeys[i]; 
		}
		m_File.writeAll(theElisKeys);
	}
}
