//============================================================================
/**
	Implementation file for Mode.h
	
	@author		Johan Pauwels
	@date		20100401
*/
//============================================================================

// Includes
#include "MusOO/Mode.h"
#include "MusOO/RelativeChord.h"
#include <cstdlib>
#include <sstream>
#include <algorithm>

using std::set;
using std::string;
using std::ostringstream;
using namespace MusOO;

Mode Mode::none()
{
	static const Mode none;
	return none;
}

Mode Mode::major()
{
	const Interval majorList[] = {Interval::unison(), Interval::majorSecond(), Interval::majorThird(), 
		Interval::perfectFourth(), Interval::perfectFifth(), Interval::majorSixth(), Interval::majorSeventh()};
	static const Mode major(majorList,7);
	return major;
}

Mode Mode::minorNatural()
{
	const Interval minorNaturalList[] = {Interval::unison(), Interval::majorSecond(), Interval::minorThird(), 
		Interval::perfectFourth(), Interval::perfectFifth(), Interval::minorSixth(), Interval::minorSeventh()};
	static const Mode minorNatural(minorNaturalList,7);
	return minorNatural;
}

Mode Mode::minorHarmonic()
{
	const Interval minorHarmonicList[] = {Interval::unison(), Interval::majorSecond(), Interval::minorThird(), 
		Interval::perfectFourth(), Interval::perfectFifth(), Interval::minorSixth(), Interval::majorSeventh()};
	static const Mode minorHarmonic(minorHarmonicList,7);
	return minorHarmonic;
}

Mode Mode::minorMelodic()
{
	const Interval minorMelodicList[] = {Interval::unison(), Interval::majorSecond(), Interval::minorThird(), 
		Interval::perfectFourth(), Interval::perfectFifth(), Interval::majorSixth(), Interval::majorSeventh()};
	static const Mode minorMelodic(minorMelodicList,7);
	return minorMelodic;
}

Mode Mode::minorGeneral()
{
	const Interval minorGeneralList[] = {Interval::unison(), Interval::majorSecond(), Interval::minorThird(),
		Interval::perfectFourth(), Interval::perfectFifth(), Interval::minorSixth(), Interval::majorSixth(), 
		Interval::minorSeventh(), Interval::majorSeventh()};
	static const Mode minorGeneral(minorGeneralList,9);
	return minorGeneral;
}

Mode Mode::dorian()
{
	const Interval dorianList[] = {Interval::unison(), Interval::majorSecond(), Interval::minorThird(), 
		Interval::perfectFourth(), Interval::perfectFifth(), Interval::majorSixth(), Interval::minorSeventh()};
	static const Mode dorian(dorianList,7);
	return dorian;
}

Mode Mode::phrygian()
{
	const Interval phrygianList[] = {Interval::unison(), Interval::minorSecond(), Interval::minorThird(), 
		Interval::perfectFourth(), Interval::perfectFifth(), Interval::minorSixth(), Interval::minorSeventh()};
	static const Mode phrygian(phrygianList,7);
	return phrygian;
}

Mode Mode::lydian()
{
	const Interval lydianList[] = {Interval::unison(), Interval::majorSecond(), Interval::majorThird(), 
		Interval::augmentedFourth(), Interval::perfectFifth(), Interval::majorSixth(), Interval::majorSeventh()};
	static const Mode lydian(lydianList,7);
	return lydian;
}

Mode Mode::mixolydian()
{
	const Interval mixolydianList[] = {Interval::unison(), Interval::majorSecond(), Interval::majorThird(), 
		Interval::perfectFourth(), Interval::perfectFifth(), Interval::majorSixth(), Interval::minorSeventh()};
	static const Mode mixolydian(mixolydianList,7);
	return mixolydian;
}

Mode Mode::aeolian()
{
	const Interval aeolianList[] = {Interval::unison(), Interval::majorSecond(), Interval::minorThird(), 
		Interval::perfectFourth(), Interval::perfectFifth(), Interval::minorSixth(), Interval::minorSeventh()};
	static const Mode aeolian(aeolianList,7);
	return aeolian;
}

Mode Mode::locrian()
{
	const Interval locrianList[] = {Interval::unison(), Interval::minorSecond(), Interval::minorThird(), 
		Interval::perfectFourth(), Interval::diminishedFifth(), Interval::minorSixth(), Interval::minorSeventh()};
	static const Mode locrian(locrianList,7);
	return locrian;
}

Mode Mode::modal()
{
	const Interval modalList[] = {Interval::unison()};
	static const Mode modal(modalList,1);
	return modal;
}

Mode::Mode()
: IntervalClassSet()
{
}

Mode::Mode(const Interval* inIntervalList, const int inNumOfIntervals)
: IntervalClassSet(inIntervalList, inNumOfIntervals)
{
}

Mode::~Mode()
{
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
	return std::min(std::abs(theDiatonicPosition1-theDiatonicPosition2), 7 - std::abs(theDiatonicPosition1-theDiatonicPosition2));
}

ptrdiff_t Mode::diatonicPosition(const ptrdiff_t inDiatonicNumber) const
{
	return 2 * (inDiatonicNumber % 4) + inDiatonicNumber / 4;
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

Mode& Mode::addInterval(const Interval& inInterval)
{
    IntervalClassSet::addInterval(inInterval);
    return *this;
}

Mode& Mode::deleteInterval(const Interval& inInterval)
{
    IntervalClassSet::deleteInterval(inInterval);
	return *this;
}

Mode& Mode::replaceInterval(const Interval& inIntervalToReplace, const Interval& inReplacementInterval)
{
    IntervalClassSet::replaceInterval(inIntervalToReplace, inReplacementInterval);
	return *this;
}
