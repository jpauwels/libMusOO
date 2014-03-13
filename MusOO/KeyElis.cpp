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
    string theKeyString = m_Tonic.str();
	if (isTrueKey())
	{
		theKeyString += "\t" + ModeElis(m_Mode).str();
	}
	return theKeyString;
}

ModeElis::ModeElis() 
{
}

ModeElis::ModeElis(const std::string& inString)
{
	if (inString == "major")
	{
		*this = major();
	}
	else if (inString == "minor" || inString == "minor composed")
	{
		*this = minorComposed();
	}
	else if (inString == "minor natural")
	{
		*this = minorNatural();
	}
	else if (inString == "minor harmonic")
	{
		*this = minorHarmonic();
	}
	else if (inString == "minor melodic")
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
	else if (*this == minorHarmonic())
	{
		return "minor harmonic";
	}
	else if (*this == minorMelodic())
	{
		return "minor melodic";
	}
	else if (*this == minorComposed())
	{
		return "minor";
	}
	else if (*this == dorian())
	{
		return "dorian";
	}
	else if (*this == mixolydian())
	{
		return "mixolydian";
	}
	else if (*this == aeolian())
	{
		return "aeolian";
	}
	else if (*this == modal())
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
