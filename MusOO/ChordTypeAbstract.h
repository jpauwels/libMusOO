#ifndef ChordType_h
#define ChordType_h

//============================================================================
/**
	Class representing .

	@author		Johan Pauwels
	@date		20100913
*/
//============================================================================
#include "MusOO/Set.h"
#include "MusOO/ComplexInterval.h"
#include <string>
#include <set>

namespace MusOO
{
template <typename ChordType>
class ChordTypeAbstract: public Set<SimpleInterval, ChordType>
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
    
    template <typename OtherChordType> friend class ChordTypeAbstract; // to access m_set and m_Bass from other ChordType types
    template <typename Chord, typename Chroma, typename OtherChordType> friend class ChordAbstract; //to access m_Bass in ChordAbstract::bass()

    /** Default constructor. */
	ChordTypeAbstract();
    /** Generalised copy constructor. */
    template <typename OtherChordType>
    ChordTypeAbstract(const ChordTypeAbstract<OtherChordType>& inChordType);
    
    /** Destructor. */
    virtual ~ChordTypeAbstract();

	const bool operator==(const ChordType& inChordType) const;
	const bool operator!=(const ChordType& inChordType) const;
	const bool operator<(const ChordType& inChordType) const;
    
	/** Returns the basic triad the current chord can be mapped to
		@return		a ChordType object of size 3 or ChordType::rootOnly() */
	const ChordType triad(bool inWithBass) const;
	const ChordType tetrad(bool inWithBass) const;
	const bool isTriad() const;

	const ChordType withoutBass() const;

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

    virtual const std::string str() const = 0;
    
protected:
	
	void subtract(const ChordType& inType);
	void subtract(const ChordType& inType, std::set<SimpleInterval>& outRestIntervals, std::set<SimpleInterval>& outMissingIntervals) const;
    const ComplexInterval autoVoicing(const SimpleInterval& inSimpleInterval) const;
	SimpleInterval m_Bass;

private:

	// only used for construction of static modes
	ChordTypeAbstract(const SimpleInterval* const inIntervalList, const int inNumOfIntervals, const SimpleInterval& inBass = SimpleInterval::undefined());
};


template <typename ChordType>
std::ostream& operator<<(std::ostream& inOutputStream, const ChordTypeAbstract<ChordType>& inChordType)
{
    inOutputStream << inChordType.str();
    return inOutputStream;
}

template <typename ChordType>
std::istream& operator>>(std::istream& inInputStream, ChordTypeAbstract<ChordType>& inChordType)
{
    std::string theChordTypeString;
    inInputStream >> theChordTypeString;
    inChordType = ChordType(theChordTypeString);
    return inInputStream;
}


