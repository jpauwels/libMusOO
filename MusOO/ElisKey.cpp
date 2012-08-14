//============================================================================
/**
	Implementation file for ElisKey.h
	
	@author		Johan Pauwels
	@date		20100330
*/
//============================================================================

// Includes
#include <string>
	using std::string;
#include <sstream>
	using std::istringstream;
	using std::stringbuf;
#include <stdexcept>
	using std::invalid_argument;
#include "ElisKey.h"

ElisKey::ElisKey()
{
}

ElisKey::ElisKey(const std::string& inKeyString)
{
	istringstream theStringStream(inKeyString);
	string theString;
	theStringStream >> theString;
	m_Tonic = Chroma(theString);
	theStringStream >> theString;
	m_Mode = ElisMode(theString);
}

ElisKey::ElisKey(const Key& inKey)
{
	m_Tonic = inKey.tonic();
	m_Mode = inKey.mode();
}

ElisKey::~ElisKey()
{
}

const std::string ElisKey::str() const
{
	return m_Tonic.str() + "\t" + ElisMode(m_Mode).str();
}

ElisMode::ElisMode() 
{
}

ElisMode::ElisMode(const std::string& inString)
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

ElisMode::ElisMode(const Mode& inMode)
: Mode(inMode)
{
}

const std::string ElisMode::str() const
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

std::ostream& operator<<(std::ostream& inOutputStream, const ElisKey& inKey)
{
	inOutputStream << inKey.str();
	return inOutputStream;
}

std::ostream& operator<<(std::ostream& inOutputStream, const ElisMode& inMode)
{
	inOutputStream << inMode.str();
	return inOutputStream;
}
