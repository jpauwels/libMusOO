#ifndef Mode_h
#define Mode_h

//============================================================================
/**
	Class representing a key mode.

	@author		Johan Pauwels
	@date		20100401
*/
//============================================================================
#include <set>
#include <string>
#include "Interval.h"

class RelativeChord;

class Mode
{
public:

	static const Mode& noMode();
	static const Mode& major();
	static const Mode& minorNatural();
	static const Mode& minorHarmonic();
	static const Mode& minorMelodic();
	static const Mode& minorComposed();
	static const Mode& dorian();
	static const Mode& phrygian();
	static const Mode& lydian();
	static const Mode& mixolydian();
	static const Mode& aeolian();
	static const Mode& locrian();
	static const Mode& modal();

	friend class Key; // to access m_IntervalList in Key::chromaList()
	friend class LerdahlDistance; //to access m_IntervalList in LerdahlDistance::basicSpace()
	/** Default constructor. */
	Mode();
	//copy constructor
	Mode(const Mode& inMode);
	virtual ~Mode();

	// operator= default implementation
	bool operator==(const Mode& inMode) const;
	bool operator!=(const Mode& inMode) const;
	bool operator<(const Mode& inMode) const;

	bool isMajor() const;
	bool isMinor() const;

	const size_t size() const;

	size_t diatonicCircleDistance(const Interval& inInterval1, const Interval& inInterval2) const;
	/**
	Returns the interval of a given diatonic number
	@param	inDiatonicNumber	the diatonic numnber the interval should have
	@return an Interval of the given diatonic number or Interval::none() if no such interval belongs to the chord type
	*/
	const Interval& getDiatonicInterval(const size_t inDiatonicNumber) const;
	/** Returns the diatonic relative triad of a given degree in this mode 
	@param	inDegree			the degree on which a diatonic chord needs to be constructed 
	@return		a relative triad diatonic in this mode built on a given degree */
	RelativeChord diatonicTriad(size_t inDegree) const;

	const size_t chromaticCOFDistance(Interval inRootInterval, const Mode& inMode) const;

protected:
	
	virtual const std::string str() const;

	std::set<Interval> m_IntervalList;
	/* Returns position on diatonic circle of fifths where 0 equals IV, 1 is I, 2 is V and so on */
	ptrdiff_t diatonicPosition(const ptrdiff_t inDiatonicNumber) const;

private:

	// only used for construction of static modes
	Mode(const Interval* inIntervalList, const int inNumOfIntervals);
};

#endif	// #ifndef Mode_h
