#ifndef Note_h
#define Note_h

//============================================================================
/**
	Class representing a note.

	@author		Johan Pauwels
	@date		20090120
*/
//============================================================================
#include "MusOO/Chroma.h"

namespace MusOO
{
class Note
{
public:

	const static Note& silence();

	/** Constructors. */
	Note();
// 	Note(double inFrequency);
// 	Note(std::string inNoteName);

	/** Destructor. */
	virtual ~Note();

	const bool operator==(const Note& inNote) const;

	const std::string str() const;

// 	const double frequency(double inDiapason = 440.) const;
// 	const std::string name() const;

// 	int intervalInCircleSteps(Note inNote);

	/** 
		Moves this note a given number of semitones up if the number is positive or down if it is negative.

		@param	inSemiTones		the number of semitones to move
		@return					a reference to this note
	*/
//	Note& moveSemiTones(int inSemiTones);

protected:

	Chroma m_Chroma;
	ptrdiff_t m_Octave;

private:

	Note(Chroma inChroma, ptrdiff_t inOctave);
	
};
}
#endif	// #ifndef Note_h
