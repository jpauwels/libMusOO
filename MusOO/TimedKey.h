#ifndef TimedKey_h
#define TimedKey_h

//============================================================================
/**
	Class representing a key with onset and offset.

	@author		Johan Pauwels
	@date		20100401
*/
//============================================================================
#include <vector>
#include "TimedLabel.h"
#include "Key.h"

typedef TimedLabel<Key> TimedKey;
typedef std::vector<TimedKey> KeySequence;

#endif	// #ifndef TimedKey_h