/****************************/
/* Static factory functions */
/****************************/
template <typename ChordType>
ChordType ChordTypeAbstract<ChordType>::none()
{
    static const ChordType none;
    return none;
}
template <typename ChordType>
ChordType ChordTypeAbstract<ChordType>::undefined()
{
    const SimpleInterval undefinedList[] = {SimpleInterval::undefined()};
    static const ChordType undefined(undefinedList, 1);
    return undefined;
}
template <typename ChordType>
ChordType ChordTypeAbstract<ChordType>::rootOnly()
{
    const SimpleInterval rootOnlyList[] = {SimpleInterval::unison()};
    static const ChordType rootOnly(rootOnlyList, 1);
    return rootOnly;
}
template <typename ChordType>
ChordType ChordTypeAbstract<ChordType>::major()
{
    const SimpleInterval majorList[] = {SimpleInterval::unison(), SimpleInterval::majorThird(), SimpleInterval::perfectFifth()};
    static const ChordType major(majorList, 3);
    return major;
}
template <typename ChordType>
ChordType ChordTypeAbstract<ChordType>::minor()
{
    const SimpleInterval minorList[] = {SimpleInterval::unison(), SimpleInterval::minorThird(), SimpleInterval::perfectFifth()};
    static const ChordType minor(minorList, 3);
    return minor;
}
template <typename ChordType>
ChordType ChordTypeAbstract<ChordType>::augmented()
{
    const SimpleInterval augmentedList[] = {SimpleInterval::unison(), SimpleInterval::majorThird(), SimpleInterval::augmentedFifth()};
    static const ChordType augmented(augmentedList, 3);
    return augmented;
}
template <typename ChordType>
ChordType ChordTypeAbstract<ChordType>::diminished()
{
    const SimpleInterval diminishedList[] = {SimpleInterval::unison(), SimpleInterval::minorThird(), SimpleInterval::diminishedFifth()};
    static const ChordType diminished(diminishedList, 3);
    return diminished;
}
template <typename ChordType>
ChordType ChordTypeAbstract<ChordType>::suspendedSecond()
{
    const SimpleInterval suspendedSecondList[] = {SimpleInterval::unison(), SimpleInterval::majorSecond(), SimpleInterval::perfectFifth()};
    static const ChordType suspendedSecond(suspendedSecondList, 3);
    return suspendedSecond;
}
template <typename ChordType>
ChordType ChordTypeAbstract<ChordType>::suspendedFourth()
{
    const SimpleInterval suspendedFourthList[] = {SimpleInterval::unison(), SimpleInterval::perfectFourth(), SimpleInterval::perfectFifth()};
    static const ChordType suspendedFourth(suspendedFourthList, 3);
    return suspendedFourth;
}
template <typename ChordType>
ChordType ChordTypeAbstract<ChordType>::majorFlatFifth()
{
    const SimpleInterval majorFlatFifthList[] = {SimpleInterval::unison(), SimpleInterval::majorThird(), SimpleInterval::diminishedFifth()};
    static const ChordType majorFlatFifth(majorFlatFifthList, 3);
    return majorFlatFifth;
}
template <typename ChordType>
ChordType ChordTypeAbstract<ChordType>::minorSharpFifth()
{
    const SimpleInterval minorSharpFifthList[] = {SimpleInterval::unison(), SimpleInterval::minorThird(), SimpleInterval::augmentedFifth()};
    static const ChordType minorSharpFifth(minorSharpFifthList, 3);
    return minorSharpFifth;
}
template <typename ChordType>
ChordType ChordTypeAbstract<ChordType>::dominantSeventh()
{
    const SimpleInterval dominantSeventhList[] = {SimpleInterval::unison(), SimpleInterval::majorThird(), SimpleInterval::perfectFifth(), SimpleInterval::minorSeventh()};
    static const ChordType dominantSeventh(dominantSeventhList, 4);
    return dominantSeventh;
}
template <typename ChordType>
ChordType ChordTypeAbstract<ChordType>::majorSeventh()
{
    const SimpleInterval majorSeventhList[] = {SimpleInterval::unison(), SimpleInterval::majorThird(), SimpleInterval::perfectFifth(), SimpleInterval::majorSeventh()};
    static const ChordType majorSeventh(majorSeventhList, 4);
    return majorSeventh;
}
template <typename ChordType>
ChordType ChordTypeAbstract<ChordType>::minorSeventh()
{
    const SimpleInterval minorSeventhList[] = {SimpleInterval::unison(), SimpleInterval::minorThird(), SimpleInterval::perfectFifth(), SimpleInterval::minorSeventh()};
    static const ChordType minorSeventh(minorSeventhList, 4);
    return minorSeventh;
}
template <typename ChordType>
ChordType ChordTypeAbstract<ChordType>::diminishedSeventh()
{
    const SimpleInterval diminishedSeventhList[] = {SimpleInterval::unison(), SimpleInterval::minorThird(), SimpleInterval::diminishedFifth(), SimpleInterval::diminishedSeventh()};
    static const ChordType diminishedSeventh(diminishedSeventhList, 4);
    return diminishedSeventh;
}
template <typename ChordType>
ChordType ChordTypeAbstract<ChordType>::augmentedSeventh()
{
    const SimpleInterval augmentedSeventhList[] = {SimpleInterval::unison(), SimpleInterval::majorThird(), SimpleInterval::augmentedFifth(), SimpleInterval::minorSeventh()};
    static const ChordType augmentedSeventh(augmentedSeventhList, 4);
    return augmentedSeventh;
}
template <typename ChordType>
ChordType ChordTypeAbstract<ChordType>::augmentedMajorSeventh()
{
    const SimpleInterval augmentedMajorSeventhList[] = {SimpleInterval::unison(), SimpleInterval::majorThird(), SimpleInterval::augmentedFifth(), SimpleInterval::majorSeventh()};
    static const ChordType augmentedMajorSeventh(augmentedMajorSeventhList, 4);
    return augmentedMajorSeventh;
}
template <typename ChordType>
ChordType ChordTypeAbstract<ChordType>::halfDiminished()
{
    const SimpleInterval halfDiminishedList[] = {SimpleInterval::unison(), SimpleInterval::minorThird(), SimpleInterval::diminishedFifth(), SimpleInterval::minorSeventh()};
    static const ChordType halfDiminished(halfDiminishedList, 4);
    return halfDiminished;
}
template <typename ChordType>
ChordType ChordTypeAbstract<ChordType>::minorMajorSeventh()
{
    const SimpleInterval minorMajorList[] = {SimpleInterval::unison(), SimpleInterval::minorThird(), SimpleInterval::perfectFifth(), SimpleInterval::majorSeventh()};
    static const ChordType minorMajor(minorMajorList, 4);
    return minorMajor;
}
template <typename ChordType>
ChordType ChordTypeAbstract<ChordType>::majorSixth()
{
    const SimpleInterval majorSixthList[] = {SimpleInterval::unison(), SimpleInterval::majorThird(), SimpleInterval::perfectFifth(), SimpleInterval::majorSixth()};
    static const ChordType majorSixth(majorSixthList, 4);
    return majorSixth;
}
template <typename ChordType>
ChordType ChordTypeAbstract<ChordType>::minorSixth()
{
    const SimpleInterval minorSixthList[] = {SimpleInterval::unison(), SimpleInterval::minorThird(), SimpleInterval::perfectFifth(), SimpleInterval::majorSixth()};
    static const ChordType minorSixth(minorSixthList, 4);
    return minorSixth;
}
template <typename ChordType>
ChordType ChordTypeAbstract<ChordType>::dominantNinth()
{
    const SimpleInterval dominantNinthList[] = {SimpleInterval::unison(), SimpleInterval::majorThird(), SimpleInterval::perfectFifth(), SimpleInterval::minorSeventh(), SimpleInterval::majorSecond()};
    static const ChordType dominantNinth(dominantNinthList, 5);
    return dominantNinth;
}
template <typename ChordType>
ChordType ChordTypeAbstract<ChordType>::majorNinth()
{
    const SimpleInterval majorNinthList[] = {SimpleInterval::unison(), SimpleInterval::majorThird(), SimpleInterval::perfectFifth(), SimpleInterval::majorSeventh(), SimpleInterval::majorSecond()};
    static const ChordType majorNinth(majorNinthList, 5);
    return majorNinth;
}
template <typename ChordType>
ChordType ChordTypeAbstract<ChordType>::minorNinth()
{
    const SimpleInterval minorNinthList[] = {SimpleInterval::unison(), SimpleInterval::minorThird(), SimpleInterval::perfectFifth(), SimpleInterval::minorSeventh(), SimpleInterval::majorSecond()};
    static const ChordType minorNinth(minorNinthList, 5);
    return minorNinth;
}
template <typename ChordType>
ChordType ChordTypeAbstract<ChordType>::dominantEleventh()
{
    const SimpleInterval dominantEleventhList[] = {SimpleInterval::unison(), SimpleInterval::majorThird(), SimpleInterval::perfectFifth(), SimpleInterval::minorSeventh(), SimpleInterval::majorSecond(), SimpleInterval::perfectFourth()};
    static const ChordType dominantEleventh(dominantEleventhList, 6);
    return dominantEleventh;
}
template <typename ChordType>
ChordType ChordTypeAbstract<ChordType>::majorEleventh()
{
    const SimpleInterval majorEleventhList[] = {SimpleInterval::unison(), SimpleInterval::majorThird(), SimpleInterval::perfectFifth(), SimpleInterval::majorSeventh(), SimpleInterval::majorSecond(), SimpleInterval::perfectFourth()};
    static const ChordType majorEleventh(majorEleventhList, 6);
    return majorEleventh;
}
template <typename ChordType>
ChordType ChordTypeAbstract<ChordType>::minorEleventh()
{
    const SimpleInterval minorEleventhList[] = {SimpleInterval::unison(), SimpleInterval::minorThird(), SimpleInterval::perfectFifth(), SimpleInterval::minorSeventh(), SimpleInterval::majorSecond(), SimpleInterval::perfectFourth()};
    static const ChordType minorEleventh(minorEleventhList, 6);
    return minorEleventh;
}
template <typename ChordType>
ChordType ChordTypeAbstract<ChordType>::dominantThirteenth()
{
    const SimpleInterval dominantThirteenthList[] = {SimpleInterval::unison(), SimpleInterval::majorThird(), SimpleInterval::perfectFifth(), SimpleInterval::minorSeventh(), SimpleInterval::majorSecond(), SimpleInterval::perfectFourth(), SimpleInterval::majorSixth()};
    static const ChordType dominantThirteenth(dominantThirteenthList, 7);
    return dominantThirteenth;
}
template <typename ChordType>
ChordType ChordTypeAbstract<ChordType>::majorThirteenth()
{
    const SimpleInterval majorThirteenthList[] = {SimpleInterval::unison(), SimpleInterval::majorThird(), SimpleInterval::perfectFifth(), SimpleInterval::majorSeventh(), SimpleInterval::majorSecond(), SimpleInterval::perfectFourth(), SimpleInterval::majorSixth()};
    static const ChordType majorThirteenth(majorThirteenthList, 7);
    return majorThirteenth;
}
template <typename ChordType>
ChordType ChordTypeAbstract<ChordType>::minorThirteenth()
{
    const SimpleInterval minorThirteenthList[] = {SimpleInterval::unison(), SimpleInterval::minorThird(), SimpleInterval::perfectFifth(), SimpleInterval::minorSeventh(), SimpleInterval::majorSecond(), SimpleInterval::perfectFourth(), SimpleInterval::majorSixth()};
    static const ChordType minorThirteenth(minorThirteenthList, 7);
    return minorThirteenth;
}
template <typename ChordType>
ChordType ChordTypeAbstract<ChordType>::suspendedFourthSeventh()
{
    const SimpleInterval suspendedFourthSeventhList[] = {SimpleInterval::unison(), SimpleInterval::perfectFourth(), SimpleInterval::perfectFifth(), SimpleInterval::minorSeventh()};
    static const ChordType suspendedFourthSeventh(suspendedFourthSeventhList, 4);
    return suspendedFourthSeventh;
}
template <typename ChordType>
ChordType ChordTypeAbstract<ChordType>::suspendedFourthNinth()
{
    const SimpleInterval suspendedFourthNinthList[] = {SimpleInterval::unison(), SimpleInterval::perfectFourth(), SimpleInterval::perfectFifth(), SimpleInterval::minorSeventh(), SimpleInterval::majorSecond()};
    static const ChordType suspendedFourthNinth(suspendedFourthNinthList, 5);
    return suspendedFourthNinth;
}
template <typename ChordType>
ChordType ChordTypeAbstract<ChordType>::italianSixth()
{
    const SimpleInterval italianSixthList[] = {SimpleInterval::unison(), SimpleInterval::augmentedFourth(), SimpleInterval::minorSixth()};
    static const ChordType italianSixth(italianSixthList, 3, SimpleInterval::minorSixth());
    return italianSixth;
}
template <typename ChordType>
ChordType ChordTypeAbstract<ChordType>::frenchSixth()
{
    const SimpleInterval frenchSixthList[] = {SimpleInterval::unison(), SimpleInterval::majorSecond(), SimpleInterval::augmentedFourth(), SimpleInterval::minorSixth()};
    static const ChordType frenchSixth(frenchSixthList, 4, SimpleInterval::minorSixth());
    return frenchSixth;
}
template <typename ChordType>
ChordType ChordTypeAbstract<ChordType>::germanSixth()
{
    const SimpleInterval germanSixthList[] = {SimpleInterval::unison(), SimpleInterval::minorThird(), SimpleInterval::augmentedFourth(), SimpleInterval::minorSixth()};
    static const ChordType germanSixth(germanSixthList, 4, SimpleInterval::minorSixth());
    return germanSixth;
}
template <typename ChordType>
ChordType ChordTypeAbstract<ChordType>::power()
{
    const SimpleInterval powerList[] = {SimpleInterval::unison(), SimpleInterval::perfectFifth()};
    static const ChordType power(powerList, 2);
    return power;
}
template <typename ChordType>
ChordType ChordTypeAbstract<ChordType>::tristan()
{
    const SimpleInterval tristanList[] = {SimpleInterval::unison(),SimpleInterval::augmentedFourth(), SimpleInterval::augmentedSixth(), SimpleInterval::augmentedSecond()};
    static const ChordType tristan(tristanList, 4);
    return tristan;
}

