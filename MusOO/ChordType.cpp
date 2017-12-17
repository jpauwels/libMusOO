//============================================================================
/**
	Implementation file for ChordType.h
	
	@author		Johan Pauwels
	@date		20100913
*/
//============================================================================

// Includes
#include "MusOO/ChordType.h"
#include <vector>
#include <sstream>
#include <stdexcept>
#include <algorithm>
#include <iterator>

using std::set;
using std::invalid_argument;
using std::vector;
using std::ostringstream;
using namespace MusOO;

/****************************/
/* Static factory functions */
/****************************/
ChordType ChordType::none()
{
	static ChordType none;
	return none;
}
ChordType ChordType::undefined()
{
	const SimpleInterval undefinedList[] = {SimpleInterval::undefined()};
	static ChordType undefined(undefinedList, 1);
	return undefined;
}
ChordType ChordType::rootOnly()
{
	const SimpleInterval rootOnlyList[] = {SimpleInterval::unison()};
	static ChordType rootOnly(rootOnlyList, 1);
	return rootOnly;
}
ChordType ChordType::major()
{
	const SimpleInterval majorList[] = {SimpleInterval::unison(), SimpleInterval::majorThird(), SimpleInterval::perfectFifth()};
	static ChordType major(majorList, 3);
	return major;
}
ChordType ChordType::minor()
{
	const SimpleInterval minorList[] = {SimpleInterval::unison(), SimpleInterval::minorThird(), SimpleInterval::perfectFifth()};
	static ChordType minor(minorList, 3);
	return minor;
}
ChordType ChordType::augmented()
{
	const SimpleInterval augmentedList[] = {SimpleInterval::unison(), SimpleInterval::majorThird(), SimpleInterval::augmentedFifth()};
	static ChordType augmented(augmentedList, 3);
	return augmented;
}
ChordType ChordType::diminished()
{
	const SimpleInterval diminishedList[] = {SimpleInterval::unison(), SimpleInterval::minorThird(), SimpleInterval::diminishedFifth()};
	static ChordType diminished(diminishedList, 3);
	return diminished;
}
ChordType ChordType::suspendedSecond()
{
	const SimpleInterval suspendedSecondList[] = {SimpleInterval::unison(), SimpleInterval::majorSecond(), SimpleInterval::perfectFifth()};
	static ChordType suspendedSecond(suspendedSecondList, 3);
	return suspendedSecond;
}
ChordType ChordType::suspendedFourth()
{
	const SimpleInterval suspendedFourthList[] = {SimpleInterval::unison(), SimpleInterval::perfectFourth(), SimpleInterval::perfectFifth()};
	static ChordType suspendedFourth(suspendedFourthList, 3);
	return suspendedFourth;
}
ChordType ChordType::majorFlatFifth()
{
	const SimpleInterval majorFlatFifthList[] = {SimpleInterval::unison(), SimpleInterval::majorThird(), SimpleInterval::diminishedFifth()};
	static ChordType majorFlatFifth(majorFlatFifthList, 3);
	return majorFlatFifth;
}
ChordType ChordType::minorSharpFifth()
{
	const SimpleInterval minorSharpFifthList[] = {SimpleInterval::unison(), SimpleInterval::minorThird(), SimpleInterval::augmentedFifth()};
	static ChordType minorSharpFifth(minorSharpFifthList, 3);
	return minorSharpFifth;
}
ChordType ChordType::dominantSeventh()
{
	const SimpleInterval dominantSeventhList[] = {SimpleInterval::unison(), SimpleInterval::majorThird(), SimpleInterval::perfectFifth(), SimpleInterval::minorSeventh()};
	static ChordType dominantSeventh(dominantSeventhList, 4);
	return dominantSeventh;
}
ChordType ChordType::majorSeventh()
{
	const SimpleInterval majorSeventhList[] = {SimpleInterval::unison(), SimpleInterval::majorThird(), SimpleInterval::perfectFifth(), SimpleInterval::majorSeventh()};
	static ChordType majorSeventh(majorSeventhList, 4);
	return majorSeventh;
}
ChordType ChordType::minorSeventh()
{
	const SimpleInterval minorSeventhList[] = {SimpleInterval::unison(), SimpleInterval::minorThird(), SimpleInterval::perfectFifth(), SimpleInterval::minorSeventh()};
	static ChordType minorSeventh(minorSeventhList, 4);
	return minorSeventh;
}
ChordType ChordType::diminishedSeventh()
{
	const SimpleInterval diminishedSeventhList[] = {SimpleInterval::unison(), SimpleInterval::minorThird(), SimpleInterval::diminishedFifth(), SimpleInterval::diminishedSeventh()};
	static ChordType diminishedSeventh(diminishedSeventhList, 4);
	return diminishedSeventh;
}
ChordType ChordType::augmentedSeventh()
{
	const SimpleInterval augmentedSeventhList[] = {SimpleInterval::unison(), SimpleInterval::majorThird(), SimpleInterval::augmentedFifth(), SimpleInterval::minorSeventh()};
	static ChordType augmentedSeventh(augmentedSeventhList, 4);
	return augmentedSeventh;
}
ChordType ChordType::augmentedMajorSeventh()
{
	const SimpleInterval augmentedMajorSeventhList[] = {SimpleInterval::unison(), SimpleInterval::majorThird(), SimpleInterval::augmentedFifth(), SimpleInterval::majorSeventh()};
	static ChordType augmentedMajorSeventh(augmentedMajorSeventhList, 4);
	return augmentedMajorSeventh;
}
ChordType ChordType::halfDiminished()
{
	const SimpleInterval halfDiminishedList[] = {SimpleInterval::unison(), SimpleInterval::minorThird(), SimpleInterval::diminishedFifth(), SimpleInterval::minorSeventh()};
	static ChordType halfDiminished(halfDiminishedList, 4);
	return halfDiminished;
}
ChordType ChordType::minorMajorSeventh()
{
	const SimpleInterval minorMajorList[] = {SimpleInterval::unison(), SimpleInterval::minorThird(), SimpleInterval::perfectFifth(), SimpleInterval::majorSeventh()};
	static ChordType minorMajor(minorMajorList, 4);
	return minorMajor;
}
ChordType ChordType::majorSixth()
{
	const SimpleInterval majorSixthList[] = {SimpleInterval::unison(), SimpleInterval::majorThird(), SimpleInterval::perfectFifth(), SimpleInterval::majorSixth()};
	static ChordType majorSixth(majorSixthList, 4);
	return majorSixth;
}
ChordType ChordType::minorSixth()
{
	const SimpleInterval minorSixthList[] = {SimpleInterval::unison(), SimpleInterval::minorThird(), SimpleInterval::perfectFifth(), SimpleInterval::majorSixth()};
	static ChordType minorSixth(minorSixthList, 4);
	return minorSixth;
}
ChordType ChordType::dominantNinth()
{
	const SimpleInterval dominantNinthList[] = {SimpleInterval::unison(), SimpleInterval::majorThird(), SimpleInterval::perfectFifth(), SimpleInterval::minorSeventh(), SimpleInterval::majorSecond()};
	static ChordType dominantNinth(dominantNinthList, 5);
	return dominantNinth;
}
ChordType ChordType::majorNinth()
{
	const SimpleInterval majorNinthList[] = {SimpleInterval::unison(), SimpleInterval::majorThird(), SimpleInterval::perfectFifth(), SimpleInterval::majorSeventh(), SimpleInterval::majorSecond()};
	static ChordType majorNinth(majorNinthList, 5);
	return majorNinth;
}
ChordType ChordType::minorNinth()
{
	const SimpleInterval minorNinthList[] = {SimpleInterval::unison(), SimpleInterval::minorThird(), SimpleInterval::perfectFifth(), SimpleInterval::minorSeventh(), SimpleInterval::majorSecond()};
	static ChordType minorNinth(minorNinthList, 5);
	return minorNinth;
}
ChordType ChordType::dominantEleventh()
{
	const SimpleInterval dominantEleventhList[] = {SimpleInterval::unison(), SimpleInterval::majorThird(), SimpleInterval::perfectFifth(), SimpleInterval::minorSeventh(), SimpleInterval::majorSecond(), SimpleInterval::perfectFourth()};
	static ChordType dominantEleventh(dominantEleventhList, 6);
	return dominantEleventh;
}
ChordType ChordType::majorEleventh()
{
	const SimpleInterval majorEleventhList[] = {SimpleInterval::unison(), SimpleInterval::majorThird(), SimpleInterval::perfectFifth(), SimpleInterval::majorSeventh(), SimpleInterval::majorSecond(), SimpleInterval::perfectFourth()};
	static ChordType majorEleventh(majorEleventhList, 6);
	return majorEleventh;
}
ChordType ChordType::minorEleventh()
{
	const SimpleInterval minorEleventhList[] = {SimpleInterval::unison(), SimpleInterval::minorThird(), SimpleInterval::perfectFifth(), SimpleInterval::minorSeventh(), SimpleInterval::majorSecond(), SimpleInterval::perfectFourth()};
	static ChordType minorEleventh(minorEleventhList, 6);
	return minorEleventh;
}
ChordType ChordType::dominantThirteenth()
{
	const SimpleInterval dominantThirteenthList[] = {SimpleInterval::unison(), SimpleInterval::majorThird(), SimpleInterval::perfectFifth(), SimpleInterval::minorSeventh(), SimpleInterval::majorSecond(), SimpleInterval::perfectFourth(), SimpleInterval::majorSixth()};
	static ChordType dominantThirteenth(dominantThirteenthList, 7);
	return dominantThirteenth;
}
ChordType ChordType::majorThirteenth()
{
	const SimpleInterval majorThirteenthList[] = {SimpleInterval::unison(), SimpleInterval::majorThird(), SimpleInterval::perfectFifth(), SimpleInterval::majorSeventh(), SimpleInterval::majorSecond(), SimpleInterval::perfectFourth(), SimpleInterval::majorSixth()};
	static ChordType majorThirteenth(majorThirteenthList, 7);
	return majorThirteenth;
}
ChordType ChordType::minorThirteenth()
{
	const SimpleInterval minorThirteenthList[] = {SimpleInterval::unison(), SimpleInterval::minorThird(), SimpleInterval::perfectFifth(), SimpleInterval::minorSeventh(), SimpleInterval::majorSecond(), SimpleInterval::perfectFourth(), SimpleInterval::majorSixth()};
	static ChordType minorThirteenth(minorThirteenthList, 7);
	return minorThirteenth;
}
ChordType ChordType::suspendedFourthSeventh()
{
	const SimpleInterval suspendedFourthSeventhList[] = {SimpleInterval::unison(), SimpleInterval::perfectFourth(), SimpleInterval::perfectFifth(), SimpleInterval::minorSeventh()};
	static ChordType suspendedFourthSeventh(suspendedFourthSeventhList, 4);
	return suspendedFourthSeventh;
}
ChordType ChordType::suspendedFourthNinth()
{
	const SimpleInterval suspendedFourthNinthList[] = {SimpleInterval::unison(), SimpleInterval::perfectFourth(), SimpleInterval::perfectFifth(), SimpleInterval::minorSeventh(), SimpleInterval::majorSecond()};
	static ChordType suspendedFourthNinth(suspendedFourthNinthList, 5);
	return suspendedFourthNinth;
}
ChordType ChordType::italianSixth()
{
	const SimpleInterval italianSixthList[] = {SimpleInterval::unison(), SimpleInterval::augmentedFourth(), SimpleInterval::minorSixth()};
	static ChordType italianSixth(italianSixthList, 3, SimpleInterval::minorSixth());
	return italianSixth;
}
ChordType ChordType::frenchSixth()
{
	const SimpleInterval frenchSixthList[] = {SimpleInterval::unison(), SimpleInterval::majorSecond(), SimpleInterval::augmentedFourth(), SimpleInterval::minorSixth()};
	static ChordType frenchSixth(frenchSixthList, 4, SimpleInterval::minorSixth());
	return frenchSixth;
}
ChordType ChordType::germanSixth()
{
	const SimpleInterval germanSixthList[] = {SimpleInterval::unison(), SimpleInterval::minorThird(), SimpleInterval::augmentedFourth(), SimpleInterval::minorSixth()};
	static ChordType germanSixth(germanSixthList, 4, SimpleInterval::minorSixth());
	return germanSixth;
}
ChordType ChordType::power()
{
	const SimpleInterval powerList[] = {SimpleInterval::unison(), SimpleInterval::perfectFifth()};
	static ChordType power(powerList, 2);
	return power;
}
ChordType ChordType::tristan()
{
	const SimpleInterval tristanList[] = {SimpleInterval::unison(),SimpleInterval::augmentedFourth(), SimpleInterval::augmentedSixth(), SimpleInterval::augmentedSecond()};
	static ChordType tristan(tristanList, 4);
	return tristan;
}

