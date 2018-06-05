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
using std::pair;
using std::invalid_argument;
using std::istringstream;
using std::ostringstream;
using std::min;
using std::set;
using namespace MusOO;

ChordChordino::ChordChordino()
{
}

ChordChordino::ChordChordino(std::string inChordString)
{
	if (!inChordString.compare(0,1,"S"))
	{
		// Silence
		*this = silence<ChordChordino>();
	}
	else if (!inChordString.compare(0,1,"N"))
	{
		// No-chord
		*this = none<ChordChordino>();
	}
	else
	{
		//find colon which separates root and type
		size_t theTypeStart = inChordString.find_first_not_of("ABCDEFGb#");
		size_t theSlash = inChordString.find("/");
		m_Root = ChromaLetter(inChordString.substr(0,theTypeStart));
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
			m_Type = ChordTypeQMUL(inChordString.substr(theTypeStart));
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
				m_Type = ChordTypeQMUL("maj"+inChordString.substr(theSlash));
			}
		}
	}
}

ChordChordino::ChordChordino(const ChordAbstract& inChord)
: ChordAbstract(inChord)
{
}

const std::unique_ptr<ChordAbstract> ChordChordino::create(const Chroma& inRoot, const ChordType& inChordType)
{
    return std::unique_ptr<ChordAbstract>(new ChordChordino(inRoot, inChordType));
}

ChordChordino::~ChordChordino()
{
}

const std::string ChordChordino::str() const
{
	string theChordString = ChromaLetter(m_Root).str();
	if (m_Type != ChordType::none() && m_Type != ChordType::major())
	{
		theChordString += ChordTypeQMUL(m_Type).str();
	}
	return theChordString;
}

std::ostream& MusOO::operator<<(std::ostream& inOutputStream, const ChordChordino& inChord)
{
	inOutputStream << inChord.str();
	return inOutputStream;
}

std::istream& MusOO::operator>>(std::istream& inInputStream, ChordChordino& inChord)
{
	string theChordString;
	inInputStream >> theChordString;
	inChord = ChordChordino(theChordString);
	return inInputStream;
}
