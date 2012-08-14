//============================================================================
/**
	Implementation file for NoteFile.h
	
	@author		Johan Pauwels
	@date		20101203
*/
//============================================================================

// Includes
#include "NoteFile.h"

NoteFile::NoteFile()
{
	
}

NoteFile::~NoteFile()
{
	// Nothing to do...
}

NoteSequence& NoteFile::readAll()
{
	return m_TimedNotes;
}

void NoteFile::writeAll(NoteSequence& inTimedNotes)
{
	m_TimedNotes = inTimedNotes;
	m_FileHasChanged = true;
}

bool NoteFile::isEmpty() const
{
	return m_TimedNotes.empty();
}


void NoteFile::open(const std::string& inFileName)
{
}

void NoteFile::close()
{
}
