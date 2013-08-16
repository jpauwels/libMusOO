#ifndef NoteFile_h
#define NoteFile_h

//============================================================================
/**
	Abstract base class representing a file on disc containing notes with 
	timestamps.

	@author		Johan Pauwels
	@date		20101203
*/
//============================================================================
#include "MusOO/TimedNote.h"

namespace MusOO
{
class NoteFile
{
public:

	NoteFile();
	/** Destructor. */
	virtual ~NoteFile();

	NoteSequence& readAll();
	void writeAll(NoteSequence& inTimedNotes);
	bool isEmpty() const;

	virtual void open(const std::string& inFileName) = 0;
	virtual void close() = 0;

protected:

	bool m_FileHasChanged;
	NoteSequence m_TimedNotes;


};
}
#endif	// #ifndef NoteFile_h
