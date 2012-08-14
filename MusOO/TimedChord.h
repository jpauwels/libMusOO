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
#include "TimedLabel.h"
#include "Chord.h"

typedef TimedLabel<Chord> TimedChord;
typedef std::vector<TimedLabel<Chord> > ChordSequence;

#endif	// #ifndef TimedChord_h
