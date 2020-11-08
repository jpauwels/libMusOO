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
#include "MusOO/ModeQMUL.h"
#include <sstream>
#include <stdexcept>
#include <algorithm>

using std::string;
using std::ostringstream;
using namespace MusOO;


RelativeChordQMUL::RelativeChordQMUL(const std::string& inString, const ModeQMUL& inMode)
{
	if (!inString.compare(0,1,"S"))
	{
		// Silence
		*this = RelativeChordQMUL::silence();
	}
	else if (!inString.compare(0,1,"N"))
	{
		// No-chord
		*this = RelativeChordQMUL::none();
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
				theType = ChordTypeQMUL::major();
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

const std::string RelativeChordQMUL::asDegree(const ModeQMUL& inMode) const
{
    if (*this == RelativeChordQMUL::unknown())
    {
        return "X";
    }
    else if (*this == RelativeChordQMUL::none())
    {
        return "N";
    }
    else if (*this == RelativeChordQMUL::silence())
    {
        return "S";
    }
    else
    {
        return m_RootInterval.asDegree(inMode) + ":" + ChordTypeQMUL(m_Type).str();
    }
}

const std::string RelativeChordQMUL::str() const
 {
     string theRelChordString = std::to_string(m_RootInterval.diatonicNumber());//IntervalRoman(m_RootInterval).str();
     if (m_Type != ChordTypeQMUL::none())
     {
         theRelChordString += ":" + ChordTypeQMUL(m_Type).str();
     }
     return theRelChordString;
 }

