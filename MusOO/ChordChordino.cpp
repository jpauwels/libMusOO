//============================================================================
/**
Implementation file for ChordChordino.h

@author		Johan Pauwels
@date		20090119
*/
//============================================================================

// Includes
#include <stdexcept>
#include <algorithm>
#include <sstream>
#include "MusOO/ChordChordino.h"
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

ChordChordino::ChordChordino(std::string inChordString)
{
	if (!inChordString.compare(0,1,"S"))
	{
		// Silence
		*this = ChordChordino::silence();
	}
	else if (!inChordString.compare(0,1,"N"))
	{
		// No-chord
		*this = ChordChordino::none();
	}
	else
	{
		//find colon which separates root and type
		size_t theTypeStart = inChordString.find_first_not_of("ABCDEFGb#");
		size_t theSlash = inChordString.find("/");
		this->m_Root = ChromaLetter(inChordString.substr(0,theTypeStart));
		//replace bass note name by circle steps
		if (theSlash != string::npos)
		{
			ostringstream theDistanceStream;
			theDistanceStream << SimpleInterval(m_Root, ChromaLetter(inChordString.substr(theSlash+1,1))).circleStepsCW();
			inChordString.replace(theSlash+1,string::npos,theDistanceStream.str());
		}
		if (theTypeStart != string::npos && theSlash == string::npos)
		{
			//explicit type, optional slash
			this->m_Type = ChordTypeQMUL(inChordString.substr(theTypeStart));
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
				this->m_Type = ChordTypeQMUL("maj"+inChordString.substr(theSlash));
			}
		}
	}
}

const std::string ChordChordino::str() const
{
	string theChordString = ChromaLetter(m_Root).str();
	if (this->m_Type != ChordTypeQMUL::none() && m_Type != ChordTypeQMUL::major())
	{
		theChordString += m_Type.str();
	}
	return theChordString;
}
