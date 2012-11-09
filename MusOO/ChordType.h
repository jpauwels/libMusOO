#ifndef ChordType_h
#define ChordType_h

//============================================================================
/**
	Class representing .

	@author		Johan Pauwels
	@date		20100913
*/
//============================================================================
#include <string>
#include <set>
#include "IntervalClassSet.h"

class ChordType: public IntervalClassSet
{
public:

	/* Predefined chord types */
	static ChordType none();
	//root only
	static ChordType rootOnly();
	//triads
	static ChordType major();
	static ChordType minor();
	static ChordType augmented();
	static ChordType diminished();
	static ChordType suspendedSecond();
	static ChordType suspendedFourth();
	static ChordType majorFlatFifth();
	static ChordType minorSharpFifth();
	//sevenths
	static ChordType dominantSeventh();
	static ChordType majorSeventh();
	static ChordType minorSeventh();
	static ChordType diminishedSeventh();
	static ChordType augmentedSeventh();
	static ChordType augmentedMajorSeventh();
	static ChordType halfDiminished();
	static ChordType minorMajorSeventh();
	static ChordType suspendedFourthSeventh();
	//sixths
	static ChordType majorSixth();
	static ChordType minorSixth();
	//ninths
	static ChordType dominantNinth();
	static ChordType majorNinth();
	static ChordType minorNinth();
	static ChordType suspendedFourthNinth();
	//elevenths
	static ChordType dominantEleventh();
	static ChordType majorEleventh();
	static ChordType minorEleventh();
	//thirteenths
	static ChordType dominantThirteenth();
	static ChordType majorThirteenth();
	static ChordType minorThirteenth();
	//augmented sixths
	static ChordType italianSixth();
	static ChordType frenchSixth();
	static ChordType germanSixth();
	//other
	static ChordType power();
	static ChordType tristan();

	friend class Chord; //to access m_IntervalList in Chord::chromas() and m_Bass in Chord::bass()

	ChordType();
	~ChordType();
    
	bool operator==(const ChordType& inChordType) const;
	bool operator!=(const ChordType& inChordType) const;
	bool operator<(const ChordType& inChordType) const;
    
	/** Returns the basic triad the current chord can be mapped to
		@return		a ChordType object of size 3 or ChordType::rootOnly() */
	const ChordType triad() const;
	const ChordType tetrad() const;
	const bool isTriad() const;

	const ChordType withoutBass() const;

//	virtual const std::string str() const;
    
	const std::vector<ChordType> inversions() const;

	/** Modifiers */
    ChordType& addInterval(const Interval& inInterval);
	ChordType& deleteInterval(const Interval& inInterval);
	ChordType& replaceInterval(const Interval& inIntervalToReplace, const Interval& inReplacementInterval);
	ChordType& addBass(const Interval& inInterval);
	ChordType& deleteBass();
    
    const bool hasSpelling() const;
    ChordType& ignoreSpelling();

protected:
	
	void subtract(const ChordType& inType);
	void subtract(const ChordType& inType, std::vector<Interval>& outRestIntervals, std::vector<Interval>& outMissingIntervals) const;
	Interval m_Bass;

private:

	// only used for construction of static modes
	ChordType(const Interval* inIntervalList, const int inNumOfIntervals, const Interval& inBass = Interval::undefined());
};

#endif	// #ifndef ChordType_h
