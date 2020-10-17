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
using std::pair;
using std::invalid_argument;
using std::istringstream;
using std::ostringstream;
using std::min;
using std::set;
using namespace MusOO;

ChordQMUL::ChordQMUL()
{
}

ChordQMUL::ChordQMUL(const std::string& inChordString)
{
	if (!inChordString.compare(0,1,"S"))
	{
		// Silence
		*this = silence<ChordQMUL>();
	}
	else if (!inChordString.compare(0,1,"N"))
	{
		// No-chord
		*this = none<ChordQMUL>();
	}
	else if (inChordString == "X")
	{
		// Undefined
		*this = undefined<ChordQMUL>();
	}
	else
	{
		//find colon which separates root and type
		size_t theColon = inChordString.find(":");
		size_t theSlash = inChordString.find("/");
		m_Root = ChromaLetter(inChordString.substr(0,min(theColon, theSlash)));
		
		if (theColon != string::npos)
		{
			//explicit type, optional slash
			m_Type = ChordTypeQMUL(inChordString.substr(theColon+1));
		}
		else
		{
			if (theSlash == string::npos)
			{
				//no explicit type, no slash
				m_Type = ChordType::major();
			}
			else
			{
				//no explicit type, with slash
				m_Type = ChordTypeQMUL(inChordString.substr(theSlash));
			}
		}
	}
}

const std::unique_ptr<ChordAbstract> ChordQMUL::create(const Chroma& inRoot, const ChordType& inChordType)
{
    return std::unique_ptr<ChordAbstract>(new ChordQMUL(inRoot, inChordType));
}

ChordQMUL::ChordQMUL(const ChordAbstract& inChord)
: ChordAbstract(inChord)
{
}

ChordQMUL::~ChordQMUL()
{
	// Nothing to do...
}

const std::string ChordQMUL::str() const
{
	string theChordString = ChromaLetter(m_Root).str();
	if (m_Type != ChordType::none())
	{
		theChordString += ":" + ChordTypeQMUL(m_Type).str();
	}
	return theChordString;
}

std::ostream& MusOO::operator<<(std::ostream& inOutputStream, const ChordQMUL& inChord)
{
	inOutputStream << inChord.str();
	return inOutputStream;
}

std::istream& MusOO::operator>>(std::istream& inInputStream, ChordQMUL& inChord)
{
	string theChordString;
	inInputStream >> theChordString;
	inChord = ChordQMUL(theChordString);
	return inInputStream;
}
