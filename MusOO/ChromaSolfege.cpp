
#include <stdexcept>
#include <cmath>
#include "MusOO/ChromaSolfege.h"

using std::map;
using std::string;
using std::pair;
using namespace MusOO;

const string ChromaSolfege::s_linePositionToString[] = {"fa", "do", "sol", "re", "la", "mi", "si"};

static const pair<string,ptrdiff_t> stringPositionMap[] =
{
	pair<string,ptrdiff_t>("la",5),
	pair<string,ptrdiff_t>("si",7),
	pair<string,ptrdiff_t>("ti",7),
	pair<string,ptrdiff_t>("do",2),
	pair<string,ptrdiff_t>("re",4),
	pair<string,ptrdiff_t>("mi",6),
	pair<string,ptrdiff_t>("fa",1),
	pair<string,ptrdiff_t>("sol",3),
	pair<string,ptrdiff_t>("so",3)
};

const map<string,ptrdiff_t> ChromaSolfege::s_stringToLinePositionMap(stringPositionMap, stringPositionMap+9);

ChromaSolfege::ChromaSolfege()
{
}

ChromaSolfege::ChromaSolfege(const std::string& inName)
{
	const size_t theModPosition = inName.find_first_of("#b");
	const map<string,ptrdiff_t>::const_iterator theMapPos = s_stringToLinePositionMap.find(inName.substr(0,theModPosition));
	if (theMapPos != s_stringToLinePositionMap.end())
	{
		m_LinePosition = theMapPos->second;
	}
	else
	{
		throw std::invalid_argument("Unknown solfege chroma " + inName);
	}
	if (theModPosition != string::npos)
	{
		m_LinePosition += this->stringModifierToCircleSteps(inName.substr(theModPosition));
	}
	m_HasSpelling = true;
}

ChromaSolfege::ChromaSolfege(const Chroma& inReference, const Interval& inInterval)
: Chroma(inReference, inInterval)
{
}

ChromaSolfege::ChromaSolfege(const Chroma& inChroma)
: Chroma(inChroma)
{
}

ChromaSolfege::~ChromaSolfege()
{
}

const std::string ChromaSolfege::str() const
{
	if (*this == Chroma::silence())
	{
		return "S";
	}
	else if (*this == Chroma::none())
	{
		return "N";
	}
	else if (*this == Chroma::undefined())
	{
		return "U";
	}
	else
	{
		string theBaseString = s_linePositionToString[((m_LinePosition-1) % 7 + 7) % 7];
		ptrdiff_t theNumOfModifiers = floor((m_LinePosition-1.) / 7);
		if (theNumOfModifiers > 0)
		{
			return theBaseString + string(theNumOfModifiers, '#');
		}
		else
		{
			return theBaseString + string(-theNumOfModifiers, 'b');
		}
	}
}
