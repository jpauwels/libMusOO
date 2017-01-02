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

KeyElis::KeyElis()
{
}

KeyElis::KeyElis(const std::string& inKeyString)
{
	istringstream theStringStream(inKeyString);
	string theString;
	theStringStream >> theString;
	m_Tonic = ChromaLetter(theString);
	theStringStream >> theString;
	m_Mode = ModeElis(theString);
}

KeyElis::KeyElis(const Key& inKey)
{
	m_Tonic = inKey.tonic();
	m_Mode = inKey.mode();
}

KeyElis::~KeyElis()
{
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

std::ostream& MusOO::operator<<(std::ostream& inOutputStream, const KeyElis& inKey)
{
	inOutputStream << inKey.str();
	return inOutputStream;
}
