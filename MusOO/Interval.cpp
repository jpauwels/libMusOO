//============================================================================
/**
	Implementation file for Interval.h

	@author		Johan Pauwels
	@date		20100916
*/
//============================================================================

// Includes
#include <cstdlib>
#include <cmath>
#include <stdexcept>
#include <sstream>
#include <limits>
#include <algorithm>
#include "MusOO/Interval.h"
#include "MusOO/Chroma.h"
#include "MusOO/Mode.h"

using std::map;
using std::pair;
using std::string;
using std::invalid_argument;
using std::istringstream;
using std::ostringstream;
using namespace MusOO;

const Interval& Interval::silence()
{
    static const Interval silence(SimpleInterval::silence(), 0);
	return silence;
}
const Interval& Interval::none()
{
	static const Interval none(SimpleInterval::none(), 0);
	return none;
}
const Interval& Interval::undefined()
{
	static const Interval undefined(SimpleInterval::undefined(), 0);
	return undefined;
}
Interval Interval::unison()
{
	static const Interval unison(SimpleInterval::unison(), 0);
	return unison;
}
Interval Interval::minorSecond()
{
	static const Interval minorSecond(SimpleInterval::minorSecond(), 0);
	return minorSecond;
}
Interval Interval::majorSecond()
{
	static const Interval majorSecond(SimpleInterval::majorSecond(), 0);
	return majorSecond;
}
Interval Interval::minorThird()
{
	static const Interval minorThird(SimpleInterval::minorThird(), 0);
	return minorThird;
}
Interval Interval::majorThird()
{
	static const Interval majorThird(SimpleInterval::majorThird(), 0);
	return majorThird;
}
Interval Interval::perfectFourth()
{
	static const Interval perfectFourth(SimpleInterval::perfectFourth(), 0);
	return perfectFourth;
}
Interval Interval::augmentedFourth()
{
	static const Interval augmentedFourth(SimpleInterval::augmentedFourth(), 0);
	return augmentedFourth;
}
Interval Interval::diminishedFifth()
{
	static const Interval diminishedFifth(SimpleInterval::diminishedFifth(), 0);
	return diminishedFifth;
}
Interval Interval::perfectFifth()
{
	static const Interval perfectFifth(SimpleInterval::perfectFifth(), 0);
	return perfectFifth;
}
Interval Interval::augmentedFifth()
{
	static const Interval augmentedFifth(SimpleInterval::augmentedFifth(), 0);
	return augmentedFifth;
}
Interval Interval::minorSixth()
{
	static const Interval minorSixth(SimpleInterval::minorSixth(), 0);
	return minorSixth;
}
Interval Interval::majorSixth()
{
	static const Interval majorSixth(SimpleInterval::majorSixth(), 0);
	return majorSixth;
}
Interval Interval::augmentedSixth()
{
	static const Interval augmentedSixth(SimpleInterval::augmentedSixth(), 0);
	return augmentedSixth;
}
Interval Interval::diminishedSeventh()
{
	static const Interval diminishedSeventh(SimpleInterval::diminishedSeventh(), 0);
	return diminishedSeventh;
}
Interval Interval::minorSeventh()
{
	static const Interval minorSeventh(SimpleInterval::minorSeventh(), 0);
	return minorSeventh;
}
Interval Interval::majorSeventh()
{
	static const Interval majorSeventh(SimpleInterval::majorSeventh(), 0);
	return majorSeventh;
}
Interval Interval::octave()
{
	static const Interval octave(SimpleInterval::unison(), 1);
	return octave;
}
Interval Interval::minorNinth()
{
	static const Interval minorNinth(SimpleInterval::minorSecond(), 1);
	return minorNinth;
}
Interval Interval::majorNinth()
{
	static const Interval majorNinth(SimpleInterval::majorSecond(), 1);
	return majorNinth;
}
Interval Interval::augmentedNinth()
{
	static const Interval augmentedNinth(SimpleInterval::augmentedSecond(), 1);
	return augmentedNinth;
}
Interval Interval::diminishedEleventh()
{
	static const Interval diminishedEleventh(SimpleInterval::diminishedFourth(), 1);
	return diminishedEleventh;
}
Interval Interval::perfectEleventh()
{
	static const Interval perfectEleventh(SimpleInterval::perfectFourth(), 1);
	return perfectEleventh;
}
Interval Interval::augmentedEleventh()
{
	static const Interval augmentedEleventh(SimpleInterval::augmentedFourth(), 1);
	return augmentedEleventh;
}
Interval Interval::minorThirteenth()
{
	static const Interval minorThirteenth(SimpleInterval::minorSixth(), 1);
	return minorThirteenth;
}
Interval Interval::majorThirteenth()
{
    static const Interval majorThirteenth(SimpleInterval::majorSixth(), 1);
	return majorThirteenth;
}

Interval::Interval()
: m_simpleInterval(SimpleInterval::undefined()), m_Octaves(0)
{
}

