#ifndef NoteMidi_h
#define NoteMidi_h

//============================================================================
/**
	Class representing a MIDI note.

	@author		Johan Pauwels
	@date		20101206
*/
//============================================================================
#include "MusOO/NoteAbstract.h"
#include "MusOO/ChromaLetter.h"

namespace MusOO
{
class NoteMidi : public NoteAbstract<NoteMidi, ChromaLetter>
{
public:

    using NoteAbstract<NoteMidi, ChromaLetter>::NoteAbstract;
	NoteMidi(const std::string& inNoteMidiNumber);
	NoteMidi(const ptrdiff_t inNoteMidiNumber);

//	NoteMidi& operator=(const ptrdiff_t inNoteMidiNumber);

	const ptrdiff_t value() const;

	const std::string str() const;

private:

	void setNoteNumber(const ptrdiff_t inNoteMidiNumber);

};
}
#endif	// #ifndef NoteMidi_h
