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
#include "MusOO/ComplexInterval.h"
#include "MusOO/Chroma.h"
#include "MusOO/Mode.h"

using std::map;
using std::pair;
using std::string;
using std::invalid_argument;
using std::istringstream;
using std::ostringstream;
using namespace MusOO;

const ComplexInterval& ComplexInterval::silence()
{
    static const ComplexInterval silence(SimpleInterval::silence(), 0);
	return silence;
}
const ComplexInterval& ComplexInterval::none()
{
	static const ComplexInterval none(SimpleInterval::none(), 0);
	return none;
}
const ComplexInterval& ComplexInterval::undefined()
{
	static const ComplexInterval undefined(SimpleInterval::undefined(), 0);
	return undefined;
}
ComplexInterval ComplexInterval::unison()
{
	static const ComplexInterval unison(SimpleInterval::unison(), 0);
	return unison;
}
ComplexInterval ComplexInterval::minorSecond()
{
	static const ComplexInterval minorSecond(SimpleInterval::minorSecond(), 0);
	return minorSecond;
}
ComplexInterval ComplexInterval::majorSecond()
{
	static const ComplexInterval majorSecond(SimpleInterval::majorSecond(), 0);
	return majorSecond;
}
ComplexInterval ComplexInterval::minorThird()
{
	static const ComplexInterval minorThird(SimpleInterval::minorThird(), 0);
	return minorThird;
}
ComplexInterval ComplexInterval::majorThird()
{
	static const ComplexInterval majorThird(SimpleInterval::majorThird(), 0);
	return majorThird;
}
ComplexInterval ComplexInterval::perfectFourth()
{
	static const ComplexInterval perfectFourth(SimpleInterval::perfectFourth(), 0);
	return perfectFourth;
}
ComplexInterval ComplexInterval::augmentedFourth()
{
	static const ComplexInterval augmentedFourth(SimpleInterval::augmentedFourth(), 0);
	return augmentedFourth;
}
ComplexInterval ComplexInterval::diminishedFifth()
{
	static const ComplexInterval diminishedFifth(SimpleInterval::diminishedFifth(), 0);
	return diminishedFifth;
}
ComplexInterval ComplexInterval::perfectFifth()
{
	static const ComplexInterval perfectFifth(SimpleInterval::perfectFifth(), 0);
	return perfectFifth;
}
ComplexInterval ComplexInterval::augmentedFifth()
{
	static const ComplexInterval augmentedFifth(SimpleInterval::augmentedFifth(), 0);
	return augmentedFifth;
}
ComplexInterval ComplexInterval::minorSixth()
{
	static const ComplexInterval minorSixth(SimpleInterval::minorSixth(), 0);
	return minorSixth;
}
ComplexInterval ComplexInterval::majorSixth()
{
	static const ComplexInterval majorSixth(SimpleInterval::majorSixth(), 0);
	return majorSixth;
}
ComplexInterval ComplexInterval::augmentedSixth()
{
	static const ComplexInterval augmentedSixth(SimpleInterval::augmentedSixth(), 0);
	return augmentedSixth;
}
ComplexInterval ComplexInterval::diminishedSeventh()
{
	static const ComplexInterval diminishedSeventh(SimpleInterval::diminishedSeventh(), 0);
	return diminishedSeventh;
}
ComplexInterval ComplexInterval::minorSeventh()
{
	static const ComplexInterval minorSeventh(SimpleInterval::minorSeventh(), 0);
	return minorSeventh;
}
ComplexInterval ComplexInterval::majorSeventh()
{
	static const ComplexInterval majorSeventh(SimpleInterval::majorSeventh(), 0);
	return majorSeventh;
}
ComplexInterval ComplexInterval::octave()
{
	static const ComplexInterval octave(SimpleInterval::unison(), 1);
	return octave;
}
ComplexInterval ComplexInterval::minorNinth()
{
	static const ComplexInterval minorNinth(SimpleInterval::minorSecond(), 1);
	return minorNinth;
}
ComplexInterval ComplexInterval::majorNinth()
{
	static const ComplexInterval majorNinth(SimpleInterval::majorSecond(), 1);
	return majorNinth;
}
ComplexInterval ComplexInterval::augmentedNinth()
{
	static const ComplexInterval augmentedNinth(SimpleInterval::augmentedSecond(), 1);
	return augmentedNinth;
}
ComplexInterval ComplexInterval::diminishedEleventh()
{
	static const ComplexInterval diminishedEleventh(SimpleInterval::diminishedFourth(), 1);
	return diminishedEleventh;
}
ComplexInterval ComplexInterval::perfectEleventh()
{
	static const ComplexInterval perfectEleventh(SimpleInterval::perfectFourth(), 1);
	return perfectEleventh;
}
ComplexInterval ComplexInterval::augmentedEleventh()
{
	static const ComplexInterval augmentedEleventh(SimpleInterval::augmentedFourth(), 1);
	return augmentedEleventh;
}
ComplexInterval ComplexInterval::minorThirteenth()
{
	static const ComplexInterval minorThirteenth(SimpleInterval::minorSixth(), 1);
	return minorThirteenth;
}
ComplexInterval ComplexInterval::majorThirteenth()
{
    static const ComplexInterval majorThirteenth(SimpleInterval::majorSixth(), 1);
	return majorThirteenth;
}

ComplexInterval::ComplexInterval()
: m_simpleInterval(SimpleInterval::undefined()), m_Octaves(0)
{
}

