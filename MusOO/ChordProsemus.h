#ifndef ChordProsemus_h
#define ChordProsemus_h

//============================================================================
/**
	Class representing a chord with Prosemus syntax.

	@author		Johan Pauwels
	@date		20101220
*/
//============================================================================
#include <string>
#include "MusOO/Chord.h"

namespace MusOO
{
class ChordProsemus : public Chord
{
public:

	/** Default constructor. */
	ChordProsemus();
	ChordProsemus(const std::string& inChordString);
	// copy constructor
	ChordProsemus(const Chord& inChord);

	/** Destructor. */
	virtual ~ChordProsemus();

	const std::string str() const;

protected:


private:


};
}
#endif	// #ifndef ChordProsemus_h