/*******************************/
/* Constructors and destructor */
/*******************************/
ChordType::ChordType()
: Set(), m_Bass(SimpleInterval::undefined())
{
}

ChordType::~ChordType()
{
	// Nothing to do...
}

ChordType::ChordType(const SimpleInterval* inIntervalList, const int inNumOfIntervals, const SimpleInterval& inBass /*= SimpleInterval::undefined()*/)
: Set(inIntervalList, inNumOfIntervals), m_Bass(inBass)
{
}

/*************/
/* Operators */
/*************/
bool ChordType::operator==(const ChordType& inChordType) const
{
	return Set::operator==(inChordType) && m_Bass == inChordType.m_Bass;
}

bool ChordType::operator!=(const ChordType& inChordType) const
{
	return Set::operator!=(inChordType) || m_Bass != inChordType.m_Bass;
}

bool ChordType::operator<(const ChordType& inChordType) const
{
    if (m_set != inChordType.m_set)
    {
        return Set::operator<(inChordType);
    }
    else
    {
        return m_Bass < inChordType.m_Bass;
    }
}

/*************/
/* Observers */
/*************/
const bool ChordType::isTriad() const
{
	return cardinality() == 3;
}

const std::vector<ChordType> ChordType::inversions() const
{
    vector<ChordType> theInversions(cardinality()+1, *this);
    theInversions[1].deleteBass();
    for (set<SimpleInterval>::const_iterator theIntervalIt = m_set.begin(); theIntervalIt != m_set.end(); ++theIntervalIt)
    {
        theInversions.push_back(ChordType(*this).addBass(*theIntervalIt));
    }
    return theInversions;
}

