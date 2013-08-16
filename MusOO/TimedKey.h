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
#include "MusOO/TimedLabel.h"
#include "MusOO/Key.h"

namespace MusOO
{
typedef TimedLabel<Key> TimedKey;
typedef std::vector<TimedKey> TimedKeySequence;
}
#endif	// #ifndef TimedKey_h
