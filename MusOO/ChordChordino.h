#ifndef ChordChordino_h
#define ChordChordino_h

//============================================================================
	/**
	Class representing a chord with syntax as used by the Chordino Vamp plugin

	@author		Johan Pauwels
	@date		20090119
*/
//============================================================================
#include <string>
#include <map>
#include "MusOO/Chord.h"

namespace MusOO
{
class ChordChordino : public Chord
{
public:

	/** Default constructor. */
	ChordChordino();
	ChordChordino(std::string inChordString);
	// copy constructor
	ChordChordino(const Chord& inChord);

	/** Destructor. */
	virtual ~ChordChordino();

	const std::string str() const;

protected:


private:


};

std::ostream& operator<<(std::ostream& inOutputStream, const ChordChordino& inChord);
std::istream& operator>>(std::istream& inInputStream, ChordChordino& inChord);
}
#endif	// #ifndef ChordChordino_h