//const std::string ChordType::str() const
//{
//	ostringstream theChordTypeStream;
//	theChordTypeStream << "[";
//	if (!m_set.empty())
//	{
//		theChordTypeStream << m_set.begin()->circleStepsCW();
//	}
//	for (set<Interval>::const_iterator it = ++m_set.begin(); it != m_set.end(); ++it)
//	{
//		theChordTypeStream << "," << it->circleStepsCW();
//	}
//	theChordTypeStream << "]";
//	if (m_Bass != SimpleInterval::unison() && m_Bass != SimpleInterval::unknown())
//	{
//		theChordTypeStream << "/" << m_Bass.majorMode();
//	}
//	return theChordTypeStream.str();
//}


const ChordType ChordType::triad(bool inWithBass) const
{
	if (*this == ChordType::none())
	{
		return *this;
	}
	else
    {
        ChordType theTriadType = ChordType::undefined();
        //if the formula contains major third
        if (m_set.count(SimpleInterval::majorThird()) > 0)
        {
            //if formula contains only augmented fifth
            if (m_set.count(SimpleInterval::augmentedFifth()) > 0 && m_set.count(SimpleInterval::perfectFifth()) == 0 && m_set.count(SimpleInterval::diminishedFifth()) == 0)
            {
                //augmented triad
                theTriadType = augmented();
            }
            //if formula contains only diminished fifth
            else if (m_set.count(SimpleInterval::diminishedFifth()) > 0 && m_set.count(SimpleInterval::perfectFifth()) == 0 && m_set.count(SimpleInterval::augmentedFifth()) == 0)
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
        else if (m_set.count(SimpleInterval::minorThird()) > 0)
        {
            //if formula contains only diminished fifth
            if (m_set.count(SimpleInterval::diminishedFifth()) > 0 && m_set.count(SimpleInterval::perfectFifth()) == 0 && m_set.count(SimpleInterval::augmentedFifth()) == 0)
            {
                //diminished triad
                theTriadType = diminished();
            }
            //if formula contains only augmented fifth
            else if (m_set.count(SimpleInterval::augmentedFifth()) > 0 && m_set.count(SimpleInterval::perfectFifth()) == 0 && m_set.count(SimpleInterval::diminishedFifth()) == 0)
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
        else if (m_set.count(SimpleInterval::perfectFourth()) > 0 && m_set.count(SimpleInterval::majorSecond()) == 0)
        {
            //suspended fourth triad
            theTriadType = suspendedFourth();
        }
        //if the formula contains major second (and no third or perfect fourth)
        else if (m_set.count(SimpleInterval::majorSecond()) > 0 && m_set.count(SimpleInterval::perfectFourth()) == 0)
        {
            //suspended second triad
            theTriadType = suspendedSecond();
        }
        //if the formula only contains root and perfect fifth
        else if (m_set.count(SimpleInterval::unison()) > 0 && m_set.count(SimpleInterval::perfectFifth()) > 0)
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

const ChordType ChordType::tetrad(bool inWithBass) const
{
	if (*this == ChordType::none())
	{
		return *this;
	}
	else
    {
        ChordType theTetradType = ChordType::undefined();
        //if the formula contains major third
        if (m_set.count(SimpleInterval::majorThird()) > 0)
        {
            //if formula contains only augmented fifth
            if (m_set.count(SimpleInterval::augmentedFifth()) > 0 && m_set.count(SimpleInterval::perfectFifth()) == 0 && m_set.count(SimpleInterval::diminishedFifth()) == 0)
            {
                if (m_set.count(SimpleInterval::minorSeventh()) > 0)
                {
                    theTetradType = augmentedSeventh();
                }
                else if (m_set.count(SimpleInterval::majorSeventh()) > 0)
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
            else if (m_set.count(SimpleInterval::diminishedFifth()) > 0 && m_set.count(SimpleInterval::perfectFifth()) == 0 && m_set.count(SimpleInterval::augmentedFifth()) == 0)
            {
                if (m_set.count(SimpleInterval::minorSeventh()) > 0)
                {
                    theTetradType = majorFlatFifth().addInterval(SimpleInterval::minorSeventh());
                }
                else if (m_set.count(SimpleInterval::majorSeventh()) > 0)
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
            else if (m_set.count(SimpleInterval::minorSeventh()) > 0)
            {
                theTetradType = dominantSeventh();
            }
            //if formula contains major seventh (no fifth necessary)
            else if (m_set.count(SimpleInterval::majorSeventh()) > 0)
            {
                theTetradType = majorSeventh();
            }
            //if formula contains major sixth (no fifth necessary)
            else if (m_set.count(SimpleInterval::majorSixth()) > 0)
            {
                theTetradType = majorSixth();
            }
            //if formula contains perfect fifth
            else //if (m_set.count(SimpleInterval::perfectFifth()) > 0)
            {
                //major triad
                theTetradType = major();
            }
        }
        //if formula contains minor third
        else if (m_set.count(SimpleInterval::minorThird()) > 0)
        {
            //if formula contains only diminished fifth
            if (m_set.count(SimpleInterval::diminishedFifth()) > 0 && m_set.count(SimpleInterval::perfectFifth()) == 0)
            {
                if (m_set.count(SimpleInterval::minorSeventh()) > 0)
                {
                    theTetradType = halfDiminished();
                }
                else if (m_set.count(SimpleInterval::diminishedSeventh()) > 0)
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
            else if (m_set.count(SimpleInterval::augmentedFifth()) > 0 && m_set.count(SimpleInterval::perfectFifth()) == 0)
            {
                if (m_set.count(SimpleInterval::minorSeventh()) > 0)
                {
                    theTetradType = minorSharpFifth().addInterval(SimpleInterval::minorSeventh());
                }
                else if (m_set.count(SimpleInterval::majorSeventh()) > 0)
                {
                    theTetradType = minorSharpFifth().addInterval(SimpleInterval::majorSeventh());
                }
                else
                {
                    theTetradType = minorSharpFifth();
                }
            }
            //if formula contains minor seventh (no fifth necessary)
            else if (m_set.count(SimpleInterval::minorSeventh()) > 0)
            {
                theTetradType = minorSeventh();
            }
            //if formula contains major seventh (no fifth necessary)
            else if (m_set.count(SimpleInterval::majorSeventh()) > 0)
            {
                theTetradType = minorMajorSeventh();
            }
            //if formula contains major sixth (no fifth necessary)
            else if (m_set.count(SimpleInterval::majorSixth()) > 0)
            {
                theTetradType = minorSixth();
            }
            //if the formula contains perfect fifth
            else //if (m_set.count(SimpleInterval::perfectFifth()) > 0)
            {
                //minor triad
                theTetradType = minor();
            }
        }
        //if the formula contains perfect fourth (and no third or major second)
        else if (m_set.count(SimpleInterval::perfectFourth()) > 0 && m_set.count(SimpleInterval::majorSecond()) == 0)
        {
            if (m_set.count(SimpleInterval::minorSeventh()) > 0)
            {
                theTetradType = suspendedFourthSeventh();
            }
            else if (m_set.count(SimpleInterval::majorSeventh()) > 0)
            {
                theTetradType = suspendedFourth().addInterval(SimpleInterval::majorSeventh());
            }
            //if formula contains major sixth (no fifth necessary)
            else if (m_set.count(SimpleInterval::majorSixth()) > 0)
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
        else if (m_set.count(SimpleInterval::majorSecond()) > 0 && m_set.count(SimpleInterval::perfectFourth()) == 0)
        {
            if (m_set.count(SimpleInterval::minorSeventh()) > 0)
            {
                theTetradType = suspendedSecond().addInterval(SimpleInterval::minorSeventh());
            }
            else if (m_set.count(SimpleInterval::majorSeventh()) > 0)
            {
                theTetradType = suspendedSecond().addInterval(SimpleInterval::majorSeventh());
            }
            //if formula contains major sixth (no fifth necessary)
            else if (m_set.count(SimpleInterval::majorSixth()) > 0)
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
        else if (m_set.count(SimpleInterval::unison()) > 0 && m_set.count(SimpleInterval::perfectFifth()) > 0)
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
void ChordType::subtract(const ChordType& inType)
{
	if (!contains(inType))
	{
		throw invalid_argument("The subtractable chord type should contain all intervals of the chord type to be subtracted");
	}
	for (set<SimpleInterval>::const_iterator it = inType.m_set.begin(); it != inType.m_set.end(); ++it)
	{
		deleteInterval(*it);
	}
}

void ChordType::subtract(const ChordType& inType, std::set<SimpleInterval>& outRestIntervals, std::set<SimpleInterval>& outMissingIntervals) const
{
    outRestIntervals = set<SimpleInterval>();
    std::set_difference(m_set.begin(), m_set.end(), inType.m_set.begin(), inType.m_set.end(), std::inserter(outRestIntervals, outRestIntervals.end()));
    outMissingIntervals = set<SimpleInterval>();
    std::set_difference(inType.m_set.begin(), inType.m_set.end(), m_set.begin(), m_set.end(), std::inserter(outMissingIntervals, outMissingIntervals.end()));
}

/**********************/
/* Overridden methods */
/**********************/
ChordType& ChordType::addInterval(const SimpleInterval& inInterval)
{
    Set::add(inInterval);
    return *this;
}

ChordType& ChordType::deleteInterval(const SimpleInterval& inInterval)
{
    Set::remove(inInterval);
	if (m_Bass == inInterval)
	{
		m_Bass = SimpleInterval::undefined();
	}
	return *this;
}

ChordType& ChordType::replaceInterval(const SimpleInterval& inIntervalToReplace, const SimpleInterval& inReplacementInterval)
{
    Set::replace(inIntervalToReplace, inReplacementInterval);
	if (m_Bass == inIntervalToReplace)
	{
		m_Bass = inReplacementInterval;
	}
	return *this;
}

ChordType& ChordType::addBass(const SimpleInterval& inInterval)
{
	addInterval(inInterval);
	m_Bass = inInterval;
	return *this;
}

ChordType& ChordType::deleteBass()
{
	m_Bass = SimpleInterval::undefined();
	return *this;
}

const ChordType ChordType::withoutBass() const
{
	ChordType theChordType(*this);
	theChordType.m_Bass = SimpleInterval::undefined();
	return theChordType;
}

const bool ChordType::hasSpelling() const
{
    return Set::hasSpelling() && m_Bass.hasSpelling();
}

ChordType ChordType::withoutSpelling() const
{
    return ChordType(*this).ignoreSpelling();
}

ChordType& ChordType::ignoreSpelling()
{
    Set::ignoreSpelling();
    m_Bass.ignoreSpelling();
	return *this;
}
