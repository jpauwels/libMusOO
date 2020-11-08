//============================================================================
/**
	Implementation file for SimpleInterval.h

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
#include "MusOO/SimpleInterval.h"
#include "MusOO/ChromaLetter.h"

using std::map;
using std::pair;
using std::string;
using std::invalid_argument;
using std::istringstream;
using std::ostringstream;
using namespace MusOO;

static const pair<size_t,ptrdiff_t> majorDegreeToCircleSteps[] = {pair<size_t,ptrdiff_t>(1,0),
pair<size_t,ptrdiff_t>(2,2), pair<size_t,ptrdiff_t>(3,4), pair<size_t,ptrdiff_t>(4,-1),
pair<size_t,ptrdiff_t>(5,1), pair<size_t,ptrdiff_t>(6,3), pair<size_t,ptrdiff_t>(7,5)};
const map<size_t,ptrdiff_t> SimpleInterval::s_MajorDegreeToCircleSteps(majorDegreeToCircleSteps,
																majorDegreeToCircleSteps+7);
static const pair<ptrdiff_t,size_t> circleStepsToMajorDegree[] = {pair<ptrdiff_t,size_t>(-1,4),
pair<ptrdiff_t,size_t>(0,1), pair<ptrdiff_t,size_t>(1,5), pair<ptrdiff_t,size_t>(2,2),
pair<ptrdiff_t,size_t>(3,6), pair<ptrdiff_t,size_t>(4,3), pair<ptrdiff_t,size_t>(5,7)};
const map<ptrdiff_t,size_t> SimpleInterval::s_CircleStepsToMajorDegree(circleStepsToMajorDegree,
																 circleStepsToMajorDegree+7);

const SimpleInterval& SimpleInterval::silence()
{
	static const SimpleInterval silence(std::numeric_limits<ptrdiff_t>::max(), true);
	return silence;
}
const SimpleInterval& SimpleInterval::none()
{
	static const SimpleInterval none(std::numeric_limits<ptrdiff_t>::max()-1, true);
	return none;
}
const SimpleInterval& SimpleInterval::undefined()
{
	static const SimpleInterval undefined(std::numeric_limits<ptrdiff_t>::max()-2, true);
	return undefined;
}
SimpleInterval SimpleInterval::unison()
{
	static const SimpleInterval prime(0, true);
	return prime;
}
SimpleInterval SimpleInterval::diminishedSecond()
{
    static const SimpleInterval diminishedSecond(-12, true);
    return diminishedSecond;
}
SimpleInterval SimpleInterval::minorSecond()
{
	static const SimpleInterval minorSecond(-5, true);
	return minorSecond;
}
SimpleInterval SimpleInterval::majorSecond()
{
	static const SimpleInterval majorSecond(2, true);
	return majorSecond;
}
SimpleInterval SimpleInterval::augmentedSecond()
{
    static const SimpleInterval augmentedSecond(9, true);
    return augmentedSecond;
}
SimpleInterval SimpleInterval::diminishedThird()
{
    static const SimpleInterval diminishedThird(-10, true);
    return diminishedThird;
}
SimpleInterval SimpleInterval::minorThird()
{
	static const SimpleInterval minorThird(-3, true);
	return minorThird;
}
SimpleInterval SimpleInterval::majorThird()
{
	static const SimpleInterval majorThird(4, true);
	return majorThird;
}
SimpleInterval SimpleInterval::augmentedThird()
{
    static const SimpleInterval augmentedThird(11, true);
    return augmentedThird;
}
SimpleInterval SimpleInterval::diminishedFourth()
{
    static const SimpleInterval diminishedFourth(-8, true);
    return diminishedFourth;
}
SimpleInterval SimpleInterval::perfectFourth()
{
	static const SimpleInterval perfectFourth(-1, true);
	return perfectFourth;
}
SimpleInterval SimpleInterval::augmentedFourth()
{
	static const SimpleInterval augmentedFourth(6, true);
	return augmentedFourth;
}
SimpleInterval SimpleInterval::diminishedFifth()
{
	static const SimpleInterval diminishedFifth(-6, true);
	return diminishedFifth;
}
SimpleInterval SimpleInterval::perfectFifth()
{
	static const SimpleInterval perfectFifth(1, true);
	return perfectFifth;
}
SimpleInterval SimpleInterval::augmentedFifth()
{
	static const SimpleInterval augmentedFifth(8, true);
	return augmentedFifth;
}
SimpleInterval SimpleInterval::diminishedSixth()
{
    static const SimpleInterval diminishedSixth(-11, true);
    return diminishedSixth;
}
SimpleInterval SimpleInterval::minorSixth()
{
	static const SimpleInterval minorSixth(-4, true);
	return minorSixth;
}
SimpleInterval SimpleInterval::majorSixth()
{
	static const SimpleInterval majorSixth(3, true);
	return majorSixth;
}
SimpleInterval SimpleInterval::augmentedSixth()
{
	static const SimpleInterval augmentedSixth(10, true);
	return augmentedSixth;
}
SimpleInterval SimpleInterval::diminishedSeventh()
{
	static const SimpleInterval diminishedSeventh(-9, true);
	return diminishedSeventh;
}
SimpleInterval SimpleInterval::minorSeventh()
{
	static const SimpleInterval minorSeventh(-2, true);
	return minorSeventh;
}
SimpleInterval SimpleInterval::majorSeventh()
{
	static const SimpleInterval majorSeventh(5, true);
	return majorSeventh;
}
SimpleInterval SimpleInterval::augmentedSeventh()
{
    static const SimpleInterval augmentedSeventh(12, true);
    return augmentedSeventh;
}

const std::string majorDegrees[] = {"I", "bII", "II", "bIII", "III", "IV", "bV", "V", "bVI", "VI", "bVII", "VII"};
const std::vector<std::string> SimpleInterval::s_MajorDegrees(majorDegrees, majorDegrees+12);

const std::string minorDegrees[] = {"I", "bII", "II", "III", "#III", "IV", "bV", "V", "VI", "#VI", "VII", "#VII"};
const std::vector<std::string> SimpleInterval::s_MinorDegrees(minorDegrees, minorDegrees+12);

SimpleInterval::SimpleInterval()
: m_LinePosition(std::numeric_limits<ptrdiff_t>::max()), m_HasSpelling(true)
{
}

SimpleInterval::SimpleInterval(const std::string& inMajorDegree, const bool inUp /*= true*/)
{
	//check for not allowed characters
	if (inMajorDegree.find_first_not_of("#b1234567890") != string::npos)
	{
		throw invalid_argument("Major degree '" + inMajorDegree + "' contains unknown characters");
	}
	m_HasSpelling = true;
	//split into modifiers and base degree
	size_t theSplit = inMajorDegree.find_first_of("1234567890");
	//convert base degree from string to int
	size_t theBaseDegree;
	istringstream (inMajorDegree.substr(theSplit,string::npos)) >> theBaseDegree;
	//convert int base degree to distance in circle steps
	m_LinePosition = s_MajorDegreeToCircleSteps.find(((theBaseDegree-1)%7)+1)->second;;
	//apply modifiers
	m_LinePosition += ChromaLetter::stringModifierToCircleSteps(inMajorDegree.substr(0,theSplit));
	if (!inUp)
	{
		m_LinePosition = -m_LinePosition;
	}
}

