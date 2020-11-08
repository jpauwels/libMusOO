#ifndef TimedChord_h
#define TimedChord_h

//============================================================================
/**
	Class representing a chord with onset and offset.

	@author		Johan Pauwels
	@date		20100603
*/
//============================================================================
#include "MusOO/TimedLabel.h"
#include "MusOO/ChordAbstract.h"
#include <vector>

namespace MusOO
{
typedef TimedLabel<Chord> TimedChord;
typedef std::vector<TimedLabel<Chord> > TimedChordSequence;
}
#endif	// #ifndef TimedChord_h
