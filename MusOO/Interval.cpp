//============================================================================
/**
	Implementation file for Interval.h

	@author		Johan Pauwels
	@date		20100916
*/
//============================================================================

// Includes
#include <cstdlib>
#include <stdexcept>
#include <sstream>
#include <limits>
#include <algorithm>
#include "Interval.h"
#include "Chroma.h"
#include "Mode.h"

using std::map;
using std::pair;
using std::string;
using std::invalid_argument;
using std::istringstream;
using std::ostringstream;

static const pair<size_t,ptrdiff_t> majorDegreeToCircleSteps[] = {pair<size_t,ptrdiff_t>(1,0),
pair<size_t,ptrdiff_t>(2,2), pair<size_t,ptrdiff_t>(3,4), pair<size_t,ptrdiff_t>(4,-1),
pair<size_t,ptrdiff_t>(5,1), pair<size_t,ptrdiff_t>(6,3), pair<size_t,ptrdiff_t>(7,5)};
const map<size_t,ptrdiff_t> Interval::s_MajorDegreeToCircleSteps(majorDegreeToCircleSteps,
																majorDegreeToCircleSteps+7);
static const pair<ptrdiff_t,size_t> circleStepsToMajorDegree[] = {pair<ptrdiff_t,size_t>(-1,4),
pair<ptrdiff_t,size_t>(0,1), pair<ptrdiff_t,size_t>(1,5), pair<ptrdiff_t,size_t>(2,2),
pair<ptrdiff_t,size_t>(3,6), pair<ptrdiff_t,size_t>(4,3), pair<ptrdiff_t,size_t>(5,7)};
const map<ptrdiff_t,size_t> Interval::s_CircleStepsToMajorDegree(circleStepsToMajorDegree,
																 circleStepsToMajorDegree+7);

const  Interval& Interval::silence()
{
	static const Interval silence(std::numeric_limits<int>::max()-2, true, 0);
	return silence;
}
const  Interval& Interval::none()
{
	static const Interval none(std::numeric_limits<int>::max()-1, true, 0);
	return none;
}
const  Interval& Interval::undefined()
{
	static const Interval undefined(std::numeric_limits<int>::max(), true, 0);
	return undefined;
}
const Interval& Interval::unison()
{
	static const Interval prime(0, true, 0);
	return prime;
}
const Interval& Interval::minorSecond()
{
	static const Interval minorSecond(-5, true, 0);
	return minorSecond;
}
const Interval& Interval::majorSecond()
{
	static const Interval majorSecond(2, true, 0);
	return majorSecond;
}
const Interval& Interval::minorThird()
{
	static const Interval minorThird(-3, true, 0);
	return minorThird;
}
const Interval& Interval::majorThird()
{
	static const Interval majorThird(4, true, 0);
	return majorThird;
}
const Interval& Interval::perfectFourth()
{
	static const Interval perfectFourth(-1, true, 0);
	return perfectFourth;
}
const Interval& Interval::augmentedFourth()
{
	static const Interval augmentedFourth(6, true, 0);
	return augmentedFourth;
}
const Interval& Interval::diminishedFifth()
{
	static const Interval diminishedFifth(-6, true, 0);
	return diminishedFifth;
}
const Interval& Interval::perfectFifth()
{
	static const Interval perfectFifth(1, true, 0);
	return perfectFifth;
}
const Interval& Interval::augmentedFifth()
{
	static const Interval augmentedFifth(8, true, 0);
	return augmentedFifth;
}
const Interval& Interval::minorSixth()
{
	static const Interval minorSixth(-4, true, 0);
	return minorSixth;
}
const Interval& Interval::majorSixth()
{
	static const Interval majorSixth(3, true, 0);
	return majorSixth;
}
const Interval& Interval::augmentedSixth()
{
	static const Interval augmentedSixth(10, true, 0);
	return augmentedSixth;
}
const Interval& Interval::diminishedSeventh()
{
	static const Interval diminishedSeventh(-9, true, 0);
	return diminishedSeventh;
}
const Interval& Interval::minorSeventh()
{
	static const Interval minorSeventh(-2, true, 0);
	return minorSeventh;
}
const Interval& Interval::majorSeventh()
{
	static const Interval majorSeventh(5, true, 0);
	return majorSeventh;
}
const Interval& Interval::octave()
{
	static const Interval octave(0, true, 1);
	return octave;
}
const Interval& Interval::minorNinth()
{
	static const Interval minorNinth(-5, true, 1);
	return minorNinth;
}
const Interval& Interval::majorNinth()
{
	static const Interval majorNinth(2, true, 1);
	return majorNinth;
}
const Interval& Interval::augmentedNinth()
{
	static const Interval augmentedNinth(9, true, 1);
	return augmentedNinth;
}
const Interval& Interval::diminishedEleventh()
{
	static const Interval diminishedEleventh(-8, true, 1);
	return diminishedEleventh;
}
const Interval& Interval::perfectEleventh()
{
	static const Interval perfectEleventh(-1, true, 1);
	return perfectEleventh;
}
const Interval& Interval::augmentedEleventh()
{
	static const Interval augmentedEleventh(6, true, 1);
	return augmentedEleventh;
}
const Interval& Interval::minorThirteenth()
{
	static const Interval minorThirteenth(-4, true, 1);
	return minorThirteenth;
}
const Interval& Interval::majorThirteenth()
{
	static const Interval majorThirteenth(3, true, 1);
	return majorThirteenth;
}

