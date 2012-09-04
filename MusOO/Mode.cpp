//============================================================================
/**
	Implementation file for Mode.h
	
	@author		Johan Pauwels
	@date		20100401
*/
//============================================================================

// Includes
#include <string>
	using std::string;
#include <sstream>
	using std::ostringstream;
#include "Mode.h"
#include "RelativeChord.h"

using std::set;

const Mode& Mode::noMode()
{
	static const Mode noMode;
	return noMode;
}

const Mode& Mode::major()
{
	const Interval majorList[] = {Interval::unison(), Interval::majorSecond(), Interval::majorThird(), 
		Interval::perfectFourth(), Interval::perfectFifth(), Interval::majorSixth(), Interval::majorSeventh()};
	static const Mode major(majorList,7);
	return major;
}

const Mode& Mode::minorNatural()
{
	const Interval minorNaturalList[] = {Interval::unison(), Interval::majorSecond(), Interval::minorThird(), 
		Interval::perfectFourth(), Interval::perfectFifth(), Interval::minorSixth(), Interval::minorSeventh()};
	static const Mode minorNatural(minorNaturalList,7);
	return minorNatural;
}

const Mode& Mode::minorHarmonic()
{
	const Interval minorHarmonicList[] = {Interval::unison(), Interval::majorSecond(), Interval::minorThird(), 
		Interval::perfectFourth(), Interval::perfectFifth(), Interval::minorSixth(), Interval::majorSeventh()};
	static const Mode minorHarmonic(minorHarmonicList,7);
	return minorHarmonic;
}

const Mode& Mode::minorMelodic()
{
	const Interval minorMelodicList[] = {Interval::unison(), Interval::majorSecond(), Interval::minorThird(), 
		Interval::perfectFourth(), Interval::perfectFifth(), Interval::majorSixth(), Interval::majorSeventh()};
	static const Mode minorMelodic(minorMelodicList,7);
	return minorMelodic;
}

const Mode& Mode::minorComposed()
{
	const Interval minorComposedList[] = {Interval::unison(), Interval::majorSecond(), Interval::minorThird(), 
		Interval::perfectFourth(), Interval::perfectFifth(), Interval::minorSixth(), Interval::majorSixth(), 
		Interval::minorSeventh(), Interval::majorSeventh()};
	static const Mode minorComposed(minorComposedList,9);
	return minorComposed;
}

const Mode& Mode::dorian()
{
	const Interval dorianList[] = {Interval::unison(), Interval::majorSecond(), Interval::minorThird(), 
		Interval::perfectFourth(), Interval::perfectFifth(), Interval::majorSixth(), Interval::minorSeventh()};
	static const Mode dorian(dorianList,7);
	return dorian;
}

const Mode& Mode::phrygian()
{
	const Interval phrygianList[] = {Interval::unison(), Interval::minorSecond(), Interval::minorThird(), 
		Interval::perfectFourth(), Interval::perfectFifth(), Interval::minorSixth(), Interval::minorSeventh()};
	static const Mode phrygian(phrygianList,7);
	return phrygian;
}

const Mode& Mode::lydian()
{
	const Interval lydianList[] = {Interval::unison(), Interval::majorSecond(), Interval::majorThird(), 
		Interval::augmentedFourth(), Interval::perfectFifth(), Interval::majorSixth(), Interval::majorSeventh()};
	static const Mode lydian(lydianList,7);
	return lydian;
}

const Mode& Mode::mixolydian()
{
	const Interval mixolydianList[] = {Interval::unison(), Interval::majorSecond(), Interval::majorThird(), 
		Interval::perfectFourth(), Interval::perfectFifth(), Interval::majorSixth(), Interval::minorSeventh()};
	static const Mode mixolydian(mixolydianList,7);
	return mixolydian;
}

const Mode& Mode::aeolian()
{
	const Interval aeolianList[] = {Interval::unison(), Interval::majorSecond(), Interval::minorThird(), 
		Interval::perfectFourth(), Interval::perfectFifth(), Interval::minorSixth(), Interval::minorSeventh()};
	static const Mode aeolian(aeolianList,7);
	return aeolian;
}

