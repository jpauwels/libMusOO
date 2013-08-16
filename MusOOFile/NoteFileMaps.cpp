//============================================================================
/**
	Implementation file for NoteFileMaps.h
	
	@author		Johan Pauwels
	@date		20101203
*/
//============================================================================

// Includes
#include <vector>
#include "MusOOFile/NoteFileMaps.h"

using std::vector;
using std::string;
using namespace MusOO;

const std::string NoteFileMaps::s_HeaderInit[] = {string("OnsetTime"), string("OffsetTime"), string("MidiPitch")};

NoteFileMaps::NoteFileMaps()
: m_LabFile(vector<string>(s_HeaderInit, s_HeaderInit+3))
{
}

NoteFileMaps::NoteFileMaps(std::string inFileName)
: m_LabFile(vector<string>(s_HeaderInit, s_HeaderInit+3))
{
	open(inFileName);
}

NoteFileMaps::~NoteFileMaps()
{
	// Nothing to do...
}

void NoteFileMaps::open(const std::string& inFileName)
{
	this->m_FileHasChanged = false;
	m_LabFile.open(inFileName);
	NoteMidiSequence theNoteNumbers = m_LabFile.readAll();
	this->m_TimedNotes.resize(theNoteNumbers.size());
	for (size_t i = 0; i < theNoteNumbers.size(); ++i)
	{
		this->m_TimedNotes[i] = theNoteNumbers[i]; 
	}
}

void NoteFileMaps::close()
{
	if (m_FileHasChanged)
	{
		NoteFile::close();
		NoteMidiSequence theNoteNumbers(this->m_TimedNotes.size());
		for (size_t i = 0; i < theNoteNumbers.size(); ++i)
		{
			theNoteNumbers[i] = this->m_TimedNotes[i]; 
		}
		m_LabFile.writeAll(theNoteNumbers);
	}
}