/*******************************/
/* Constructors and destructor */
/*******************************/
template <typename ChordType>
ChordTypeAbstract<ChordType>::ChordTypeAbstract()
: Set<SimpleInterval, ChordType>(), m_Bass(SimpleInterval::undefined())
{
}

template <typename ChordType>
template <typename OtherChordType>
ChordTypeAbstract<ChordType>::ChordTypeAbstract(const ChordTypeAbstract<OtherChordType>& inChordType)
: Set<SimpleInterval, ChordType>(inChordType), m_Bass(inChordType.m_Bass)
{
}

template <typename ChordType>
ChordTypeAbstract<ChordType>::ChordTypeAbstract(const SimpleInterval* const inIntervalList, const int inNumOfIntervals, const SimpleInterval& inBass /*= SimpleInterval::undefined()*/)
: Set<SimpleInterval, ChordType>(inIntervalList, inNumOfIntervals), m_Bass(inBass)
{
}

template <typename ChordType>
ChordTypeAbstract<ChordType>::~ChordTypeAbstract()
{
}

/*************/
/* Operators */
/*************/
template <typename ChordType>
const bool ChordTypeAbstract<ChordType>::operator==(const ChordType& inChordType) const
{
    return Set<SimpleInterval, ChordType>::operator==(inChordType) && m_Bass == inChordType.m_Bass;
}

