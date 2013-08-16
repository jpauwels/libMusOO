#ifndef TimedNote_h
#define TimedNote_h

//============================================================================
/**
	Class representing a note with onset and offset time.

	@author		Johan Pauwels
	@date		20101203
*/
//============================================================================
#include <vector>
#include "TimedLabel.h"
#include "Note.h"

namespace MusOO
{
typedef TimedLabel<Note> TimedNote;
typedef std::vector<TimedLabel<Note> > NoteSequence;
}
#endif	// #ifndef TimedNote_h
