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
	m_Tonic = Chroma(theString);
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
	return m_Tonic.str() + "\t" + ModeElis(m_Mode).str();
}

ModeElis::ModeElis() 
{
}

ModeElis::ModeElis(const std::string& inString)
{
	if (!inString.compare("major"))
	{
		*this = major();
	}
	else if (!inString.compare("minor"))
	{
		*this = minorHarmonic();
	}
	else if (!inString.compare("minor natural"))
	{
		*this = minorNatural();
	}
	else if (!inString.compare("minor harmonic"))
	{
		*this = minorHarmonic();
	}
	else if (!inString.compare("minor melodic"))
	{
		*this = minorMelodic();
	}
	else
	{
		throw invalid_argument("Unknown Elis mode name " + inString);
	}
}

ModeElis::ModeElis(const Mode& inMode)
: Mode(inMode)
{
}

const std::string ModeElis::str() const
{
	if (*this == major())
	{
		return "major";
	}
	else if (*this == minorMelodic() || *this == minorHarmonic())
	{
		return "minor";
	}
	if (*this == dorian())
	{
		return "dorian";
	}
	if (*this == mixolydian())
	{
		return "mixolydian";
	}
	if (*this == aeolian())
	{
		return "aeolian";
	}
	if (*this == modal())
	{
		return "modal";
	}
	else
	{
		return Mode::str();
	}
}

std::ostream& MusOO::operator<<(std::ostream& inOutputStream, const KeyElis& inKey)
{
	inOutputStream << inKey.str();
	return inOutputStream;
}

std::ostream& MusOO::operator<<(std::ostream& inOutputStream, const ModeElis& inMode)
{
	inOutputStream << inMode.str();
	return inOutputStream;
}
