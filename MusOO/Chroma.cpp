//============================================================================
/**
	Implementation file for Chroma.h

	@author		Johan Pauwels
	@date		20100322
*/
//============================================================================

// Includes
#include <string>
	using std::string;
#include <map>
	using std::map;
	using std::pair;
#include <stdexcept>
	using std::invalid_argument;
#include <limits>
	using std::numeric_limits;
#include <ostream>
#include <vector>
	using std::vector;
#include "MusOO/Chroma.h"
#include "MusOO/Interval.h"
using namespace MusOO;

const Chroma& Chroma::silence()
{
	static const Chroma silence(numeric_limits<int>::max(), true);
	return silence;
}
const Chroma& Chroma::none()
{
	static const Chroma noChroma(numeric_limits<int>::max()-1, true);
	return noChroma;
}
const Chroma& Chroma::undefined()
{
	static const Chroma undefined(numeric_limits<int>::max()-2, true);
	return undefined;
}
Chroma Chroma::Fb()
{
	static const Chroma Fb(-6, true);
	return Fb;
}
Chroma Chroma::Cb()
{
	static const Chroma Cb(-5, true);
	return Cb;
}
Chroma Chroma::Gb()
{
	static const Chroma Gb(-4, true);
	return Gb;
}
Chroma Chroma::Db()
{
	static const Chroma Db(-3, true);
	return Db;
}
Chroma Chroma::Ab()
{
	static const Chroma Ab(-2, true);
	return Ab;
}
Chroma Chroma::Eb()
{
	static const Chroma Eb(-1, true);
	return Eb;
}
Chroma Chroma::Bb()
{
	static const Chroma Bb(0, true);
	return Bb;
}
Chroma Chroma::F()
{
	static const Chroma F(1, true);
	return F;
}
Chroma Chroma::C()
{
	static const Chroma C(2, true);
	return C;
}
Chroma Chroma::G()
{
	static const Chroma G(3, true);
	return G;
}
Chroma Chroma::D()
{
	static const Chroma D(4, true);
	return D;
}
Chroma Chroma::A()
{
	static const Chroma A(5, true);
	return A;
}
Chroma Chroma::E()
{
	static const Chroma E(6, true);
	return E;
}
Chroma Chroma::B()
{
	static const Chroma B(7, true);
	return B;
}
Chroma Chroma::Fs()
{
	static const Chroma Fs(8, true);
	return Fs;
}
Chroma Chroma::Cs()
{
	static const Chroma Cs(9, true);
	return Cs;
}
Chroma Chroma::Gs()
{
	static const Chroma Gs(10, true);
	return Gs;
}
Chroma Chroma::Ds()
{
	static const Chroma Ds(11, true);
	return Ds;
}
Chroma Chroma::As()
{
	static const Chroma As(12, true);
	return As;
}
Chroma Chroma::Es()
{
	static const Chroma Es(13, true);
	return Es;
}
Chroma Chroma::Bs()
{
	static const Chroma Bs(14, true);
	return Bs;
}
const std::vector<Chroma>& Chroma::circleOfFifths(const Chroma& inStartChroma /* = Chroma::A*/, const bool inHasSpelling /*= false*/)
{
	static vector<Chroma> theCircleOfFifths(12);
	for(int i = 0; i < 12; ++i)
	{
		theCircleOfFifths[i] = Chroma((inStartChroma.m_LinePosition+i)%12, inHasSpelling);
	}
	return theCircleOfFifths;
}

static const pair<char,int> theNameToCirclePosition[] = {pair<char,int>('A',5), pair<char,int>('B',7), 
	pair<char,int>('C',2), pair<char,int>('D',4), pair<char,int>('E',6), pair<char,int>('F',1), 
	pair<char,int>('G',3), pair<char,int>('N',numeric_limits<int>::max()-1)};
const map<char,int> Chroma::s_NameToCirclePosition(theNameToCirclePosition, theNameToCirclePosition+8);

static const pair<int,char> theCirclePositionToName[] = {pair<int,char>(1,'F'), pair<int,char>(2,'C'), 
	pair<int,char>(3,'G'), pair<int,char>(4,'D'), pair<int,char>(5,'A'), pair<int,char>(6,'E'), 
	pair<int,char>(7,'B')};
const map<int,char> Chroma::s_CirclePositionToName(theCirclePositionToName, theCirclePositionToName+7);

Chroma::Chroma() 
: m_LinePosition(Chroma::undefined().m_LinePosition), m_HasSpelling(true)
{
}

Chroma::Chroma(const int inCirclePosition, const bool inHasSpelling)
: m_LinePosition(inCirclePosition), m_HasSpelling(inHasSpelling)
{
}