template <typename ChordType>
const bool ChordTypeAbstract<ChordType>::operator!=(const ChordType& inChordType) const
{
    return Set<SimpleInterval, ChordType>::operator!=(inChordType) || m_Bass != inChordType.m_Bass;
}

template <typename ChordType>
const bool ChordTypeAbstract<ChordType>::operator<(const ChordType& inChordType) const
{
    if (this->m_set != inChordType.m_set)
    {
        return Set<SimpleInterval, ChordType>::operator<(inChordType);
    }
    else
    {
        return m_Bass < inChordType.m_Bass;
    }
}

/*************/
/* Observers */
/*************/
template <typename ChordType>
const bool ChordTypeAbstract<ChordType>::isTriad() const
{
    return this->cardinality() == 3;
}

template <typename ChordType>
const std::vector<ChordType> ChordTypeAbstract<ChordType>::inversions() const
{
    std::vector<ChordType> theInversions(this->cardinality()+1, *this);
    theInversions[1].deleteBass();
    for (std::set<SimpleInterval>::const_iterator theIntervalIt = this->m_set.begin(); theIntervalIt != this->m_set.end(); ++theIntervalIt)
    {
        theInversions.push_back(ChordType(*this).addBass(*theIntervalIt));
    }
    return theInversions;
}

