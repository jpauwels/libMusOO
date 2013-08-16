#ifndef TimedChord_h
#define TimedChord_h

//============================================================================
/**
	Class representing a chord with onset and offset.

	@author		Johan Pauwels
	@date		20100603
*/
//============================================================================
#include <vector>
#include "MusOO/TimedLabel.h"
#include "MusOO/Chord.h"

namespace MusOO
{
typedef TimedLabel<Chord> TimedChord;
typedef std::vector<TimedLabel<Chord> > TimedChordSequence;
}
#endif	// #ifndef TimedChord_h