Chroma::Chroma(const std::string& inName, const bool inHasSpelling /*= true*/)
: m_HasSpelling(inHasSpelling)
{
	if (inName.empty())
	{
		throw invalid_argument("Empty note name");
	}
	else if (inName.find_first_not_of("s#bABCDEFGN") != string::npos)
	{
		throw invalid_argument("Illegal input \"" + inName + "\" for a chroma name");
	}
	//convert base note
	m_LinePosition = s_NameToCirclePosition.find(inName[0])->second;
	//convert modifier
	m_LinePosition += stringModifierToCircleSteps(inName.substr(1));
}

Chroma::Chroma(const Chroma& inReference, const Interval& inInterval)
: m_LinePosition(inReference.m_LinePosition + inInterval.m_LinePosition),
  m_HasSpelling(inReference.m_HasSpelling && inInterval.hasSpelling())
{
    if (!inInterval.isTrueInterval())
    {
        m_LinePosition = inInterval.m_LinePosition;
        m_HasSpelling = true;
    }
}

Chroma::~Chroma()
{
	// Nothing to do...
}

const int Chroma::stringModifierToCircleSteps(const std::string& inStringModifier)
{
	int theCircleModifier = 0;
	for (size_t i = 0; i < inStringModifier.length(); i++)
	{
		//if the next character is a flat, move 7 positions to the left
		if (!inStringModifier.substr(i,1).compare("b"))
		{
			theCircleModifier -= 7;
		}
		//if the next character is a sharp or an "s", move 7 positions to the right
		else if (!inStringModifier.substr(i,1).compare("#") || !inStringModifier.substr(i,1).compare("s"))
		{
			theCircleModifier += 7;
		}
		else
		{
			throw invalid_argument("Unknown modifier: " + inStringModifier.substr(i,1));
		}
	}
	return theCircleModifier;
}

const std::string Chroma::str() const
{
	if (*this == silence())
	{
		return "S";
	}
	else if (*this == none())
	{
		return "N";
	}
	else if (*this == undefined())
	{
		return "U";
	}
	//limit the position on the circle to the allowed basic range by adding modifiers
	int theRangeLimitedCirclePosition = m_LinePosition;
	string theModifierString = "";
	while (theRangeLimitedCirclePosition < s_CirclePositionToName.begin()->first)
	{
		theModifierString.append("b");
		theRangeLimitedCirclePosition += 7;
	}
	while (s_CirclePositionToName.lower_bound(theRangeLimitedCirclePosition) == s_CirclePositionToName.end())
	{
		theModifierString.append("#");
		theRangeLimitedCirclePosition -= 7;
	}
	//convert the range-limited circle position to the basic note string
	return s_CirclePositionToName.find(theRangeLimitedCirclePosition)->second + theModifierString;
}

const bool Chroma::hasSpelling() const
{
	return m_HasSpelling;
}

Chroma Chroma::withoutSpelling() const
{
	return Chroma(*this).ignoreSpelling();
}

Chroma& Chroma::ignoreSpelling()
{
    if (isTrueChroma())
    {
        m_HasSpelling = false;
    }
	return *this;
}

const bool Chroma::operator==(const Chroma& inChroma) const
{
	if (!isTrueChroma() || !inChroma.isTrueChroma() || (m_HasSpelling && inChroma.m_HasSpelling))
	{
		return m_LinePosition == inChroma.m_LinePosition;
	}
	else
	{
        return ((m_LinePosition % 12) + 12) % 12 == ((inChroma.m_LinePosition % 12) + 12) % 12;
	}
}

const bool Chroma::operator!=(const Chroma& inChroma) const
{
	return !(*this == inChroma);
}

Chroma& Chroma::operator+=(const Interval& inInterval)
{
	m_LinePosition += inInterval.m_LinePosition;
	m_HasSpelling = m_HasSpelling && inInterval.m_LinePosition;
	return *this;
}

Chroma& Chroma::operator-=(const Interval& inInterval)
{
	m_LinePosition += inInterval.m_LinePosition;
	m_HasSpelling = m_HasSpelling && inInterval.m_LinePosition;
	return *this;
}

bool Chroma::operator<(const Chroma& inChroma) const
{
	if (!isTrueChroma() || !inChroma.isTrueChroma())
	{
		return m_LinePosition < inChroma.m_LinePosition;
	}
	else
	{
		if (((m_LinePosition % 12) + 12) % 12 != ((inChroma.m_LinePosition % 12) + 12) % 12)
		{
			return ((m_LinePosition % 12) + 12) % 12 < ((inChroma.m_LinePosition % 12) + 12) % 12;
		}
		else
		{
			if (m_HasSpelling && inChroma.m_HasSpelling)
			{
				return m_LinePosition < inChroma.m_LinePosition;
			}
			else
			{
				return false;
			}
		}
	}
}

const bool Chroma::isTrueChroma() const
{
	return m_LinePosition < numeric_limits<int>::max()-2;
}

std::ostream& MusOO::operator<<(std::ostream& inOutputStream, const Chroma& inChroma)
{
	inOutputStream << inChroma.str();
	return inOutputStream;
}
