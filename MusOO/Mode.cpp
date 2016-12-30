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
	const SimpleInterval majorList[] = {SimpleInterval::unison(), SimpleInterval::majorSecond(), SimpleInterval::majorThird(), 
		SimpleInterval::perfectFourth(), SimpleInterval::perfectFifth(), SimpleInterval::majorSixth(), SimpleInterval::majorSeventh()};
	static const Mode major(majorList,7);
	return major;
}

Mode Mode::minorNatural()
{
	const SimpleInterval minorNaturalList[] = {SimpleInterval::unison(), SimpleInterval::majorSecond(), SimpleInterval::minorThird(), 
		SimpleInterval::perfectFourth(), SimpleInterval::perfectFifth(), SimpleInterval::minorSixth(), SimpleInterval::minorSeventh()};
	static const Mode minorNatural(minorNaturalList,7);
	return minorNatural;
}

Mode Mode::minorHarmonic()
{
	const SimpleInterval minorHarmonicList[] = {SimpleInterval::unison(), SimpleInterval::majorSecond(), SimpleInterval::minorThird(), 
		SimpleInterval::perfectFourth(), SimpleInterval::perfectFifth(), SimpleInterval::minorSixth(), SimpleInterval::majorSeventh()};
	static const Mode minorHarmonic(minorHarmonicList,7);
	return minorHarmonic;
}

Mode Mode::minorMelodic()
{
	const SimpleInterval minorMelodicList[] = {SimpleInterval::unison(), SimpleInterval::majorSecond(), SimpleInterval::minorThird(), 
		SimpleInterval::perfectFourth(), SimpleInterval::perfectFifth(), SimpleInterval::majorSixth(), SimpleInterval::majorSeventh()};
	static const Mode minorMelodic(minorMelodicList,7);
	return minorMelodic;
}

Mode Mode::minorGeneral()
{
	const SimpleInterval minorGeneralList[] = {SimpleInterval::unison(), SimpleInterval::majorSecond(), SimpleInterval::minorThird(),
		SimpleInterval::perfectFourth(), SimpleInterval::perfectFifth(), SimpleInterval::minorSixth(), SimpleInterval::majorSixth(), 
		SimpleInterval::minorSeventh(), SimpleInterval::majorSeventh()};
	static const Mode minorGeneral(minorGeneralList,9);
	return minorGeneral;
}

Mode Mode::dorian()
{
	const SimpleInterval dorianList[] = {SimpleInterval::unison(), SimpleInterval::majorSecond(), SimpleInterval::minorThird(), 
		SimpleInterval::perfectFourth(), SimpleInterval::perfectFifth(), SimpleInterval::majorSixth(), SimpleInterval::minorSeventh()};
	static const Mode dorian(dorianList,7);
	return dorian;
}

Mode Mode::phrygian()
{
	const SimpleInterval phrygianList[] = {SimpleInterval::unison(), SimpleInterval::minorSecond(), SimpleInterval::minorThird(), 
		SimpleInterval::perfectFourth(), SimpleInterval::perfectFifth(), SimpleInterval::minorSixth(), SimpleInterval::minorSeventh()};
	static const Mode phrygian(phrygianList,7);
	return phrygian;
}

Mode Mode::lydian()
{
	const SimpleInterval lydianList[] = {SimpleInterval::unison(), SimpleInterval::majorSecond(), SimpleInterval::majorThird(), 
		SimpleInterval::augmentedFourth(), SimpleInterval::perfectFifth(), SimpleInterval::majorSixth(), SimpleInterval::majorSeventh()};
	static const Mode lydian(lydianList,7);
	return lydian;
}

Mode Mode::mixolydian()
{
	const SimpleInterval mixolydianList[] = {SimpleInterval::unison(), SimpleInterval::majorSecond(), SimpleInterval::majorThird(), 
		SimpleInterval::perfectFourth(), SimpleInterval::perfectFifth(), SimpleInterval::majorSixth(), SimpleInterval::minorSeventh()};
	static const Mode mixolydian(mixolydianList,7);
	return mixolydian;
}

Mode Mode::aeolian()
{
	const SimpleInterval aeolianList[] = {SimpleInterval::unison(), SimpleInterval::majorSecond(), SimpleInterval::minorThird(), 
		SimpleInterval::perfectFourth(), SimpleInterval::perfectFifth(), SimpleInterval::minorSixth(), SimpleInterval::minorSeventh()};
	static const Mode aeolian(aeolianList,7);
	return aeolian;
}

Mode Mode::locrian()
{
	const SimpleInterval locrianList[] = {SimpleInterval::unison(), SimpleInterval::minorSecond(), SimpleInterval::minorThird(), 
		SimpleInterval::perfectFourth(), SimpleInterval::diminishedFifth(), SimpleInterval::minorSixth(), SimpleInterval::minorSeventh()};
	static const Mode locrian(locrianList,7);
	return locrian;
}

Mode Mode::modal()
{
	const SimpleInterval modalList[] = {SimpleInterval::unison()};
	static const Mode modal(modalList,1);
	return modal;
}

Mode::Mode()
: Set()
{
}

Mode::Mode(const SimpleInterval* inIntervalList, const int inNumOfIntervals)
: Set(inIntervalList, inNumOfIntervals)
{
}

Mode::~Mode()
{
}

size_t Mode::diatonicCircleDistance(const Interval& inInterval1, const Interval& inInterval2) const
{
	if ((m_set.count(inInterval1.simpleInterval()) == 0 || m_set.count(inInterval2.simpleInterval()) == 0) &&
		m_set.count(inInterval1.simpleInterval()) != m_set.count(inInterval2.simpleInterval()))
	{
		return m_set.size()/2;
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
	SimpleInterval theRootInterval = getDiatonicInterval(inDegree);
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

Mode& Mode::addInterval(const SimpleInterval& inInterval)
{
    Set::add(inInterval);
    return *this;
}

Mode& Mode::deleteInterval(const SimpleInterval& inInterval)
{
    Set::remove(inInterval);
	return *this;
}

Mode& Mode::replaceInterval(const SimpleInterval& inIntervalToReplace, const SimpleInterval& inReplacementInterval)
{
    Set::replace(inIntervalToReplace, inReplacementInterval);
	return *this;
}

bool Mode::isMajor() const
{
    return contains(SimpleInterval::majorThird());
}

bool Mode::isMinor() const
{
    return contains(SimpleInterval::minorThird());
}

