#ifndef NoteMidi_h
#define NoteMidi_h

//============================================================================
/**
	Class representing a MIDI note.

	@author		Johan Pauwels
	@date		20101206
*/
//============================================================================
#include "MusOO/Note.h"

namespace MusOO
{
class NoteMidi : public Note
{
public:

	/** Default constructor. */
	NoteMidi();
	NoteMidi(std::string inNoteMidiNumber);
	NoteMidi(size_t inNoteMidiNumber);
	NoteMidi(const Note& inNote);

	/** Destructor. */
	virtual ~NoteMidi();

	NoteMidi& operator=(const size_t inNoteMidiNumber);

	const size_t number() const;

	const std::string str() const;

protected:


private:

	void setNoteNumber(const size_t inNoteMidiNumber);

};

std::ostream& operator<<(std::ostream& inOutputStream, const NoteMidi& inNote);
std::istream& operator>>(std::istream& inInputStream, NoteMidi& inNote);
}
#endif	// #ifndef NoteMidi_h