//Interval::Interval(const Chroma& inRoot, const Chroma& inOther, const bool inUp /*= true*/)
//: m_Octaves(0)
//{
//	if (!inRoot.isTrueChroma() || !inOther.isTrueChroma())
//	{
//		*this = undefined();
//	}
//	else
//	{
//		if (inUp)
//		{
//			m_LinePosition = inOther.m_LinePosition - inRoot.m_LinePosition;
//		}
//		else
//		{
//			m_LinePosition = inRoot.m_LinePosition - inOther.m_LinePosition;
//		}
//		m_HasSpelling = inRoot.hasSpelling() && inOther.hasSpelling();
//	}
//}
//
//Interval::Interval(const std::string& inMajorDegree, const bool inUp /*= true*/)
//{
//	//check for not allowed characters
//	if (inMajorDegree.find_first_not_of("#b1234567890") != string::npos)
//	{
//		throw invalid_argument("Major degree '" + inMajorDegree + "' contains unknown characters");
//	}
//	m_HasSpelling = true;
//	//split into modifiers and base degree
//	size_t theSplit = inMajorDegree.find_first_of("1234567890");
//	//convert base degree from string to int
//	size_t theBaseDegree;
//	istringstream (inMajorDegree.substr(theSplit,string::npos)) >> theBaseDegree;
//	//convert int base degree to distance in circle steps
//	m_LinePosition = s_MajorDegreeToCircleSteps.find(((theBaseDegree-1)%7)+1)->second;;
//	//apply modifiers
//	m_LinePosition += Chroma::stringModifierToCircleSteps(inMajorDegree.substr(0,theSplit));
//	m_Octaves = 0;
//	if (!inUp)
//	{
//		m_LinePosition = -m_LinePosition;
//	}
//}

//Interval::Interval(const std::string& inDegree, const Mode& inMode)
//{
//	ptrdiff_t theSemiTones;
//	if (inMode.isMajor())
//	{
//		theSemiTones = std::find(s_MajorDegrees.begin(), s_MajorDegrees.end(), inDegree) - s_MajorDegrees.begin();
//	}
//	else
//	{
//		theSemiTones = std::find(s_MinorDegrees.begin(), s_MinorDegrees.end(), inDegree) - s_MinorDegrees.begin();
//	}
//	m_LinePosition = ((7*theSemiTones % 12) + 12) % 12;
//	m_Octaves = 0;
//	m_HasSpelling = false;
//}

//Interval::Interval(int inCircleSteps, const bool inHasSpelling, const size_t inOctaves)
//: m_LinePosition(inCircleSteps), m_Octaves(inOctaves), m_HasSpelling(inHasSpelling)
//{
//}

Interval::Interval(const ptrdiff_t inSemiTones)
: m_simpleInterval(SimpleInterval(inSemiTones % 12)), m_Octaves(std::abs(inSemiTones) / 12)
{
}

Interval::Interval(const SimpleInterval& inSimpleInterval, const size_t inOctaves /*= 0*/)
: m_simpleInterval(inSimpleInterval), m_Octaves(inOctaves)
{
}

Interval::~Interval()
{
	// Nothing to do...
}

bool Interval::operator==(const Interval& inInterval) const
{
	if (m_Octaves != inInterval.m_Octaves)
	{
		return false;
	}
	else
	{
        return m_simpleInterval == inInterval.m_simpleInterval;
	}
}

bool Interval::operator!=(const Interval& inInterval) const
{
	return !operator==(inInterval);
}

bool Interval::operator<(const Interval& inInterval) const
{
	if (m_Octaves != inInterval.m_Octaves)
	{
		return m_Octaves < inInterval.m_Octaves;
	}
	else
	{
		return m_simpleInterval < inInterval.m_simpleInterval;
	}
}

const bool Interval::hasSpelling() const
{
	return m_simpleInterval.hasSpelling();
}

Interval Interval::withoutSpelling() const
{
    return Interval(*this).ignoreSpelling();
}

Interval& Interval::ignoreSpelling()
{
    if (isTrueInterval())
    {
        m_simpleInterval.ignoreSpelling();
    }
	return *this;
}

const ptrdiff_t Interval::semiTonesUp() const
{
    return m_simpleInterval.semiTonesUp() + 12 * m_Octaves;
}

const ptrdiff_t Interval::semiTonesDown() const
{
    return m_simpleInterval.semiTonesDown() - 12 * m_Octaves;
}

const ptrdiff_t Interval::circleStepsCW() const
{
    return m_simpleInterval.circleStepsCCW() + 12 * m_Octaves;
}

const ptrdiff_t Interval::circleStepsCCW() const
{
    return m_simpleInterval.circleStepsCCW() - 12 * m_Octaves;
}

const std::string Interval::majorDegree() const
{
    return m_simpleInterval.majorDegree();
}

const bool Interval::isTrueInterval() const
{
    return m_simpleInterval.isTrueSimpleInterval();
}

const ptrdiff_t Interval::diatonicNumber() const
{
    return m_simpleInterval.diatonicNumber() + 7 * m_Octaves;
}

Interval& Interval::operator+=(const Interval& inInterval)
{
	m_simpleInterval += inInterval.m_simpleInterval;
	m_Octaves += inInterval.m_Octaves;
	return *this;
}

Interval& Interval::operator-=(const Interval& inInterval)
{
	m_simpleInterval -= inInterval.m_simpleInterval;
	m_Octaves -= inInterval.m_Octaves;
	return *this;
}

const Interval Interval::operator+(const Interval& inInterval) const
{
	return Interval(*this) += inInterval;
}

const Interval Interval::operator-(const Interval& inInterval) const
{
	return Interval(*this) -= inInterval;
}

const std::string Interval::asDegree(const Mode& inMode) const
{
    return m_simpleInterval.asDegree(inMode);
}

const SimpleInterval& Interval::simpleInterval() const
{
    return m_simpleInterval;
}