SimpleInterval::SimpleInterval(const ptrdiff_t inCircleSteps, const bool inHasSpelling)
: m_LinePosition(inCircleSteps), m_HasSpelling(inHasSpelling)
{
}

SimpleInterval::SimpleInterval(const ptrdiff_t inSemiTones)
: m_LinePosition(((7*inSemiTones % 12) + 12) % 12), m_HasSpelling(false)
{
}

SimpleInterval::~SimpleInterval()
{
	// Nothing to do...
}

bool SimpleInterval::operator==(const SimpleInterval& inSimpleInterval) const
{
    if (!isTrueSimpleInterval() || !inSimpleInterval.isTrueSimpleInterval() || (m_HasSpelling && inSimpleInterval.m_HasSpelling))
    {
        return m_LinePosition == inSimpleInterval.m_LinePosition;
    }
    else
    {
        return ((m_LinePosition % 12) + 12) % 12 == ((inSimpleInterval.m_LinePosition % 12) + 12) % 12;
    }
}

bool SimpleInterval::operator!=(const SimpleInterval& inSimpleInterval) const
{
	return !operator==(inSimpleInterval);
}

bool SimpleInterval::operator<(const SimpleInterval& inSimpleInterval) const
{
	if (!isTrueSimpleInterval() || !inSimpleInterval.isTrueSimpleInterval())
	{
		return m_LinePosition < inSimpleInterval.m_LinePosition;
	}
    if (((m_LinePosition % 12) + 12) % 12 != ((inSimpleInterval.m_LinePosition % 12) + 12) % 12)
    {
        return ((m_LinePosition % 12) + 12) % 12 < ((inSimpleInterval.m_LinePosition % 12) + 12) % 12;
    }
    else
    {
        if (m_HasSpelling && inSimpleInterval.m_HasSpelling)
        {
            return m_LinePosition < inSimpleInterval.m_LinePosition;
        }
        else
        {
            return false;
        }
	}
}