const Mode& Mode::locrian()
{
	const Interval locrianList[] = {Interval::unison(), Interval::minorSecond(), Interval::minorThird(), 
		Interval::perfectFourth(), Interval::diminishedFifth(), Interval::minorSixth(), Interval::minorSeventh()};
	static const Mode locrian(locrianList,7);
	return locrian;
}

const Mode& Mode::modal()
{
	const Interval modalList[] = {Interval::unison()};
	static const Mode modal(modalList,1);
	return modal;
}

Mode::Mode()
{
}

Mode::Mode(const Mode& inMode)
: m_IntervalList(inMode.m_IntervalList)
{
}

Mode::Mode(const Interval* inIntervalList, const int inNumOfIntervals)
: m_IntervalList(inIntervalList, inIntervalList+inNumOfIntervals)
{
}

Mode::~Mode()
{
}

const std::string Mode::str() const
{
	ostringstream theModeStream;
	theModeStream << "[";
	if (!m_IntervalList.empty())
	{
		theModeStream << m_IntervalList.begin()->circleStepsCW();
        for (set<Interval>::const_iterator i = ++m_IntervalList.begin(); i != m_IntervalList.end(); ++i)
        {
            theModeStream << ",";
            theModeStream << i->circleStepsCW();
        }
	}
	theModeStream << "]";
	return theModeStream.str();
}

bool Mode::operator==(const Mode& inMode) const
{
	return m_IntervalList == inMode.m_IntervalList;
}

bool Mode::operator!=(const Mode& inMode) const
{
	return m_IntervalList != inMode.m_IntervalList;
}

bool Mode::isMajor() const
{
	return m_IntervalList.count(Interval::majorThird()) > 0;
}

bool Mode::isMinor() const
{
	return m_IntervalList.count(Interval::minorThird()) > 0;
}

bool Mode::operator<(const Mode& inMode) const
{
	return m_IntervalList < inMode.m_IntervalList;
}

const size_t Mode::size() const
{
	return m_IntervalList.size();
}

size_t Mode::diatonicCircleDistance(const Interval& inInterval1, const Interval& inInterval2) const
{
	if ((m_IntervalList.count(inInterval1) == 0 || m_IntervalList.count(inInterval2) == 0) && 
		m_IntervalList.count(inInterval1) != m_IntervalList.count(inInterval2))
	{
		return m_IntervalList.size()/2;
	}
	ptrdiff_t theDiatonicPosition1 = diatonicPosition(inInterval1.diatonicNumber());
	ptrdiff_t theDiatonicPosition2 = diatonicPosition(inInterval2.diatonicNumber());
	return std::min(abs(theDiatonicPosition1-theDiatonicPosition2), 7 - abs(theDiatonicPosition1-theDiatonicPosition2));
}

ptrdiff_t Mode::diatonicPosition(const ptrdiff_t inDiatonicNumber) const
{
	return 2 * (inDiatonicNumber % 4) + inDiatonicNumber / 4;
}

const Interval& Mode::getDiatonicInterval(const size_t inDiatonicNumber) const
{
	for (set<Interval>::const_iterator it = m_IntervalList.begin(); it != m_IntervalList.end(); ++it)
	{
		if (it->diatonicNumber() == inDiatonicNumber)
		{
			return *it;
		}
	}
	return Interval::none();
}

RelativeChord Mode::diatonicTriad(size_t inDegree) const
{
	Interval theRootInterval = getDiatonicInterval(inDegree);
	ChordType theType = ChordType::rootOnly();
	theType.addInterval(getDiatonicInterval((inDegree+1)%7+1) - theRootInterval);
	theType.addInterval(getDiatonicInterval((inDegree+3)%7+1) - theRootInterval);
	return RelativeChord(theRootInterval, theType);
}

const size_t Mode::chromaticCOFDistance(Interval inRootInterval, const Mode& inMode) const
{
	if (isMinor())
	{
		inRootInterval -= Interval::minorThird();
	}
	if (inMode.isMinor())
	{
		inRootInterval += Interval::minorThird();
	}
	return std::min(inRootInterval.circleStepsCCW(), inRootInterval.circleStepsCW());
}
