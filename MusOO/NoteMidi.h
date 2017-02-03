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
	NoteMidi(const std::string& inNoteMidiNumber);
	NoteMidi(const ptrdiff_t inNoteMidiNumber);
	NoteMidi(const Note& inNote);

	/** Destructor. */
	virtual ~NoteMidi();

	NoteMidi& operator=(const ptrdiff_t inNoteMidiNumber);

	const ptrdiff_t value() const;

	const std::string str() const;

protected:


private:

	void setNoteNumber(const ptrdiff_t inNoteMidiNumber);

};

std::ostream& operator<<(std::ostream& inOutputStream, const NoteMidi& inNote);
std::istream& operator>>(std::istream& inInputStream, NoteMidi& inNote);
}
#endif	// #ifndef NoteMidi_h
