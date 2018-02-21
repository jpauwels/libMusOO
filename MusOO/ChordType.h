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
#include "MusOO/Set.h"
#include "MusOO/ComplexInterval.h"

namespace MusOO
{
class ChordType: public Set<SimpleInterval>
{
public:

	/* Predefined chord types */
	static ChordType none();
	static ChordType undefined();
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

	friend class Chord; //to access m_set in Chord::chromas() and m_Bass in Chord::bass()

	ChordType();
	~ChordType();
    
	bool operator==(const ChordType& inChordType) const;
	bool operator!=(const ChordType& inChordType) const;
	bool operator<(const ChordType& inChordType) const;
    
	/** Returns the basic triad the current chord can be mapped to
		@return		a ChordType object of size 3 or ChordType::rootOnly() */
	const ChordType triad(bool inWithBass) const;
	const ChordType tetrad(bool inWithBass) const;
	const bool isTriad() const;

	const ChordType withoutBass() const;

//	virtual const std::string str() const;
    
	const std::vector<ChordType> inversions() const;

	/** Modifiers */
    ChordType& addInterval(const SimpleInterval& inInterval);
	ChordType& deleteInterval(const SimpleInterval& inInterval);
	ChordType& replaceInterval(const SimpleInterval& inIntervalToReplace, const SimpleInterval& inReplacementInterval);
	ChordType& addBass(const SimpleInterval& inInterval);
	ChordType& deleteBass();
    
    const bool hasSpelling() const;
    ChordType withoutSpelling() const;
    ChordType& ignoreSpelling();

protected:
	
	void subtract(const ChordType& inType);
	void subtract(const ChordType& inType, std::set<SimpleInterval>& outRestIntervals, std::set<SimpleInterval>& outMissingIntervals) const;
    const ComplexInterval autoVoicing(const SimpleInterval& inSimpleInterval) const;
	SimpleInterval m_Bass;

private:

	// only used for construction of static modes
	ChordType(const SimpleInterval* inIntervalList, const int inNumOfIntervals, const SimpleInterval& inBass = SimpleInterval::undefined());
};
}
#endif	// #ifndef ChordType_h
