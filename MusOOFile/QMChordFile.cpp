//============================================================================
/**
	Implementation file for QMChordFile.h
	
	@author		Johan Pauwels
	@date		20090119
*/
//============================================================================

// Includes
#include "QMChordFile.h"

QMChordFile::QMChordFile()
{
}

QMChordFile::QMChordFile(std::string inFileName)
{
	open(inFileName);
}

QMChordFile::~QMChordFile()
{
	close();
}

void QMChordFile::open(const std::string& inFileName)
{
	m_FileHasChanged = false;
	m_File.open(inFileName);
	m_TimedChords = ChordSequence(m_File.readAll().begin(), m_File.readAll().end());
}

void QMChordFile::close()
{
	if (m_FileHasChanged)
	{
		ChordFile::close();
		QMChordSequence theQMChords(m_TimedChords.begin(), m_TimedChords.end());
 		m_File.writeAll(theQMChords);
	}
}
