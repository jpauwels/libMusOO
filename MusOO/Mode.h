#ifndef Mode_h
#define Mode_h

//============================================================================
/**
	Class representing a key mode.

	@author		Johan Pauwels
	@date		20100401
*/
//============================================================================
#include "MusOO/IntervalClassSet.h"

namespace MusOO
{
class RelativeChord;
class Interval;

class Mode : public IntervalClassSet
{
public:
    
    friend class Key; // to access m_IntervalList in Key::chromas()
    
	static Mode none();
	static Mode major();
	static Mode minorNatural();
	static Mode minorHarmonic();
	static Mode minorMelodic();
	static Mode minorComposed();
	static Mode dorian();
	static Mode phrygian();
	static Mode lydian();
	static Mode mixolydian();
	static Mode aeolian();
	static Mode locrian();
	static Mode modal();
    
	/** Default constructor. */
	Mode();
	//Mode(const Mode& inMode) = default;
	virtual ~Mode();

	size_t diatonicCircleDistance(const Interval& inInterval1, const Interval& inInterval2) const;

	/** Returns the diatonic relative triad of a given degree in this mode 
	@param	inDegree			the degree on which a diatonic chord needs to be constructed 
	@return		a relative triad diatonic in this mode built on a given degree */
	RelativeChord diatonicTriad(size_t inDegree) const;

	const size_t chromaticCOFDistance(Interval inRootInterval, const Mode& inMode) const;
    
    Mode& addInterval(const Interval& inInterval);
	Mode& deleteInterval(const Interval& inInterval);
	Mode& replaceInterval(const Interval& inIntervalToReplace, const Interval& inReplacementInterval);

protected:
    
	/* Returns position on diatonic circle of fifths where 0 equals IV, 1 is I, 2 is V and so on */
	ptrdiff_t diatonicPosition(const ptrdiff_t inDiatonicNumber) const;

private:

	// only used for construction of static modes
	Mode(const Interval* inIntervalList, const int inNumOfIntervals);
};
}
#endif	// #ifndef Mode_h
