//============================================================================
/**
	Implementation file for ChordFileProsemus.h
	
	@author		Johan Pauwels
	@date		20101222
*/
//============================================================================

// Includes
#include <sstream>
#include <stdexcept>
#include "MusOOFile/ChordFileProsemus.h"

using std::string;
using std::istringstream;
using namespace MusOO;

ChordFileProsemus::ChordFileProsemus(const bool inPitchSpelled)
: ChordFile(inPitchSpelled)
{
	
}

ChordFileProsemus::ChordFileProsemus(std::string inFilePath, const bool inPitchSpelled)
: ChordFile(inPitchSpelled)
{
	open(inFilePath);
}

ChordFileProsemus::~ChordFileProsemus()
{
	close();
}

void ChordFileProsemus::open(const std::string& inFilePath)
{
	if (m_File.is_open())
	{
		close();
	}
	this->m_FileHasChanged = false;
	this->m_TimedChords.clear();
	m_File.open(inFilePath.c_str(), std::fstream::in);
	m_FilePath = inFilePath;
	if (m_File.is_open())
	{
		string theLine;
		getline(m_File, theLine);
		istringstream theLineStream(theLine);
		string theChordString;
		size_t theChordCounter = 0;
		while (theLineStream >> theChordString)
		{
			TimedChord theCurrentChord;
			theCurrentChord.onset() = theChordCounter;
			theCurrentChord.offset() = ++theChordCounter;
			theCurrentChord.label() = ChordProsemus(theChordString);
			this->m_TimedChords.push_back(theCurrentChord);
		}
	}
    ChordFile::open(inFilePath);
}

void ChordFileProsemus::close()
{
	if (m_File.is_open())
	{
		m_File.close();
	}
	if (m_FileHasChanged)
	{
		m_File.clear();
		m_File.open(m_FilePath.c_str(), std::fstream::out);
		if (!m_File.is_open())
		{
			throw std::runtime_error("Could not open file '" + m_FilePath + "' for writing");
		}
		for (size_t i = 0; i < this->m_TimedChords.size(); ++i)
		{
			m_File << ChordProsemus(this->m_TimedChords[i].label()).str() << " ";
		}
		m_File.flush();
		m_File.close();
	}
}