template <typename ChordType>
const ChordType ChordTypeAbstract<ChordType>::triad(bool inWithBass) const
{
    if (*this == ChordType::none())
    {
        return static_cast<const ChordType&>(*this);
    }
    else
    {
        ChordType theTriadType = ChordType::undefined();
        //if the formula contains major third
        if (this->m_set.count(SimpleInterval::majorThird()) > 0)
        {
            //if formula contains only augmented fifth
            if (this->m_set.count(SimpleInterval::augmentedFifth()) > 0 && this->m_set.count(SimpleInterval::perfectFifth()) == 0 && this->m_set.count(SimpleInterval::diminishedFifth()) == 0)
            {
                //augmented triad
                theTriadType = augmented();
            }
            //if formula contains only diminished fifth
            else if (this->m_set.count(SimpleInterval::diminishedFifth()) > 0 && this->m_set.count(SimpleInterval::perfectFifth()) == 0 && this->m_set.count(SimpleInterval::augmentedFifth()) == 0)
            {
                //majorb5 triad
                theTriadType = majorFlatFifth();
            }
            else
            {
                //major triad
                theTriadType = major();
            }
        }
        //if formula contains minor third
        else if (this->m_set.count(SimpleInterval::minorThird()) > 0)
        {
            //if formula contains only diminished fifth
            if (this->m_set.count(SimpleInterval::diminishedFifth()) > 0 && this->m_set.count(SimpleInterval::perfectFifth()) == 0 && this->m_set.count(SimpleInterval::augmentedFifth()) == 0)
            {
                //diminished triad
                theTriadType = diminished();
            }
            //if formula contains only augmented fifth
            else if (this->m_set.count(SimpleInterval::augmentedFifth()) > 0 && this->m_set.count(SimpleInterval::perfectFifth()) == 0 && this->m_set.count(SimpleInterval::diminishedFifth()) == 0)
            {
                theTriadType = minorSharpFifth();
            }
            else
            {
                //minor triad
                theTriadType = minor();
            }
        }
        //if the formula contains perfect fourth (and no third or major second)
        else if (this->m_set.count(SimpleInterval::perfectFourth()) > 0 && this->m_set.count(SimpleInterval::majorSecond()) == 0)
        {
            //suspended fourth triad
            theTriadType = suspendedFourth();
        }
        //if the formula contains major second (and no third or perfect fourth)
        else if (this->m_set.count(SimpleInterval::majorSecond()) > 0 && this->m_set.count(SimpleInterval::perfectFourth()) == 0)
        {
            //suspended second triad
            theTriadType = suspendedSecond();
        }
        //if the formula only contains root and perfect fifth
        else if (this->m_set.count(SimpleInterval::unison()) > 0 && this->m_set.count(SimpleInterval::perfectFifth()) > 0)
        {
            //power chord
            theTriadType = power();
        }
        else
        {
            //if nothing else matches
            theTriadType = rootOnly();
        }
        // if bass has to be kept and if the original bass is part of the mapped type
        if (inWithBass && theTriadType.m_set.count(this->m_Bass) > 0)
        {
            theTriadType.m_Bass = this->m_Bass;
        }
        return theTriadType;
    }
}

