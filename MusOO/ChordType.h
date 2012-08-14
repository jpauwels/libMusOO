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
#include "Interval.h"

class ChordType
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

	friend class Chord; //to access m_Formula in Chord::chromaList()
	friend class LerdahlDistance; //to access m_Formula in LerdahlDistance::basicSpace()

	ChordType();
	~ChordType();

	/** Operators */
	bool operator==(const ChordType& inChordType) const;
	bool operator!=(const ChordType& inChordType) const;
	bool operator<(const ChordType& inChordType) const;

	/** Returns the basic triad the current chord can be mapped to
		@return		a ChordType object of size 3 or ChordType::rootOnly() */
	const ChordType triad() const;
	const ChordType tetrad() const;
	const bool isTriad() const;

	const ChordType withoutBass() const;

	const size_t size() const;

//	virtual const std::string str() const;

	/** 
	Checks if this chord type is equal to a given one

	@param		inType		the type to compare with this one
	@return		true if the types are equal
	*/
	const bool equalTypes(const ChordType inType) const;

	/**
	Checks if this chord type contains all the notes of a given chord type

	@param		inType1		the type contained by this type
	@return		true if this type contains all notes of <inType>
	*/
	const bool contains(const ChordType inType) const;
	
	const bool contains(const Interval& inInterval) const;

	const bool hasChordalBass() const;

	/** Modifiers */
	ChordType& addInterval(const Interval& inInterval);
	ChordType& addBass(const Interval& inInterval);
	ChordType& deleteInterval(const Interval& inInterval);
	ChordType& replaceInterval(const Interval& inIntervalToReplace, const Interval& inReplacementInterval);

	/**
	Returns the interval of a given diatonic number
	@param	inDiatonicNumber	the diatonic numnber the interval should have
	@return an Interval of the given diatonic number or Interval::none() if no such interval belongs to the chord type
	*/
	const Interval& getInterval(const size_t inDiatonicNumber) const;

protected:
	
	void subtract(const ChordType& inType);
	std::set<Interval> m_Formula;
	Interval m_Bass;

private:

	// only used for construction of static modes
	ChordType(const Interval* inIntervalList, const int inNumOfIntervals, const Interval& inBass = Interval::unknown());
};

#endif	// #ifndef ChordType_h