ComplexInterval::ComplexInterval(const Chroma& inRoot, const Chroma& inOther, const bool inUp /*= true*/)
: m_Octaves(0)
{
	if (!inRoot.isTrueChroma() || !inOther.isTrueChroma())
	{
		*this = undefined();
	}
	else
	{
        ptrdiff_t linePosition;
		if (inUp)
		{
			linePosition = inOther.m_LinePosition - inRoot.m_LinePosition;
		}
		else
		{
			linePosition = inRoot.m_LinePosition - inOther.m_LinePosition;
		}
		m_simpleInterval = SimpleInterval(linePosition, inRoot.hasSpelling() && inOther.hasSpelling());
	}
}

//ComplexInterval::ComplexInterval(const std::string& inMajorDegree, const bool inUp /*= true*/)
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

//ComplexInterval::ComplexInterval(const std::string& inDegree, const Mode& inMode)
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

ComplexInterval::ComplexInterval(const ptrdiff_t inSemiTones)
: m_simpleInterval(SimpleInterval(inSemiTones % 12)), m_Octaves(std::abs(inSemiTones) / 12)
{
}

ComplexInterval::ComplexInterval(const SimpleInterval& inSimpleInterval, const size_t inOctaves /*= 0*/)
: m_simpleInterval(inSimpleInterval), m_Octaves(inOctaves)
{
}

ComplexInterval::~ComplexInterval()
{
	// Nothing to do...
}

bool ComplexInterval::operator==(const ComplexInterval& inComplexInterval) const
{
	if (m_Octaves != inComplexInterval.m_Octaves)
	{
		return false;
	}
	else
	{
        return m_simpleInterval == inComplexInterval.m_simpleInterval;
	}
}

bool ComplexInterval::operator!=(const ComplexInterval& inComplexInterval) const
{
	return !operator==(inComplexInterval);
}

bool ComplexInterval::operator<(const ComplexInterval& inComplexInterval) const
{
	if (m_Octaves != inComplexInterval.m_Octaves)
	{
		return m_Octaves < inComplexInterval.m_Octaves;
	}
	else
	{
		return m_simpleInterval < inComplexInterval.m_simpleInterval;
	}
}

const bool ComplexInterval::hasSpelling() const
{
	return m_simpleInterval.hasSpelling();
}

ComplexInterval ComplexInterval::withoutSpelling() const
{
    return ComplexInterval(*this).ignoreSpelling();
}

ComplexInterval& ComplexInterval::ignoreSpelling()
{
    if (isTrueInterval())
    {
        m_simpleInterval.ignoreSpelling();
    }
	return *this;
}

const ptrdiff_t ComplexInterval::semiTonesUp() const
{
    return m_simpleInterval.semiTonesUp() + 12 * m_Octaves;
}

const ptrdiff_t ComplexInterval::semiTonesDown() const
{
    return m_simpleInterval.semiTonesDown() - 12 * m_Octaves;
}

const ptrdiff_t ComplexInterval::circleStepsCW() const
{
    return m_simpleInterval.circleStepsCCW() + 12 * m_Octaves;
}

const ptrdiff_t ComplexInterval::circleStepsCCW() const
{
    return m_simpleInterval.circleStepsCCW() - 12 * m_Octaves;
}

const std::string ComplexInterval::majorDegreeString() const
{
    if (*this == ComplexInterval::silence())
    {
        return "S";
    }
    else if (*this == ComplexInterval::none())
    {
        return "N";
    }
    else if (*this == ComplexInterval::undefined())
    {
        return "X";
    }
    else
    {
        //limit the number of circle steps to the right range by adding modifiers
        const auto majDegree = m_simpleInterval.majorDegree();
        const ptrdiff_t numModifiers = std::get<0>(majDegree);
        string modifiers = "";
        if (numModifiers > 0)
        {
            modifiers = string(numModifiers, '#');
        }
        else if (numModifiers < 0)
        {
            modifiers = string(-numModifiers, 'b');
        }
        return modifiers + std::to_string(7*m_Octaves+std::get<1>(majDegree));
    }
}

const bool ComplexInterval::isTrueInterval() const
{
    return m_simpleInterval.isTrueSimpleInterval();
}

const ptrdiff_t ComplexInterval::diatonicNumber() const
{
    return m_simpleInterval.diatonicNumber() + 7 * m_Octaves;
}

ComplexInterval& ComplexInterval::operator+=(const ComplexInterval& inComplexInterval)
{
	m_simpleInterval += inComplexInterval.m_simpleInterval;
	m_Octaves += inComplexInterval.m_Octaves;
	return *this;
}

ComplexInterval& ComplexInterval::operator-=(const ComplexInterval& inComplexInterval)
{
	m_simpleInterval -= inComplexInterval.m_simpleInterval;
	m_Octaves -= inComplexInterval.m_Octaves;
	return *this;
}

const ComplexInterval ComplexInterval::operator+(const ComplexInterval& inComplexInterval) const
{
	return ComplexInterval(*this) += inComplexInterval;
}

const ComplexInterval ComplexInterval::operator-(const ComplexInterval& inComplexInterval) const
{
	return ComplexInterval(*this) -= inComplexInterval;
}

const std::string ComplexInterval::asDegree(const Mode& inMode) const
{
    return m_simpleInterval.asDegree(inMode);
}

const SimpleInterval& ComplexInterval::simpleInterval() const
{
    return m_simpleInterval;
}