const bool SimpleInterval::hasSpelling() const
{
	return m_HasSpelling;
}

SimpleInterval SimpleInterval::withoutSpelling() const
{
    return SimpleInterval(*this).ignoreSpelling();
}

SimpleInterval& SimpleInterval::ignoreSpelling()
{
    if (isTrueSimpleInterval())
    {
        m_HasSpelling = false;
    }
	return *this;
}

const ptrdiff_t SimpleInterval::semiTonesUp() const
{
    if (!isTrueSimpleInterval())
    {
        throw invalid_argument("Only true SimpleIntervals can be raised a semitone");
    }
	return ((7*m_LinePosition % 12) + 12) % 12;
}

const ptrdiff_t SimpleInterval::semiTonesDown() const
{
    if (!isTrueSimpleInterval())
    {
        throw invalid_argument("Only true SimpleIntervals can be lowered a semitone");
    }
	return ((-7*m_LinePosition % 12) + 12) % 12;
}

const ptrdiff_t SimpleInterval::circleStepsCW() const
{
    if (!isTrueSimpleInterval())
    {
        throw invalid_argument("Circle steps can only be calculated for true SimpleIntervals");
    }
	return ((m_LinePosition % 12) + 12) % 12;
}

const ptrdiff_t SimpleInterval::circleStepsCCW() const
{
    if (!isTrueSimpleInterval())
    {
        throw invalid_argument("Circle steps can only be calculated for true SimpleIntervals");
    }
	return ((-m_LinePosition % 12) + 12) % 12;
}

const std::tuple<ptrdiff_t, ptrdiff_t> SimpleInterval::majorDegree() const
{
    if (*this == SimpleInterval::silence() || *this == SimpleInterval::none() || *this == SimpleInterval::undefined())
    {
        return std::make_tuple(0, this->m_LinePosition);
    }
    else
    {
        //limit the number of circle steps to the right range by adding modifiers
        ptrdiff_t theNumOfModifiers = static_cast<ptrdiff_t>(std::floor((m_LinePosition + 1) / 7.));
        //convert the range-limited circle steps to the degree
        ptrdiff_t naturalDegree = s_CircleStepsToMajorDegree.find(m_LinePosition-7*theNumOfModifiers)->second;
        return std::make_pair(theNumOfModifiers, naturalDegree);
    }
}

const std::string SimpleInterval::majorDegreeString() const
{
    if (*this == SimpleInterval::silence())
    {
        return "S";
    }
    else if (*this == SimpleInterval::none())
    {
        return "N";
    }
    else if (*this == SimpleInterval::undefined())
    {
        return "X";
    }
    else
    {
        //limit the number of circle steps to the right range by adding modifiers
        const auto majDegree = majorDegree();
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
        return modifiers + std::to_string(std::get<1>(majDegree));
    }
}

const bool SimpleInterval::isTrueSimpleInterval() const
{
	return m_LinePosition < std::numeric_limits<ptrdiff_t>::max()-2;
}

const ptrdiff_t SimpleInterval::diatonicNumber() const
{
	return ((4*m_LinePosition) % 7 + 7) % 7 + 1;
}

SimpleInterval& SimpleInterval::operator+=(const SimpleInterval& inSimpleInterval)
{
	m_LinePosition += inSimpleInterval.m_LinePosition;
	m_HasSpelling = m_HasSpelling && inSimpleInterval.m_HasSpelling;
	return *this;
}

SimpleInterval& SimpleInterval::operator-=(const SimpleInterval& inSimpleInterval)
{
	m_LinePosition -= inSimpleInterval.m_LinePosition;
	m_HasSpelling = m_HasSpelling && inSimpleInterval.m_HasSpelling;
	return *this;
}

const SimpleInterval SimpleInterval::operator+(const SimpleInterval& inSimpleInterval) const
{
	return SimpleInterval(*this) += inSimpleInterval;
}

const SimpleInterval SimpleInterval::operator-(const SimpleInterval& inSimpleInterval) const
{
	return SimpleInterval(*this) -= inSimpleInterval;
}