template <typename ChordType>
const ChordType ChordTypeAbstract<ChordType>::tetrad(bool inWithBass) const
{
    if (*this == ChordType::none())
    {
        return static_cast<const ChordType&>(*this);
    }
    else
    {
        ChordType theTetradType = ChordType::undefined();
        //if the formula contains major third
        if (this->m_set.count(SimpleInterval::majorThird()) > 0)
        {
            //if formula contains only augmented fifth
            if (this->m_set.count(SimpleInterval::augmentedFifth()) > 0 && this->m_set.count(SimpleInterval::perfectFifth()) == 0 && this->m_set.count(SimpleInterval::diminishedFifth()) == 0)
            {
                if (this->m_set.count(SimpleInterval::minorSeventh()) > 0)
                {
                    theTetradType = augmentedSeventh();
                }
                else if (this->m_set.count(SimpleInterval::majorSeventh()) > 0)
                {
                    theTetradType = augmentedMajorSeventh();
                }
                else
                {
                    //augmented triad
                    theTetradType = augmented();
                }
            }
            //if formula contains only diminished fifth
            else if (this->m_set.count(SimpleInterval::diminishedFifth()) > 0 && this->m_set.count(SimpleInterval::perfectFifth()) == 0 && this->m_set.count(SimpleInterval::augmentedFifth()) == 0)
            {
                if (this->m_set.count(SimpleInterval::minorSeventh()) > 0)
                {
                    theTetradType = majorFlatFifth().addInterval(SimpleInterval::minorSeventh());
                }
                else if (this->m_set.count(SimpleInterval::majorSeventh()) > 0)
                {
                    theTetradType = majorFlatFifth().addInterval(SimpleInterval::majorSeventh());
                }
                else
                {
                    //majorb5 triad
                    theTetradType = majorFlatFifth();
                }
            }
            //if formula contains minor seventh (no fifth necessary)
            else if (this->m_set.count(SimpleInterval::minorSeventh()) > 0)
            {
                theTetradType = dominantSeventh();
            }
            //if formula contains major seventh (no fifth necessary)
            else if (this->m_set.count(SimpleInterval::majorSeventh()) > 0)
            {
                theTetradType = majorSeventh();
            }
            //if formula contains major sixth (no fifth necessary)
            else if (this->m_set.count(SimpleInterval::majorSixth()) > 0)
            {
                theTetradType = majorSixth();
            }
            //if formula contains perfect fifth
            else //if (this->m_set.count(SimpleInterval::perfectFifth()) > 0)
            {
                //major triad
                theTetradType = major();
            }
        }
        //if formula contains minor third
        else if (this->m_set.count(SimpleInterval::minorThird()) > 0)
        {
            //if formula contains only diminished fifth
            if (this->m_set.count(SimpleInterval::diminishedFifth()) > 0 && this->m_set.count(SimpleInterval::perfectFifth()) == 0)
            {
                if (this->m_set.count(SimpleInterval::minorSeventh()) > 0)
                {
                    theTetradType = halfDiminished();
                }
                else if (this->m_set.count(SimpleInterval::diminishedSeventh()) > 0)
                {
                    theTetradType = diminishedSeventh();
                }
                else
                {
                    //diminished triad
                    theTetradType = diminished();
                }
            }
            //if formula contains only augmented fifth
            else if (this->m_set.count(SimpleInterval::augmentedFifth()) > 0 && this->m_set.count(SimpleInterval::perfectFifth()) == 0)
            {
                if (this->m_set.count(SimpleInterval::minorSeventh()) > 0)
                {
                    theTetradType = minorSharpFifth().addInterval(SimpleInterval::minorSeventh());
                }
                else if (this->m_set.count(SimpleInterval::majorSeventh()) > 0)
                {
                    theTetradType = minorSharpFifth().addInterval(SimpleInterval::majorSeventh());
                }
                else
                {
                    theTetradType = minorSharpFifth();
                }
            }
            //if formula contains minor seventh (no fifth necessary)
            else if (this->m_set.count(SimpleInterval::minorSeventh()) > 0)
            {
                theTetradType = minorSeventh();
            }
            //if formula contains major seventh (no fifth necessary)
            else if (this->m_set.count(SimpleInterval::majorSeventh()) > 0)
            {
                theTetradType = minorMajorSeventh();
            }
            //if formula contains major sixth (no fifth necessary)
            else if (this->m_set.count(SimpleInterval::majorSixth()) > 0)
            {
                theTetradType = minorSixth();
            }
            //if the formula contains perfect fifth
            else //if (this->m_set.count(SimpleInterval::perfectFifth()) > 0)
            {
                //minor triad
                theTetradType = minor();
            }
        }
        //if the formula contains perfect fourth (and no third or major second)
        else if (this->m_set.count(SimpleInterval::perfectFourth()) > 0 && this->m_set.count(SimpleInterval::majorSecond()) == 0)
        {
            if (this->m_set.count(SimpleInterval::minorSeventh()) > 0)
            {
                theTetradType = suspendedFourthSeventh();
            }
            else if (this->m_set.count(SimpleInterval::majorSeventh()) > 0)
            {
                theTetradType = suspendedFourth().addInterval(SimpleInterval::majorSeventh());
            }
            //if formula contains major sixth (no fifth necessary)
            else if (this->m_set.count(SimpleInterval::majorSixth()) > 0)
            {
                theTetradType = suspendedFourth().addInterval(SimpleInterval::majorSixth());
            }
            else
            {
                //suspended fourth triad
                theTetradType = suspendedFourth();
            }
        }
        //if the formula contains major second (and no third or perfect fourth)
        else if (this->m_set.count(SimpleInterval::majorSecond()) > 0 && this->m_set.count(SimpleInterval::perfectFourth()) == 0)
        {
            if (this->m_set.count(SimpleInterval::minorSeventh()) > 0)
            {
                theTetradType = suspendedSecond().addInterval(SimpleInterval::minorSeventh());
            }
            else if (this->m_set.count(SimpleInterval::majorSeventh()) > 0)
            {
                theTetradType = suspendedSecond().addInterval(SimpleInterval::majorSeventh());
            }
            //if formula contains major sixth (no fifth necessary)
            else if (this->m_set.count(SimpleInterval::majorSixth()) > 0)
            {
                theTetradType = suspendedSecond().addInterval(SimpleInterval::majorSixth());
            }
            else
            {
                //suspended second triad
                theTetradType = suspendedSecond();
            }
        }
        //if the formula only contains root and perfect fifth
        else if (this->m_set.count(SimpleInterval::unison()) > 0 && this->m_set.count(SimpleInterval::perfectFifth()) > 0)
        {
            //power chord
            theTetradType = power();
        }
        else
        {
            //if nothing else matches
            theTetradType = rootOnly();
        }
        // if bass has to be kept and if the original bass is part of the mapped type
        if (inWithBass && theTetradType.m_set.count(this->m_Bass) > 0)
        {
            theTetradType.m_Bass = this->m_Bass;
        }
        return theTetradType;
    }
}

