//============================================================================
/**
	Implementation file for ChordType.h
	
	@author		Johan Pauwels
	@date		20100913
*/
//============================================================================

// Includes
#include <vector>
	using std::vector;
#include <sstream>
	using std::ostringstream;
#include <algorithm>
	using std::includes;
#include <stdexcept>
	using std::invalid_argument;
#include "ChordType.h"

using std::set;

ChordType ChordType::none()
{
	static ChordType noChord;
	return noChord;
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

ChordType::ChordType()
: m_Bass(Interval::unknown())
{
}

ChordType::~ChordType()
{
	// Nothing to do...
}

ChordType::ChordType(const Interval* inIntervalList, const int inNumOfIntervals, const Interval& inBass /*= Interval::unknown()*/)
: m_Formula(inIntervalList, inIntervalList+inNumOfIntervals), m_Bass(inBass)
{
}

bool ChordType::operator==(const ChordType& inChordType) const
{
	return equalTypes(inChordType);
}

bool ChordType::operator!=(const ChordType& inChordType) const
{
	return !equalTypes(inChordType);
}

bool ChordType::operator<(const ChordType& inChordType) const
{
	if (size() != inChordType.size())
	{
		return size() < inChordType.size();
	}
	else
	{
		if (m_Formula != inChordType.m_Formula)
		{
			return m_Formula < inChordType.m_Formula;
		}
		else
		{
			return m_Bass < inChordType.m_Bass;
		}
	}
}

const bool ChordType::equalTypes(const ChordType inType) const
{
	if (m_Formula.size() != inType.size())
	{
		return false;
	}
	return contains(inType) && m_Bass == inType.m_Bass;
}

const bool ChordType::contains(const ChordType inType) const
{
	return includes(m_Formula.begin(), m_Formula.end(), inType.m_Formula.begin(), inType.m_Formula.end());
}

const bool ChordType::contains(const Interval& inInterval) const
{
	return m_Formula.count(inInterval) > 0;
}

void ChordType::subtract(const ChordType& inType)
{
	if (!contains(inType))
	{
		throw invalid_argument("The subtractable chord type should contain all intervals of the chord type to be subtracted");
	}
	for (set<Interval>::const_iterator it = inType.m_Formula.begin(); it != inType.m_Formula.end(); ++it)
	{
		deleteInterval(*it);
	}
}

void ChordType::subtract(const ChordType& inType, std::vector<Interval>& outRestIntervals, std::vector<Interval>& outMissingIntervals) const
{
	outRestIntervals = vector<Interval>(size());
	vector<Interval>::iterator theNewEndIt = set_difference(m_Formula.begin(), m_Formula.end(), inType.m_Formula.begin(), inType.m_Formula.end(), outRestIntervals.begin());
	outRestIntervals.erase(theNewEndIt, outRestIntervals.end());
	outMissingIntervals = vector<Interval>(inType.size());
	theNewEndIt = set_difference(inType.m_Formula.begin(), inType.m_Formula.end(), m_Formula.begin(), m_Formula.end(), outMissingIntervals.begin());
	outMissingIntervals.erase(theNewEndIt, outMissingIntervals.end());
}

const size_t ChordType::size() const
{
	return m_Formula.size();
}

//const std::string ChordType::str() const
//{
//	ostringstream theChordTypeStream;
//	theChordTypeStream << "[";
//	if (!m_Formula.empty())
//	{
//		theChordTypeStream << m_Formula.begin()->circleStepsCW();
//	}
//	for (set<Interval>::const_iterator it = ++m_Formula.begin(); it != m_Formula.end(); ++it)
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

const ChordType ChordType::triad() const
{
	if (*this == ChordType::none())
	{
		return *this;
	}
	//if the formula contains major third
	else if (m_Formula.count(Interval::majorThird()) > 0)
	{
		//if formula contains augmented fifth
		if (m_Formula.count(Interval::augmentedFifth()) > 0)
		{
			//augmented triad
			return augmented();
		}
		//if formula contains diminished fifth
		else if (m_Formula.count(Interval::diminishedFifth()) > 0)
		{
			//majorb5 triad
			return majorFlatFifth();
		}
		//if formula contains perfect fifth
		else //if (m_Formula.count(Interval::perfectFifth()) > 0)
		{
			//major triad
			return major();
		}
	}
	//if formula contains minor third
	else if (m_Formula.count(Interval::minorThird()) > 0)
	{
		//if formula contains diminished fifth
		if (m_Formula.count(Interval::diminishedFifth()) > 0)
		{
			//diminished triad
			return diminished();
		}
		//if formula contains augmented fifth
		else if (m_Formula.count(Interval::augmentedFifth()) > 0)
		{
			return minorSharpFifth();
		}
		//if the formula contains perfect fifth
		else //if (m_Formula.count(Interval::perfectFifth()) > 0)
		{
			//minor triad
			return minor();
		}
	}
	//if the formula contains perfect fourth (and no third or major second)
	else if (m_Formula.count(Interval::perfectFourth()) > 0 && m_Formula.count(Interval::majorSecond()) == 0)
	{
		//suspended fourth triad
		return suspendedFourth();
	}
	//if the formula contains major second (and no third or perfect fourth)
	else if (m_Formula.count(Interval::majorSecond()) > 0 && m_Formula.count(Interval::perfectFourth()) == 0)
	{
		//suspended second triad
		return suspendedSecond();
	}
	//if the formula only contains root and perfect fifth
	else if (m_Formula.count(Interval::unison()) > 0 && m_Formula.count(Interval::perfectFifth()) > 0)
	{
		//power chord
		return power();
	}
	else
	{
		//if nothing else matches
		return rootOnly();
	}
}

const ChordType ChordType::tetrad() const
{
	if (*this == ChordType::none())
	{
		return *this;
	}
	//if the formula contains major third
	else if (m_Formula.count(Interval::majorThird()) > 0)
	{
		//if formula contains augmented fifth
		if (m_Formula.count(Interval::augmentedFifth()) > 0)
		{
			if (m_Formula.count(Interval::minorSeventh()) > 0)
			{
				return augmentedSeventh();
			}
			else if (m_Formula.count(Interval::majorSeventh()) > 0)
			{
				return augmentedMajorSeventh();
			}
			else
			{
				//augmented triad
				return augmented();
			}
		}
		//if formula contains diminished fifth
		else if (m_Formula.count(Interval::diminishedFifth()) > 0)
		{
			if (m_Formula.count(Interval::minorSeventh()) > 0)
			{
				return majorFlatFifth().addInterval(Interval::minorSeventh());
			}
			else if (m_Formula.count(Interval::majorSeventh()) > 0)
			{
				return majorFlatFifth().addInterval(Interval::majorSeventh());
			}
			else
			{
				//majorb5 triad
				return majorFlatFifth();
			}
		}
		//if formula contains minor seventh (no fifth necessary)
		else if (m_Formula.count(Interval::minorSeventh()) > 0)
		{
			return dominantSeventh();
		}
		//if formula contains major seventh (no fifth necessary)
		else if (m_Formula.count(Interval::majorSeventh()) > 0)
		{
			return majorSeventh();
		}
		//if formula contains major sixth (no fifth necessary)
		else if (m_Formula.count(Interval::majorSixth()) > 0)
		{
			return majorSixth();
		}
		//if formula contains perfect fifth
		else //if (m_Formula.count(Interval::perfectFifth()) > 0)
		{
			//major triad
			return major();
		}
	}
	//if formula contains minor third
	else if (m_Formula.count(Interval::minorThird()) > 0)
	{
		//if formula contains diminished fifth
		if (m_Formula.count(Interval::diminishedFifth()) > 0)
		{
			if (m_Formula.count(Interval::minorSeventh()) > 0)
			{
				return halfDiminished();
			}
			else if (m_Formula.count(Interval::diminishedSeventh()) > 0)
			{
				return diminishedSeventh();
			}
			else
			{
				//diminished triad
				return diminished();
			}
		}
		//if formula contains augmented fifth
		else if (m_Formula.count(Interval::augmentedFifth()) > 0)
		{
			if (m_Formula.count(Interval::minorSeventh()) > 0)
			{
				return minorSharpFifth().addInterval(Interval::minorSeventh());
			}
			else if (m_Formula.count(Interval::majorSeventh()) > 0)
			{
				return minorSharpFifth().addInterval(Interval::majorSeventh());
			}
			else
			{
				return minorSharpFifth();
			}
		}
		//if formula contains minor seventh (no fifth necessary)
		else if (m_Formula.count(Interval::minorSeventh()) > 0)
		{
			return minorSeventh();
		}
		//if formula contains major seventh (no fifth necessary)
		else if (m_Formula.count(Interval::majorSeventh()) > 0)
		{
			return minorMajorSeventh();
		}
		//if formula contains major sixth (no fifth necessary)
		else if (m_Formula.count(Interval::majorSixth()) > 0)
		{
			return minorSixth();
		}
		//if the formula contains perfect fifth
		else //if (m_Formula.count(Interval::perfectFifth()) > 0)
		{
			//minor triad
			return minor();
		}
	}
	//if the formula contains perfect fourth (and no third or major second)
	else if (m_Formula.count(Interval::perfectFourth()) > 0 && m_Formula.count(Interval::majorSecond()) == 0)
	{
		if (m_Formula.count(Interval::minorSeventh()) > 0)
		{
			return suspendedFourthSeventh();
		}
		else if (m_Formula.count(Interval::majorSeventh()) > 0)
		{
			return suspendedFourth().addInterval(Interval::majorSeventh());
		}
		//if formula contains major sixth (no fifth necessary)
		else if (m_Formula.count(Interval::majorSixth()) > 0)
		{
			return suspendedFourth().addInterval(Interval::majorSixth());
		}
		else
		{
			//suspended fourth triad
			return suspendedFourth();
		}
	}
	//if the formula contains major second (and no third or perfect fourth)
	else if (m_Formula.count(Interval::majorSecond()) > 0 && m_Formula.count(Interval::perfectFourth()) == 0)
	{
		if (m_Formula.count(Interval::minorSeventh()) > 0)
		{
			return suspendedSecond().addInterval(Interval::minorSeventh());
		}
		else if (m_Formula.count(Interval::majorSeventh()) > 0)
		{
			return suspendedSecond().addInterval(Interval::majorSeventh());
		}
		//if formula contains major sixth (no fifth necessary)
		else if (m_Formula.count(Interval::majorSixth()) > 0)
		{
			return suspendedSecond().addInterval(Interval::majorSixth());
		}
		else
		{
			//suspended second triad
			return suspendedSecond();
		}
	}
	//if the formula only contains root and perfect fifth
	else if (m_Formula.count(Interval::unison()) > 0 && m_Formula.count(Interval::perfectFifth()) > 0)
	{
		//power chord
		return power();
	}
	else
	{
		//if nothing else matches
		return rootOnly();
	}
}

const bool ChordType::isTriad() const
{
	return size() == 3;
}

const bool ChordType::hasChordalBass() const
{
	return m_Formula.count(m_Bass) > 0 || m_Bass == Interval::unknown();
}

ChordType& ChordType::addInterval(const Interval& inInterval)
{
	m_Formula.insert(inInterval);
	return *this;
}

ChordType& ChordType::addBass(const Interval& inInterval)
{
	m_Formula.insert(inInterval);
	m_Bass = inInterval;
	return *this;
}

ChordType& ChordType::deleteInterval(const Interval& inInterval)
{
	size_t theNumOfDeletes = m_Formula.erase(inInterval);
	if (theNumOfDeletes != 1)
	{
		throw invalid_argument("Interval to be deleted does not exist in chord");
	}
	if (m_Bass == inInterval)
	{
		m_Bass = Interval::unknown();
	}
	return *this;
}

ChordType& ChordType::deleteBass()
{
	m_Bass = Interval::unknown();
	return *this;
}

ChordType& ChordType::replaceInterval(const Interval& inIntervalToReplace, const Interval& inReplacementInterval)
{
	size_t theNumOfDeletes = m_Formula.erase(inIntervalToReplace);
	if (theNumOfDeletes != 1)
	{
		throw invalid_argument("Interval to be replaced does not exist in chord");
	}
	m_Formula.insert(inReplacementInterval);
	if (m_Bass == inIntervalToReplace)
	{
		m_Bass = inReplacementInterval;
	}
	return *this;
}

const ChordType ChordType::withoutBass() const
{
	ChordType theChordType(*this);
	theChordType.m_Bass = Interval::unknown();
	return theChordType;
}

const Interval& ChordType::getInterval(const size_t inDiatonicNumber) const
{
	for (set<Interval>::const_iterator it = m_Formula.begin(); it != m_Formula.end(); ++it)
	{
		if (it->diatonicNumber() == inDiatonicNumber)
		{
			return *it;
		}
	}
	return Interval::none();
}
