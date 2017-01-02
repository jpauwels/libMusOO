//============================================================================
/**
	Implementation file for ChordProsemus.h

	@author		Johan Pauwels
	@date		20101220
*/
//============================================================================

// Includes
#include <map>
#include <stdexcept>
#include "MusOO/ChordProsemus.h"
#include "MusOO/ChromaLetter.h"
#include "MusOO/ChordTypeProsemus.h"

using std::map;
using std::pair;
using std::string;
using namespace MusOO;

ChordProsemus::ChordProsemus()
{
}

ChordProsemus::ChordProsemus(const std::string& inChordString)
{
	//find root
	size_t theRootIndex = inChordString.find_first_not_of("ABCDEFG#b");
	m_Root = ChromaLetter(inChordString.substr(0,theRootIndex));
	if (theRootIndex == string::npos)
	{
		m_Type = ChordType::major();
	}
	else
	{
		m_Type = ChordTypeProsemus(inChordString.substr(theRootIndex));
	}
}

ChordProsemus::ChordProsemus(const Chord& inChord)
: Chord(inChord)
{
}

ChordProsemus::~ChordProsemus()
{
}

const std::string ChordProsemus::str() const
{
	return ChromaLetter(m_Root).str() + ChordTypeProsemus(m_Type).str();
}
