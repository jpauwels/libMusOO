//============================================================================
/**
	Implementation file for ChordFileQM.h
	
	@author		Johan Pauwels
	@date		20090119
*/
//============================================================================

// Includes
#include "MusOOFile/ChordFileQM.h"

using namespace MusOO;

ChordFileQM::ChordFileQM(const bool inPitchSpelled)
: ChordFile(inPitchSpelled)
{
}

ChordFileQM::ChordFileQM(std::string inFileName, const bool inPitchSpelled)
: ChordFile(inPitchSpelled)
{
	open(inFileName);
}

ChordFileQM::~ChordFileQM()
{
	close();
}

void ChordFileQM::open(const std::string& inFileName)
{
	m_FileHasChanged = false;
	m_File.open(inFileName);
	m_TimedChords = TimedChordSequence(m_File.readAll().begin(), m_File.readAll().end());
    ChordFile::open(inFileName);
}

void ChordFileQM::close()
{
	if (m_FileHasChanged)
	{
		ChordFile::close();
		TimedChordQMSequence theChordQMs(m_TimedChords.begin(), m_TimedChords.end());
 		m_File.writeAll(theChordQMs);
	}
}
