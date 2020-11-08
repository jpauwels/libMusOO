//============================================================================
/**
	Implementation file for KeyElis.h
	
	@author		Johan Pauwels
	@date		20100330
*/
//============================================================================

// Includes
#include <sstream>
#include <stdexcept>
#include "MusOO/KeyElis.h"
#include "MusOO/ChromaLetter.h"
#include "MusOO/ModeElis.h"

using std::istringstream;
using std::stringbuf;
using std::string;
using std::invalid_argument;
using namespace MusOO;

KeyElis::KeyElis(const std::string& inKeyString)
{
	istringstream theStringStream(inKeyString);
	string theString;
	theStringStream >> theString;
	m_Tonic = ChromaLetter(theString);
	theStringStream >> theString;
	m_Mode = ModeElis(theString);
}

const std::string KeyElis::str() const
{
    string theKeyString = ChromaLetter(m_Tonic).str();
	if (isTrueKey())
	{
		theKeyString += "\t" + ModeElis(m_Mode).str();
	}
	return theKeyString;
}
