#ifndef MapsNoteFile_h
#define MapsNoteFile_h

//============================================================================
/**
	Class representing a note file according to the MAPS syntax.

	@author		Johan Pauwels
	@date		20101203
*/
//============================================================================
#include <string>
#include <vector>
#include "NoteFile.h"
#include "MidiNote.h"
#include "LabFile.h"

class MapsNoteFile : public NoteFile
{
public:

	/** Default constructor. */
	MapsNoteFile();
	MapsNoteFile(std::string inFileName);

	/** Destructor. */
	virtual ~MapsNoteFile();

	virtual void open(const std::string& inFileName);
	virtual void close();

protected:


private:

	typedef TimedLabel<MidiNote> TimedMidiNote;
	typedef std::vector<TimedMidiNote> MidiNoteSequence;

	LabFile<MidiNote> m_LabFile;
	static const std::string s_HeaderInit[];


};

#endif	// #ifndef MapsNoteFile_h
