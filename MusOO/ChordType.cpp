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
	const Interval undefinedList[] = {Interval::undefined()};
	static ChordType undefined(undefinedList, 1);
	return undefined;
}
ChordType ChordType::rootOnly()
{
	const Interval rootOnlyList[] = {Interval::unison()};
	static ChordType rootOnly(rootOnlyList, 1);
	return rootOnly;
}
ChordType ChordType::major()
{
	const Interval majorList[] = {Interval::unison(), Interval::majorThird(), Interval::perfectFifth()};
	static ChordType major(majorList, 3);
	return major;
}
ChordType ChordType::minor()
{
	const Interval minorList[] = {Interval::unison(), Interval::minorThird(), Interval::perfectFifth()};
	static ChordType minor(minorList, 3);
	return minor;
}
ChordType ChordType::augmented()
{
	const Interval augmentedList[] = {Interval::unison(), Interval::majorThird(), Interval::augmentedFifth()};
	static ChordType augmented(augmentedList, 3);
	return augmented;
}
ChordType ChordType::diminished()
{
	const Interval diminishedList[] = {Interval::unison(), Interval::minorThird(), Interval::diminishedFifth()};
	static ChordType diminished(diminishedList, 3);
	return diminished;
}
ChordType ChordType::suspendedSecond()
{
	const Interval suspendedSecondList[] = {Interval::unison(), Interval::majorSecond(), Interval::perfectFifth()};
	static ChordType suspendedSecond(suspendedSecondList, 3);
	return suspendedSecond;
}
ChordType ChordType::suspendedFourth()
{
	const Interval suspendedFourthList[] = {Interval::unison(), Interval::perfectFourth(), Interval::perfectFifth()};
	static ChordType suspendedFourth(suspendedFourthList, 3);
	return suspendedFourth;
}
ChordType ChordType::majorFlatFifth()
{
	const Interval majorFlatFifthList[] = {Interval::unison(), Interval::majorThird(), Interval::diminishedFifth()};
	static ChordType majorFlatFifth(majorFlatFifthList, 3);
	return majorFlatFifth;
}
ChordType ChordType::minorSharpFifth()
{
	const Interval minorSharpFifthList[] = {Interval::unison(), Interval::minorThird(), Interval::augmentedFifth()};
	static ChordType minorSharpFifth(minorSharpFifthList, 3);
	return minorSharpFifth;
}
ChordType ChordType::dominantSeventh()
{
	const Interval dominantSeventhList[] = {Interval::unison(), Interval::majorThird(), Interval::perfectFifth(), Interval::minorSeventh()};
	static ChordType dominantSeventh(dominantSeventhList, 4);
	return dominantSeventh;
}
ChordType ChordType::majorSeventh()
{
	const Interval majorSeventhList[] = {Interval::unison(), Interval::majorThird(), Interval::perfectFifth(), Interval::majorSeventh()};
	static ChordType majorSeventh(majorSeventhList, 4);
	return majorSeventh;
}
ChordType ChordType::minorSeventh()
{
	const Interval minorSeventhList[] = {Interval::unison(), Interval::minorThird(), Interval::perfectFifth(), Interval::minorSeventh()};
	static ChordType minorSeventh(minorSeventhList, 4);
	return minorSeventh;
}
ChordType ChordType::diminishedSeventh()
{
	const Interval diminishedSeventhList[] = {Interval::unison(), Interval::minorThird(), Interval::diminishedFifth(), Interval::diminishedSeventh()};
	static ChordType diminishedSeventh(diminishedSeventhList, 4);
	return diminishedSeventh;
}
ChordType ChordType::augmentedSeventh()
{
	const Interval augmentedSeventhList[] = {Interval::unison(), Interval::majorThird(), Interval::augmentedFifth(), Interval::minorSeventh()};
	static ChordType augmentedSeventh(augmentedSeventhList, 4);
	return augmentedSeventh;
}
ChordType ChordType::augmentedMajorSeventh()
{
	const Interval augmentedMajorSeventhList[] = {Interval::unison(), Interval::majorThird(), Interval::augmentedFifth(), Interval::majorSeventh()};
	static ChordType augmentedMajorSeventh(augmentedMajorSeventhList, 4);
	return augmentedMajorSeventh;
}
ChordType ChordType::halfDiminished()
{
	const Interval halfDiminishedList[] = {Interval::unison(), Interval::minorThird(), Interval::diminishedFifth(), Interval::minorSeventh()};
	static ChordType halfDiminished(halfDiminishedList, 4);
	return halfDiminished;
}
ChordType ChordType::minorMajorSeventh()
{
	const Interval minorMajorList[] = {Interval::unison(), Interval::minorThird(), Interval::perfectFifth(), Interval::majorSeventh()};
	static ChordType minorMajor(minorMajorList, 4);
	return minorMajor;
}
ChordType ChordType::majorSixth()
{
	const Interval majorSixthList[] = {Interval::unison(), Interval::majorThird(), Interval::perfectFifth(), Interval::majorSixth()};
	static ChordType majorSixth(majorSixthList, 4);
	return majorSixth;
}
ChordType ChordType::minorSixth()
{
	const Interval minorSixthList[] = {Interval::unison(), Interval::minorThird(), Interval::perfectFifth(), Interval::majorSixth()};
	static ChordType minorSixth(minorSixthList, 4);
	return minorSixth;
}
ChordType ChordType::dominantNinth()
{
	const Interval dominantNinthList[] = {Interval::unison(), Interval::majorThird(), Interval::perfectFifth(), Interval::minorSeventh(), Interval::majorNinth()};
	static ChordType dominantNinth(dominantNinthList, 5);
	return dominantNinth;
}
ChordType ChordType::majorNinth()
{
	const Interval majorNinthList[] = {Interval::unison(), Interval::majorThird(), Interval::perfectFifth(), Interval::majorSeventh(), Interval::majorNinth()};
	static ChordType majorNinth(majorNinthList, 5);
	return majorNinth;
}
ChordType ChordType::minorNinth()
{
	const Interval minorNinthList[] = {Interval::unison(), Interval::minorThird(), Interval::perfectFifth(), Interval::minorSeventh(), Interval::majorNinth()};
	static ChordType minorNinth(minorNinthList, 5);
	return minorNinth;
}
ChordType ChordType::dominantEleventh()
{
	const Interval dominantEleventhList[] = {Interval::unison(), Interval::majorThird(), Interval::perfectFifth(), Interval::minorSeventh(), Interval::majorNinth(), Interval::perfectEleventh()};
	static ChordType dominantEleventh(dominantEleventhList, 6);
	return dominantEleventh;
}
ChordType ChordType::majorEleventh()
{
	const Interval majorEleventhList[] = {Interval::unison(), Interval::majorThird(), Interval::perfectFifth(), Interval::majorSeventh(), Interval::majorNinth(), Interval::perfectEleventh()};
	static ChordType majorEleventh(majorEleventhList, 6);
	return majorEleventh;
}
ChordType ChordType::minorEleventh()
{
	const Interval minorEleventhList[] = {Interval::unison(), Interval::minorThird(), Interval::perfectFifth(), Interval::minorSeventh(), Interval::majorNinth(), Interval::perfectEleventh()};
	static ChordType minorEleventh(minorEleventhList, 6);
	return minorEleventh;
}
ChordType ChordType::dominantThirteenth()
{
	const Interval dominantThirteenthList[] = {Interval::unison(), Interval::majorThird(), Interval::perfectFifth(), Interval::minorSeventh(), Interval::majorNinth(), Interval::perfectEleventh(), Interval::majorThirteenth()};
	static ChordType dominantThirteenth(dominantThirteenthList, 7);
	return dominantThirteenth;
}
ChordType ChordType::majorThirteenth()
{
	const Interval majorThirteenthList[] = {Interval::unison(), Interval::majorThird(), Interval::perfectFifth(), Interval::majorSeventh(), Interval::majorNinth(), Interval::perfectEleventh(), Interval::majorThirteenth()};
	static ChordType majorThirteenth(majorThirteenthList, 7);
	return majorThirteenth;
}
ChordType ChordType::minorThirteenth()
{
	const Interval minorThirteenthList[] = {Interval::unison(), Interval::minorThird(), Interval::perfectFifth(), Interval::minorSeventh(), Interval::majorNinth(), Interval::perfectEleventh(), Interval::majorThirteenth()};
	static ChordType minorThirteenth(minorThirteenthList, 7);
	return minorThirteenth;
}
ChordType ChordType::suspendedFourthSeventh()
{
	const Interval suspendedFourthSeventhList[] = {Interval::unison(), Interval::perfectFourth(), Interval::perfectFifth(), Interval::minorSeventh()};
	static ChordType suspendedFourthSeventh(suspendedFourthSeventhList, 4);
	return suspendedFourthSeventh;
}
ChordType ChordType::suspendedFourthNinth()
{
	const Interval suspendedFourthNinthList[] = {Interval::unison(), Interval::perfectFourth(), Interval::perfectFifth(), Interval::minorSeventh(), Interval::majorNinth()};
	static ChordType suspendedFourthNinth(suspendedFourthNinthList, 5);
	return suspendedFourthNinth;
}
ChordType ChordType::italianSixth()
{
	const Interval italianSixthList[] = {Interval::unison(), Interval::augmentedFourth(), Interval::minorSixth()};
	static ChordType italianSixth(italianSixthList, 3, Interval::minorSixth());
	return italianSixth;
}
ChordType ChordType::frenchSixth()
{
	const Interval frenchSixthList[] = {Interval::unison(), Interval::majorSecond(), Interval::augmentedFourth(), Interval::minorSixth()};
	static ChordType frenchSixth(frenchSixthList, 4, Interval::minorSixth());
	return frenchSixth;
}
ChordType ChordType::germanSixth()
{
	const Interval germanSixthList[] = {Interval::unison(), Interval::minorThird(), Interval::augmentedFourth(), Interval::minorSixth()};
	static ChordType germanSixth(germanSixthList, 4, Interval::minorSixth());
	return germanSixth;
}
ChordType ChordType::power()
{
	const Interval powerList[] = {Interval::unison(), Interval::perfectFifth()};
	static ChordType power(powerList, 2);
	return power;
}
ChordType ChordType::tristan()
{
	const Interval tristanList[] = {Interval::unison(),Interval::augmentedFourth(), Interval::augmentedSixth(), Interval::augmentedNinth()};
	static ChordType tristan(tristanList, 4);
	return tristan;
}

