//============================================================================
/**
	Implementation file for ModeElis.h
	
	@author		Johan Pauwels
	@date		20100330
*/
//============================================================================

// Includes
#include <sstream>
#include <stdexcept>
#include "MusOO/ModeElis.h"

using std::istringstream;
using std::stringbuf;
using std::string;
using std::invalid_argument;
using namespace MusOO;

ModeElis::ModeElis(const std::string& inString)
{
	if (inString == "major")
	{
		*this = major();
	}
	else if (inString == "minor" || inString == "minor general")
	{
		*this = minorGeneral();
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
		throw invalid_argument("Unknown Elis mode name '" + inString + "'");
	}
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
	else if (*this == minorGeneral())
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
		return ModeElis::str();
	}
}
