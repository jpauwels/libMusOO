#ifndef ChordQMUL_h
#define ChordQMUL_h

//============================================================================
	/**
	Class representing a chord with syntax defined by Harte et al.

	@author		Johan Pauwels
	@date		20090119
*/
//============================================================================
#include <string>
#include <map>
#include "MusOO/Chord.h"

namespace MusOO
{
class ChordQMUL : public Chord
{
public:

	/** Default constructor. */
	ChordQMUL();
	ChordQMUL(const std::string& inChordString);
	// copy constructor
	ChordQMUL(const Chord& inChord);

	/** Destructor. */
	virtual ~ChordQMUL();

	const std::string str() const;

protected:


private:


};

std::ostream& operator<<(std::ostream& inOutputStream, const ChordQMUL& inChord);
std::istream& operator>>(std::istream& inInputStream, ChordQMUL& inChord);
}
#endif	// #ifndef ChordQMUL_h