/*******************************/
/* Constructors and destructor */
/*******************************/
ChordType::ChordType()
: IntervalClassSet(), m_Bass(Interval::undefined())
{
}

ChordType::~ChordType()
{
	// Nothing to do...
}

ChordType::ChordType(const Interval* inIntervalList, const int inNumOfIntervals, const Interval& inBass /*= Interval::undefined()*/)
: IntervalClassSet(inIntervalList, inNumOfIntervals), m_Bass(inBass)
{
}

/*************/
/* Operators */
/*************/
bool ChordType::operator==(const ChordType& inChordType) const
{
	return IntervalClassSet::operator==(inChordType) && m_Bass == inChordType.m_Bass;
}

bool ChordType::operator!=(const ChordType& inChordType) const
{
	return IntervalClassSet::operator!=(inChordType) || m_Bass != inChordType.m_Bass;
}

bool ChordType::operator<(const ChordType& inChordType) const
{
    if (m_IntervalList != inChordType.m_IntervalList)
    {
        return IntervalClassSet::operator<(inChordType);
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
    for (set<Interval>::const_iterator theIntervalIt = m_IntervalList.begin(); theIntervalIt != m_IntervalList.end(); ++theIntervalIt)
    {
        theInversions.push_back(ChordType(*this).addBass(*theIntervalIt));
    }
    return theInversions;
}

//const std::string ChordType::str() const
//{
//	ostringstream theChordTypeStream;
//	theChordTypeStream << "[";
//	if (!m_IntervalList.empty())
//	{
//		theChordTypeStream << m_IntervalList.begin()->circleStepsCW();
//	}
//	for (set<Interval>::const_iterator it = ++m_IntervalList.begin(); it != m_IntervalList.end(); ++it)
//	{
//		theChordTypeStream << "," << it->circleStepsCW();
//	}
//	theChordTypeStream << "]";
//	if (m_Bass != Interval::unison() && m_Bass != Interval::unknown())
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
        ChordType theTriadType;
        //if the formula contains major third
        if (m_IntervalList.count(Interval::majorThird()) > 0)
        {
            //if formula contains only augmented fifth
            if (m_IntervalList.count(Interval::augmentedFifth()) > 0 && m_IntervalList.count(Interval::perfectFifth()) == 0)
            {
                //augmented triad
                theTriadType = augmented();
            }
            //if formula contains only diminished fifth
            else if (m_IntervalList.count(Interval::diminishedFifth()) > 0 && m_IntervalList.count(Interval::perfectFifth()) == 0)
            {
                //majorb5 triad
                theTriadType = majorFlatFifth();
            }
            //if formula contains perfect fifth
            else //if (m_IntervalList.count(Interval::perfectFifth()) > 0)
            {
                //major triad
                theTriadType = major();
            }
        }
        //if formula contains minor third
        else if (m_IntervalList.count(Interval::minorThird()) > 0)
        {
            //if formula contains only diminished fifth
            if (m_IntervalList.count(Interval::diminishedFifth()) > 0 && m_IntervalList.count(Interval::perfectFifth()) == 0)
            {
                //diminished triad
                theTriadType = diminished();
            }
            //if formula contains only augmented fifth
            else if (m_IntervalList.count(Interval::augmentedFifth()) > 0 && m_IntervalList.count(Interval::perfectFifth()) == 0)
            {
                theTriadType = minorSharpFifth();
            }
            //if the formula contains perfect fifth
            else //if (m_IntervalList.count(Interval::perfectFifth()) > 0)
            {
                //minor triad
                theTriadType = minor();
            }
        }
        //if the formula contains perfect fourth (and no third or major second)
        else if (m_IntervalList.count(Interval::perfectFourth()) > 0 && m_IntervalList.count(Interval::majorSecond()) == 0)
        {
            //suspended fourth triad
            theTriadType = suspendedFourth();
        }
        //if the formula contains major second (and no third or perfect fourth)
        else if (m_IntervalList.count(Interval::majorSecond()) > 0 && m_IntervalList.count(Interval::perfectFourth()) == 0)
        {
            //suspended second triad
            theTriadType = suspendedSecond();
        }
        //if the formula only contains root and perfect fifth
        else if (m_IntervalList.count(Interval::unison()) > 0 && m_IntervalList.count(Interval::perfectFifth()) > 0)
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
        if (inWithBass && theTriadType.m_IntervalList.count(this->m_Bass) > 0)
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
        ChordType theTetradType;
        //if the formula contains major third
        if (m_IntervalList.count(Interval::majorThird()) > 0)
        {
            //if formula contains only augmented fifth
            if (m_IntervalList.count(Interval::augmentedFifth()) > 0 && m_IntervalList.count(Interval::perfectFifth()) == 0)
            {
                if (m_IntervalList.count(Interval::minorSeventh()) > 0)
                {
                    theTetradType = augmentedSeventh();
                }
                else if (m_IntervalList.count(Interval::majorSeventh()) > 0)
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
            else if (m_IntervalList.count(Interval::diminishedFifth()) > 0 && m_IntervalList.count(Interval::perfectFifth()) == 0)
            {
                if (m_IntervalList.count(Interval::minorSeventh()) > 0)
                {
                    theTetradType = majorFlatFifth().addInterval(Interval::minorSeventh());
                }
                else if (m_IntervalList.count(Interval::majorSeventh()) > 0)
                {
                    theTetradType = majorFlatFifth().addInterval(Interval::majorSeventh());
                }
                else
                {
                    //majorb5 triad
                    theTetradType = majorFlatFifth();
                }
            }
            //if formula contains minor seventh (no fifth necessary)
            else if (m_IntervalList.count(Interval::minorSeventh()) > 0)
            {
                theTetradType = dominantSeventh();
            }
            //if formula contains major seventh (no fifth necessary)
            else if (m_IntervalList.count(Interval::majorSeventh()) > 0)
            {
                theTetradType = majorSeventh();
            }
            //if formula contains major sixth (no fifth necessary)
            else if (m_IntervalList.count(Interval::majorSixth()) > 0)
            {
                theTetradType = majorSixth();
            }
            //if formula contains perfect fifth
            else //if (m_IntervalList.count(Interval::perfectFifth()) > 0)
            {
                //major triad
                theTetradType = major();
            }
        }
        //if formula contains minor third
        else if (m_IntervalList.count(Interval::minorThird()) > 0)
        {
            //if formula contains only diminished fifth
            if (m_IntervalList.count(Interval::diminishedFifth()) > 0 && m_IntervalList.count(Interval::perfectFifth()) == 0)
            {
                if (m_IntervalList.count(Interval::minorSeventh()) > 0)
                {
                    theTetradType = halfDiminished();
                }
                else if (m_IntervalList.count(Interval::diminishedSeventh()) > 0)
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
            else if (m_IntervalList.count(Interval::augmentedFifth()) > 0 && m_IntervalList.count(Interval::perfectFifth()) == 0)
            {
                if (m_IntervalList.count(Interval::minorSeventh()) > 0)
                {
                    theTetradType = minorSharpFifth().addInterval(Interval::minorSeventh());
                }
                else if (m_IntervalList.count(Interval::majorSeventh()) > 0)
                {
                    theTetradType = minorSharpFifth().addInterval(Interval::majorSeventh());
                }
                else
                {
                    theTetradType = minorSharpFifth();
                }
            }
            //if formula contains minor seventh (no fifth necessary)
            else if (m_IntervalList.count(Interval::minorSeventh()) > 0)
            {
                theTetradType = minorSeventh();
            }
            //if formula contains major seventh (no fifth necessary)
            else if (m_IntervalList.count(Interval::majorSeventh()) > 0)
            {
                theTetradType = minorMajorSeventh();
            }
            //if formula contains major sixth (no fifth necessary)
            else if (m_IntervalList.count(Interval::majorSixth()) > 0)
            {
                theTetradType = minorSixth();
            }
            //if the formula contains perfect fifth
            else //if (m_IntervalList.count(Interval::perfectFifth()) > 0)
            {
                //minor triad
                theTetradType = minor();
            }
        }
        //if the formula contains perfect fourth (and no third or major second)
        else if (m_IntervalList.count(Interval::perfectFourth()) > 0 && m_IntervalList.count(Interval::majorSecond()) == 0)
        {
            if (m_IntervalList.count(Interval::minorSeventh()) > 0)
            {
                theTetradType = suspendedFourthSeventh();
            }
            else if (m_IntervalList.count(Interval::majorSeventh()) > 0)
            {
                theTetradType = suspendedFourth().addInterval(Interval::majorSeventh());
            }
            //if formula contains major sixth (no fifth necessary)
            else if (m_IntervalList.count(Interval::majorSixth()) > 0)
            {
                theTetradType = suspendedFourth().addInterval(Interval::majorSixth());
            }
            else
            {
                //suspended fourth triad
                theTetradType = suspendedFourth();
            }
        }
        //if the formula contains major second (and no third or perfect fourth)
        else if (m_IntervalList.count(Interval::majorSecond()) > 0 && m_IntervalList.count(Interval::perfectFourth()) == 0)
        {
            if (m_IntervalList.count(Interval::minorSeventh()) > 0)
            {
                theTetradType = suspendedSecond().addInterval(Interval::minorSeventh());
            }
            else if (m_IntervalList.count(Interval::majorSeventh()) > 0)
            {
                theTetradType = suspendedSecond().addInterval(Interval::majorSeventh());
            }
            //if formula contains major sixth (no fifth necessary)
            else if (m_IntervalList.count(Interval::majorSixth()) > 0)
            {
                theTetradType = suspendedSecond().addInterval(Interval::majorSixth());
            }
            else
            {
                //suspended second triad
                theTetradType = suspendedSecond();
            }
        }
        //if the formula only contains root and perfect fifth
        else if (m_IntervalList.count(Interval::unison()) > 0 && m_IntervalList.count(Interval::perfectFifth()) > 0)
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
        if (inWithBass && theTetradType.m_IntervalList.count(this->m_Bass) > 0)
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
	for (set<Interval>::const_iterator it = inType.m_IntervalList.begin(); it != inType.m_IntervalList.end(); ++it)
	{
		deleteInterval(*it);
	}
}

void ChordType::subtract(const ChordType& inType, std::set<Interval>& outRestIntervals, std::set<Interval>& outMissingIntervals) const
{
    outRestIntervals = set<Interval>();
    std::set_difference(m_IntervalList.begin(), m_IntervalList.end(), inType.m_IntervalList.begin(), inType.m_IntervalList.end(), std::inserter(outRestIntervals, outRestIntervals.end()));
    outMissingIntervals = set<Interval>();
    std::set_difference(inType.m_IntervalList.begin(), inType.m_IntervalList.end(), m_IntervalList.begin(), m_IntervalList.end(), std::inserter(outMissingIntervals, outMissingIntervals.end()));
}

/**********************/
/* Overridden methods */
/**********************/
ChordType& ChordType::addInterval(const Interval& inInterval)
{
    IntervalClassSet::addInterval(inInterval);
    return *this;
}

ChordType& ChordType::deleteInterval(const Interval& inInterval)
{
    IntervalClassSet::deleteInterval(inInterval);
	if (m_Bass == inInterval)
	{
		m_Bass = Interval::undefined();
	}
	return *this;
}

ChordType& ChordType::replaceInterval(const Interval& inIntervalToReplace, const Interval& inReplacementInterval)
{
    IntervalClassSet::replaceInterval(inIntervalToReplace, inReplacementInterval);
	if (m_Bass == inIntervalToReplace)
	{
		m_Bass = inReplacementInterval;
	}
	return *this;
}

ChordType& ChordType::addBass(const Interval& inInterval)
{
	addInterval(inInterval);
	m_Bass = inInterval;
	return *this;
}

ChordType& ChordType::deleteBass()
{
	m_Bass = Interval::undefined();
	return *this;
}

const ChordType ChordType::withoutBass() const
{
	ChordType theChordType(*this);
	theChordType.m_Bass = Interval::undefined();
	return theChordType;
}

const bool ChordType::hasSpelling() const
{
    return IntervalClassSet::hasSpelling() && m_Bass.hasSpelling();
}

ChordType& ChordType::ignoreSpelling()
{
    IntervalClassSet::ignoreSpelling();
    m_Bass.ignoreSpelling();
	return *this;
}