/*************/
/* Modifiers */
/*************/
template <typename ChordType>
void ChordTypeAbstract<ChordType>::subtract(const ChordType& inType)
{
    if (!contains(inType))
    {
        throw std::invalid_argument("The subtractable chord type should contain all intervals of the chord type to be subtracted");
    }
    for (std::set<SimpleInterval>::const_iterator it = inType.m_set.begin(); it != inType.m_set.end(); ++it)
    {
        deleteInterval(*it);
    }
}

template <typename ChordType>
void ChordTypeAbstract<ChordType>::subtract(const ChordType& inType, std::set<SimpleInterval>& outRestIntervals, std::set<SimpleInterval>& outMissingIntervals) const
{
    outRestIntervals = std::set<SimpleInterval>();
    std::set_difference(this->m_set.begin(), this->m_set.end(), inType.m_set.begin(), inType.m_set.end(), std::inserter(outRestIntervals, outRestIntervals.end()));
    outMissingIntervals = std::set<SimpleInterval>();
    std::set_difference(inType.m_set.begin(), inType.m_set.end(), this->m_set.begin(), this->m_set.end(), std::inserter(outMissingIntervals, outMissingIntervals.end()));
}

/**********************/
/* Overridden methods */
/**********************/
template <typename ChordType>
ChordType& ChordTypeAbstract<ChordType>::addInterval(const SimpleInterval& inInterval)
{
    Set<SimpleInterval, ChordType>::add(inInterval);
    return static_cast<ChordType&>(*this);
}

template <typename ChordType>
ChordType& ChordTypeAbstract<ChordType>::deleteInterval(const SimpleInterval& inInterval)
{
    Set<SimpleInterval, ChordType>::remove(inInterval);
    if (m_Bass == inInterval)
    {
        m_Bass = SimpleInterval::undefined();
    }
    return static_cast<ChordType&>(*this);
}

