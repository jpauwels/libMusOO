//============================================================================
/**
	Implementation file for RelativeChordQMUL.h

	@author		Johan Pauwels
	@date		20101222
*/
//============================================================================

// Includes
#include "MusOO/RelativeChordQMUL.h"
#include "MusOO/ChordTypeQMUL.h"
#include "MusOO/Mode.h"
#include <sstream>
#include <stdexcept>
#include <algorithm>

using std::string;
using std::ostringstream;
using namespace MusOO;


RelativeChordQMUL::RelativeChordQMUL()
{
}

RelativeChordQMUL::RelativeChordQMUL(const std::string& inString, const Mode& inMode)
{
	if (!inString.compare(0,1,"S"))
	{
		// Silence
		*this = silence<RelativeChordQMUL>();
	}
	else if (!inString.compare(0,1,"N"))
	{
		// No-chord
		*this = none<RelativeChordQMUL>();
	}
	else
	{
		//find colon which separates root and type
		size_t theColon = inString.find(":");
		size_t theSlash = inString.find("/");
		string theRootDegree = inString.substr(0,std::min(theColon, theSlash));
		ChordTypeQMUL theType;

		if (theColon != string::npos)
		{
			//explicit type, optional slash
			theType = ChordTypeQMUL(inString.substr(theColon+1));
		}
		else
		{
			if (theSlash == string::npos)
			{
				//no explicit type, no slash
				theType = ChordType::major();
			}
			else
			{
				//no explicit type, with slash
				theType = ChordTypeQMUL("maj"+inString.substr(theSlash));
			}
		}
		*this = RelativeChordQMUL(theRootDegree, theType, inMode);
	}
}

RelativeChordQMUL::RelativeChordQMUL(const RelativeChordAbstract& inRelativeChord)
	: RelativeChordAbstract(inRelativeChord)
{
}

const std::string RelativeChordQMUL::asDegree(const Mode& inMode) const
{
    if (*this == unknown<RelativeChordQMUL>())
    {
        return "X";
    }
    else if (*this == none<RelativeChordQMUL>())
    {
        return "N";
    }
    else if (*this == silence<RelativeChordQMUL>())
    {
        return "S";
    }
    else
    {
        return m_RootInterval.asDegree(inMode) + ":" + ChordTypeQMUL(m_Type).str();
    }
}

/*const std::string RelativeChordQMUL::str() const
 {
	if (*this == RelativeChord::unknown())
	{
 return "X";
	}
	else if (*this == RelativeChord::none())
	{
 return "N";
	}
	else if (*this == RelativeChord::silence())
	{
 return "S";
	}
	ostringstream theStringStream;
	theStringStream << IntervalRoman(m_RootInterval).str() << ":" << ChordTypeQMUL(m_Type).str();
	return theStringStream.str();
 }*/

