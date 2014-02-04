//============================================================================
/**
	Implementation file for KeyQM.h
	
	@author		Johan Pauwels
	@date		20100330
*/
//============================================================================

// Includes
#include <sstream>
#include <stdexcept>
#include "MusOO/KeyQM.h"

using std::string;
using std::istringstream;
using std::ostringstream;
using std::invalid_argument;
using namespace MusOO;

KeyQM::KeyQM()
{
}

KeyQM::KeyQM(std::string inKeyString)
{
	if (!inKeyString.compare(0,1,"S") || !inKeyString.compare("N"))
	{
		// Silence
		*this = Key::silence();
	}
	else
	{
		if (!inKeyString.compare(0, 3, "Key"))
		{
            istringstream theStringStream(inKeyString.substr(3));
            theStringStream >> inKeyString;
			string theExtraString;
            std::getline(theStringStream, theExtraString);
            inKeyString += theExtraString;
		}
		if (!inKeyString.compare("N"))
		{
			*this = Key::silence();
		}
		else
		{
			//find colon which separates tonic and mode
			size_t theColon = inKeyString.find(":");
			m_Tonic = Chroma(inKeyString.substr(0,theColon));
			if (theColon == string::npos)
			{
				m_Mode = Mode::major();
			}
			else
			{
				m_Mode = ModeQM(inKeyString.substr(theColon+1));
			}
		}
	}
}

KeyQM::KeyQM(const Key& inKey)
: Key(inKey.tonic(), ModeQM(inKey.mode()))
{
}

KeyQM::~KeyQM()
{
	// Nothing to do...
}

const std::string KeyQM::str() const
{
	string theKeyString;
	if (*this == Key::silence())
	{
		theKeyString = "Silence";
	}
	else
	{
		theKeyString = "Key " + m_Tonic.str();
		if (m_Mode != Mode::major())
		{
			theKeyString += ":" + ModeQM(m_Mode).str();
		}
	}
	return theKeyString;
}

ModeQM::ModeQM()
{
}

ModeQM::ModeQM(const Mode& inMode)
: Mode(inMode)
{
}

ModeQM::ModeQM(const std::string& inString)
{
	if (!inString.compare("") || !inString.compare("major"))
	{
		*this = major();
	}
	else if (!inString.compare("minor") || !inString.compare("minor-harmonic"))
	{
		*this = minorHarmonic();
	}
	else if (!inString.compare("dorian"))
	{
		*this = dorian();
	}
	else if (!inString.compare("mixolydian"))
	{
		*this = mixolydian();
	}
	else if (!inString.compare("aeolian"))
	{
		*this = aeolian();
	}
	else if (!inString.compare("modal"))
	{
		*this = modal();
	}
	else
	{
		throw invalid_argument("Unknown QM mode name " + inString);
	}
}

const std::string ModeQM::str() const
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
		ostringstream theModeStream;
        theModeStream << "(";
        if (!m_IntervalList.empty())
        {
            theModeStream << m_IntervalList.begin()->majorDegree();
            for (std::set<Interval>::const_iterator i = ++m_IntervalList.begin(); i != m_IntervalList.end(); ++i)
            {
                theModeStream << ",";
                theModeStream << i->majorDegree();
            }
        }
        theModeStream << ")";
        return theModeStream.str();
	}
}

std::ostream& MusOO::operator<<(std::ostream& inOutputStream, const KeyQM& inKey)
{
	inOutputStream << inKey.str();
	return inOutputStream;
}

std::ostream& MusOO::operator<<(std::ostream& inOutputStream, const ModeQM& inMode)
{
	inOutputStream << inMode.str();
	return inOutputStream;
}
