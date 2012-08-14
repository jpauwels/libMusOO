#ifndef MidiNote_h
#define MidiNote_h

//============================================================================
/**
	Class representing a MIDI note.

	@author		Johan Pauwels
	@date		20101206
*/
//============================================================================
#include "Note.h"

class MidiNote : public Note
{
public:

	/** Default constructor. */
	MidiNote();
	MidiNote(std::string inMidiNoteNumber);
	MidiNote(size_t inMidiNoteNumber);
	MidiNote(const Note& inNote);

	/** Destructor. */
	virtual ~MidiNote();

	MidiNote& operator=(const size_t inMidiNoteNumber);

	const size_t number() const;

	const std::string str() const;

protected:


private:

	void setNoteNumber(const size_t inMidiNoteNumber);

};

#endif	// #ifndef MidiNote_h