const std::string majorDegrees[] = {"I", "bII", "II", "bIII", "III", "IV", "bV", "V", "bVI", "VI", "bVII", "VII"};
const std::vector<std::string> Interval::s_MajorDegrees(majorDegrees, majorDegrees+12);

const std::string minorDegrees[] = {"I", "bII", "II", "III", "#III", "IV", "bV", "V", "VI", "#VI", "VII", "#VII"};
const std::vector<std::string> Interval::s_MinorDegrees(minorDegrees, minorDegrees+12);

Interval::Interval()
: m_Octaves(0), m_HasSpelling(true), m_CircleSteps(std::numeric_limits<int>::max())
{
}

Interval::Interval(const Chroma& inRoot, const Chroma& inOther, const bool inUp /*= true*/)
: m_Octaves(0)
{
	if (!inRoot.isTrueChroma() || !inOther.isTrueChroma())
	{
		*this = undefined();
	}
	else
	{
		if (inUp)
		{
			m_CircleSteps = inOther.m_CirclePosition - inRoot.m_CirclePosition;
		}
		else
		{
			m_CircleSteps = inRoot.m_CirclePosition - inOther.m_CirclePosition;
		}
		m_HasSpelling = inRoot.hasSpelling() && inOther.hasSpelling();
	}
}

Interval::Interval(const std::string& inMajorDegree, const bool inUp /*= true*/)
{
	//check for not allowed characters
	if (inMajorDegree.find_first_not_of("#b1234567890") != string::npos)
	{
		throw invalid_argument("Major degree " + inMajorDegree + " contains unknown characters");
	}
	m_HasSpelling = true;
	//split into modifiers and base degree
	size_t theSplit = inMajorDegree.find_first_of("1234567890");
	//convert base degree from string to int
	size_t theBaseDegree;
	istringstream (inMajorDegree.substr(theSplit,string::npos)) >> theBaseDegree;
	//convert int base degree to distance in circle steps
	m_CircleSteps = s_MajorDegreeToCircleSteps.find(((theBaseDegree-1)%7)+1)->second;;
	//apply modifiers
	m_CircleSteps += Chroma::stringModifierToCircleSteps(inMajorDegree.substr(0,theSplit));
	m_Octaves = 0;
	if (!inUp)
	{
		m_CircleSteps = -m_CircleSteps;
	}
}

Interval::Interval(const std::string& inDegree, const Mode& inMode)
{
	ptrdiff_t theSemiTones;
	if (inMode.isMajor())
	{
		theSemiTones = std::find(s_MajorDegrees.begin(), s_MajorDegrees.end(), inDegree) - s_MajorDegrees.begin();
	}
	else
	{
		theSemiTones = std::find(s_MinorDegrees.begin(), s_MinorDegrees.end(), inDegree) - s_MinorDegrees.begin();
	}
	m_CircleSteps = ((7*theSemiTones % 12) + 12) % 12;
	m_Octaves = 0;
	m_HasSpelling = false;
}

Interval::Interval(int inCircleSteps, const bool inHasSpelling, const size_t inOctaves)
: m_CircleSteps(inCircleSteps), m_Octaves(inOctaves), m_HasSpelling(inHasSpelling)
{
}

Interval::Interval(const int inSemiTones)
: m_CircleSteps(((7*inSemiTones % 12) + 12) % 12), m_Octaves(abs(inSemiTones) / 12), m_HasSpelling(false)
{
}

