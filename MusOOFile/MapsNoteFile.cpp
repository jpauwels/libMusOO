//============================================================================
/**
	Implementation file for MapsNoteFile.h
	
	@author		Johan Pauwels
	@date		20101203
*/
//============================================================================

// Includes
#include <vector>
#include "MapsNoteFile.h"

using std::vector;
using std::string;

const std::string MapsNoteFile::s_HeaderInit[] = {string("OnsetTime"), string("OffsetTime"), string("MidiPitch")};

MapsNoteFile::MapsNoteFile()
: m_LabFile(vector<string>(s_HeaderInit, s_HeaderInit+3))
{
}

MapsNoteFile::MapsNoteFile(std::string inFileName)
: m_LabFile(vector<string>(s_HeaderInit, s_HeaderInit+3))
{
	open(inFileName);
}

MapsNoteFile::~MapsNoteFile()
{
	// Nothing to do...
}

void MapsNoteFile::open(const std::string& inFileName)
{
	this->m_FileHasChanged = false;
	m_LabFile.open(inFileName);
	MidiNoteSequence theNoteNumbers = m_LabFile.readAll();
	this->m_TimedNotes.resize(theNoteNumbers.size());
	for (size_t i = 0; i < theNoteNumbers.size(); ++i)
	{
		this->m_TimedNotes[i] = theNoteNumbers[i]; 
	}
}

void MapsNoteFile::close()
{
	if (m_FileHasChanged)
	{
		NoteFile::close();
		MidiNoteSequence theNoteNumbers(this->m_TimedNotes.size());
		for (size_t i = 0; i < theNoteNumbers.size(); ++i)
		{
			theNoteNumbers[i] = this->m_TimedNotes[i]; 
		}
		m_LabFile.writeAll(theNoteNumbers);
	}
}
