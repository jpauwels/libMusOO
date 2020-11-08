//============================================================================
/**
Implementation file for ChordQMUL.h

@author		Johan Pauwels
@date		20090119
*/
//============================================================================

// Includes
#include <stdexcept>
#include <algorithm>
#include <sstream>
#include "MusOO/ChordQMUL.h"
#include "MusOO/ChromaLetter.h"
#include "MusOO/ChordTypeQMUL.h"

using std::string;
using std::vector;
using std::map;
using std::invalid_argument;
using std::istringstream;
using std::ostringstream;
using std::min;
using std::set;
using namespace MusOO;

ChordQMUL::ChordQMUL(const std::string& inChordString)
{
	if (!inChordString.compare(0,1,"S"))
	{
		// Silence
		*this = ChordQMUL::silence();
	}
	else if (!inChordString.compare(0,1,"N"))
	{
		// No-chord
		*this = ChordQMUL::none();
	}
	else if (inChordString == "X")
	{
		// Undefined
		*this = ChordQMUL::undefined();
	}
	else
	{
		//find colon which separates root and type
		size_t theColon = inChordString.find(":");
		size_t theSlash = inChordString.find("/");
		this->m_Root = ChromaLetter(inChordString.substr(0,min(theColon, theSlash)));
		
		if (theColon != string::npos)
		{
			//explicit type, optional slash
			this->m_Type = ChordTypeQMUL(inChordString.substr(theColon+1));
		}
		else
		{
			if (theSlash == string::npos)
			{
				//no explicit type, no slash
				this->m_Type = ChordTypeQMUL::major();
			}
			else
			{
				//no explicit type, with slash
				this->m_Type = ChordTypeQMUL(inChordString.substr(theSlash));
			}
		}
	}
}

const std::string ChordQMUL::str() const
{
	string theChordString = ChromaLetter(this->m_Root).str();
	if (this->m_Type != ChordTypeQMUL::none())
	{
		theChordString += ":" + m_Type.str();
	}
	return theChordString;
}