template <typename ChordType>
ChordType& ChordTypeAbstract<ChordType>::replaceInterval(const SimpleInterval& inIntervalToReplace, const SimpleInterval& inReplacementInterval)
{
    Set<SimpleInterval, ChordType>::replace(inIntervalToReplace, inReplacementInterval);
    if (m_Bass == inIntervalToReplace)
    {
        m_Bass = inReplacementInterval;
    }
    return static_cast<ChordType&>(*this);
}

template <typename ChordType>
ChordType& ChordTypeAbstract<ChordType>::addBass(const SimpleInterval& inInterval)
{
    if (inInterval == SimpleInterval::silence() || inInterval == SimpleInterval::none())
    {
        throw std::invalid_argument("Only true or undefined intervals can be added as bass");
    }
    else if (inInterval == SimpleInterval::undefined())
    {
        m_Bass = inInterval;
    }
    else
    {
        addInterval(inInterval);
        m_Bass = inInterval;
    }
    return static_cast<ChordType&>(*this);
}

template <typename ChordType>
ChordType& ChordTypeAbstract<ChordType>::deleteBass()
{
    m_Bass = SimpleInterval::undefined();
    return static_cast<ChordType&>(*this);
}

template <typename ChordType>
const ChordType ChordTypeAbstract<ChordType>::withoutBass() const
{
    ChordType theChordType(*this);
    theChordType.m_Bass = SimpleInterval::undefined();
    return theChordType;
}

template <typename ChordType>
const bool ChordTypeAbstract<ChordType>::hasSpelling() const
{
    return Set<SimpleInterval, ChordType>::hasSpelling() && m_Bass.hasSpelling();
}

template <typename ChordType>
ChordType ChordTypeAbstract<ChordType>::withoutSpelling() const
{
    return ChordType(static_cast<const ChordType&>(*this)).ignoreSpelling();
}

template <typename ChordType>
ChordType& ChordTypeAbstract<ChordType>::ignoreSpelling()
{
    Set<SimpleInterval, ChordType>::ignoreSpelling();
    m_Bass.ignoreSpelling();
    return static_cast<ChordType&>(*this);
}

template <typename ChordType>
const ComplexInterval ChordTypeAbstract<ChordType>::autoVoicing(const SimpleInterval& inSimpleInterval) const
{
    const bool roomAvailable = this->m_set.count(inSimpleInterval+1) == 0 && this->m_set.count(inSimpleInterval-1) == 0;
    if (hasSpelling() && inSimpleInterval.hasSpelling())
    {
        ptrdiff_t naturalDegree;
        std::tie(std::ignore, naturalDegree) = inSimpleInterval.majorDegree();
        if (!roomAvailable && (naturalDegree == 2 || naturalDegree == 4 || naturalDegree == 6))
        {
            return ComplexInterval(inSimpleInterval, 1);
        }
        else
        {
            return ComplexInterval(inSimpleInterval, 0);
        }
    }
    else
    {
        if (roomAvailable || inSimpleInterval == SimpleInterval::perfectFifth() || inSimpleInterval == SimpleInterval::minorSeventh() || inSimpleInterval == SimpleInterval::majorSeventh())
        {
            return ComplexInterval(inSimpleInterval, 0);
        }
        else if (inSimpleInterval == SimpleInterval::minorSecond())
        {
            return ComplexInterval(SimpleInterval::minorSecond(), 1);
        }
        else if (inSimpleInterval == SimpleInterval::majorSecond())
        {
            return ComplexInterval(SimpleInterval::majorSecond(), 1);
        }
        else if (inSimpleInterval == SimpleInterval::augmentedSecond())
        {
            return ComplexInterval(SimpleInterval::augmentedSecond(), 1);
        }
        else if (inSimpleInterval == SimpleInterval::diminishedFourth())
        {
            return ComplexInterval(SimpleInterval::diminishedFourth(), 1);
        }
        else if (inSimpleInterval == SimpleInterval::perfectFourth())
        {
            return ComplexInterval(SimpleInterval::perfectFourth(), 1);
        }
        else if (inSimpleInterval == SimpleInterval::augmentedFourth())
        {
            return ComplexInterval(SimpleInterval::augmentedFourth(), 1);
        }
        else if (inSimpleInterval == SimpleInterval::minorSixth())
        {
            return ComplexInterval(SimpleInterval::minorSixth(), 1);
        }
        else if (inSimpleInterval == SimpleInterval::majorSixth())
        {
            return ComplexInterval(SimpleInterval::majorSixth(), 1);
        }
        else //unison
        {
            return ComplexInterval(inSimpleInterval, 0);
        }
    }
}

}
#endif	// #ifndef ChordType_h