Interval::~Interval()
{
	// Nothing to do...
}

bool Interval::operator==(const Interval& inInterval) const
{
	if (!isTrueInterval() || !inInterval.isTrueInterval())
	{
		return m_CircleSteps == inInterval.m_CircleSteps;
	}
	if (m_Octaves != inInterval.m_Octaves)
	{
		return false;
	}
	else
	{
		if (((m_CircleSteps % 12) + 12) % 12 != ((inInterval.m_CircleSteps % 12) + 12) % 12)
		{
			return false;
		}
		else
		{
			if (m_HasSpelling && inInterval.m_HasSpelling)
			{
				return m_CircleSteps == inInterval.m_CircleSteps;
			}
			else
			{
				return true;
			}
		}
	}
}

bool Interval::operator!=(const Interval& inInterval) const
{
	return !operator==(inInterval);
}

bool Interval::operator<(const Interval& inInterval) const
{
	if (!isTrueInterval() || !inInterval.isTrueInterval())
	{
		return m_CircleSteps < inInterval.m_CircleSteps;
	}
	if (m_Octaves != inInterval.m_Octaves)
	{
		return m_Octaves < inInterval.m_Octaves;
	}
	else
	{
		if (((m_CircleSteps % 12) + 12) % 12 != ((inInterval.m_CircleSteps % 12) + 12) % 12)
		{
			return ((m_CircleSteps % 12) + 12) % 12 < ((inInterval.m_CircleSteps % 12) + 12) % 12;
		}
		else
		{
			if (m_HasSpelling && inInterval.m_HasSpelling)
			{
				return m_CircleSteps < inInterval.m_CircleSteps;
			}
			else
			{
				return false;
			}
		}
	}
}

const bool Interval::hasSpelling() const
{
	return m_HasSpelling;
}

const Interval& Interval::ignoreSpelling()
{
	m_HasSpelling = false;
	return *this;
}

const ptrdiff_t Interval::semiTonesUp() const
{
	return ((7*m_CircleSteps % 12) + 12) % 12;
}

const ptrdiff_t Interval::semiTonesDown() const
{
	return ((-7*m_CircleSteps % 12) + 12) % 12;
}

const ptrdiff_t Interval::circleStepsCW() const
{
	return ((m_CircleSteps % 12) + 12) % 12;
}

const ptrdiff_t Interval::circleStepsCCW() const
{
	return ((-m_CircleSteps % 12) + 12) % 12;
}

const std::string Interval::majorDegree() const
{
	//limit the number of circle steps to the right range by adding modifiers
	string theDegree = "";
	ptrdiff_t theCircleSteps(m_CircleSteps);
	while (theCircleSteps < s_CircleStepsToMajorDegree.begin()->first)
	{
		theDegree.append("b");
		theCircleSteps += 7;
	}
	while (s_CircleStepsToMajorDegree.lower_bound(theCircleSteps) == s_CircleStepsToMajorDegree.end())
	{
		theDegree.append("#");
		theCircleSteps -= 7;
	}
	//convert the range-limited circle steps to the degree
	ostringstream theStream;
	theStream << s_CircleStepsToMajorDegree.find(theCircleSteps)->second;
	theDegree.append(theStream.str());
	return theDegree;
}

const bool Interval::isTrueInterval() const
{
	return m_CircleSteps != silence().m_CircleSteps && m_CircleSteps != none().m_CircleSteps && 
		m_CircleSteps != undefined().m_CircleSteps;
}

const ptrdiff_t Interval::diatonicNumber() const
{
	return ((4*m_CircleSteps) % 7 + 7) % 7 + 1;
}

Interval& Interval::operator+=(const Interval& inInterval)
{
	m_CircleSteps += inInterval.m_CircleSteps;
	m_HasSpelling = m_HasSpelling && inInterval.m_HasSpelling;
	m_Octaves += inInterval.m_Octaves;
	return *this;
}

Interval& Interval::operator-=(const Interval& inInterval)
{
	m_CircleSteps -= inInterval.m_CircleSteps;
	m_HasSpelling = m_HasSpelling && inInterval.m_HasSpelling;
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
	if (inMode.isMajor())
	{
		return s_MajorDegrees[((semiTonesUp() % 12) + 12) % 12];
	}
	else
	{
		return s_MinorDegrees[((semiTonesUp() % 12) + 12) % 12];
	}
}
