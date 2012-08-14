//============================================================================
/**
	Implementation file for QMKeyFile.h
	
	@author		Johan Pauwels
	@date		20100401
*/
//============================================================================

// Includes
#include "QMKeyFile.h"

QMKeyFile::QMKeyFile()
{
}

QMKeyFile::QMKeyFile(std::string inFileName)
{
	open(inFileName);
}

QMKeyFile::~QMKeyFile()
{
	close();
}

void QMKeyFile::open(const std::string& inFileName)
{
	m_FileHasChanged = false;
	m_File.open(inFileName);
	QMKeySequence theQMKeys = m_File.readAll();
	m_TimedKeys.resize(theQMKeys.size());
	for (size_t i = 0; i < theQMKeys.size(); ++i)
	{
		m_TimedKeys[i] = theQMKeys[i]; 
	}
}

void QMKeyFile::close()
{
	if (m_FileHasChanged)
	{
		QMKeySequence theQMKeys(m_TimedKeys.size());
		for (size_t i = 0; i < theQMKeys.size(); ++i)
		{
			theQMKeys[i] = m_TimedKeys[i]; 
		}
		m_File.writeAll(theQMKeys);
	}
}
