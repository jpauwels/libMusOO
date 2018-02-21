//============================================================================
/**
	Implementation file for ModeQMUL.h
	
	@author		Johan Pauwels
	@date		20100330
*/
//============================================================================

// Includes
#include <sstream>
#include <stdexcept>
#include "MusOO/ModeQMUL.h"

using std::string;
using std::istringstream;
using std::ostringstream;
using std::invalid_argument;
using namespace MusOO;

ModeQMUL::ModeQMUL()
{
}

ModeQMUL::ModeQMUL(const Mode& inMode)
: Mode(inMode)
{
}

ModeQMUL::ModeQMUL(const std::string& inString)
{
	if (inString == "" || inString == "major")
	{
		*this = major();
	}
	else if (inString == "minor-natural")
	{
		*this = minorNatural();
	}
	else if (inString == "minor-harmonic")
	{
		*this = minorHarmonic();
	}
	else if (inString == "minor-melodic")
	{
		*this = minorMelodic();
	}
	else if (inString == "minor" || inString == "minor-general")
	{
		*this = minorGeneral();
	}
	else if (inString == "dorian")
	{
		*this = dorian();
	}
	else if (inString == "mixolydian")
	{
		*this = mixolydian();
	}
	else if (inString == "aeolian")
	{
		*this = aeolian();
	}
	else if (inString == "modal")
	{
		*this = modal();
	}
	else
	{
		throw invalid_argument("Unknown QMUL mode name '" + inString + "'");
	}
}

const std::string ModeQMUL::str() const
{
	if (*this == major())
	{
		return "major";
	}
	else if (*this == minorHarmonic())
	{
		return "minor-harmonic";
	}
	else if (*this == minorMelodic())
	{
		return "minor-melodic";
	}
	else if (*this == minorGeneral())
	{
		return "minor-general";
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
		ostringstream theModeStream;
        theModeStream << "(";
        if (!m_set.empty())
        {
            theModeStream << m_set.begin()->majorDegreeString();
            for (std::set<SimpleInterval>::const_iterator i = ++m_set.begin(); i != m_set.end(); ++i)
            {
                theModeStream << ",";
                theModeStream << i->majorDegreeString();
            }
        }
        theModeStream << ")";
        return theModeStream.str();
	}
}

std::ostream& MusOO::operator<<(std::ostream& inOutputStream, const ModeQMUL& inMode)
{
	inOutputStream << inMode.str();
	return inOutputStream;
}
