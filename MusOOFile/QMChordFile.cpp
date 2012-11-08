//============================================================================
/**
	Implementation file for QMChordFile.h
	
	@author		Johan Pauwels
	@date		20090119
*/
//============================================================================

// Includes
#include "QMChordFile.h"

QMChordFile::QMChordFile(const bool inPitchSpelled)
: ChordFile(inPitchSpelled)
{
}

QMChordFile::QMChordFile(std::string inFileName, const bool inPitchSpelled)
: ChordFile(inPitchSpelled)
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
	m_TimedChords = TimedChordSequence(m_File.readAll().begin(), m_File.readAll().end());
    ChordFile::open(inFileName);
}

void QMChordFile::close()
{
	if (m_FileHasChanged)
	{
		ChordFile::close();
		TimedQMChordSequence theQMChords(m_TimedChords.begin(), m_TimedChords.end());
 		m_File.writeAll(theQMChords);
	}
}
