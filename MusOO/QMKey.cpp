//============================================================================
/**
	Implementation file for QMKey.h
	
	@author		Johan Pauwels
	@date		20100330
*/
//============================================================================

// Includes
#include <string>
	using std::string;
#include <sstream>
	using std::istringstream;
#include <stdexcept>
	using std::invalid_argument;
#include "QMKey.h"

QMKey::QMKey()
{
}

QMKey::QMKey(const std::string& inKeyString)
{
	if (!inKeyString.compare(0,1,"S") || !inKeyString.compare("N"))
	{
		// Silence
		*this = Key::silence();
	}
	else
	{
		istringstream theStringStream(inKeyString);
		string theString;
		theStringStream >> theString;
		if (!theString.compare("Key"))
		{
			theStringStream >> theString;
		}
		if (!theString.compare("N"))
		{
			*this = Key::silence();
		}
		else
		{
			//find colon which separates tonic and mode
			size_t theColon = theString.find(":");
			m_Tonic = Chroma(theString.substr(0,theColon));
			if (theColon == string::npos)
			{
				m_Mode = Mode::major();
			}
			else
			{
				m_Mode = QMMode(theString.substr(theColon+1));
			}
		}
	}
}

QMKey::QMKey(const Key& inKey)
: Key(inKey.tonic(), QMMode(inKey.mode()))
{
}

QMKey::~QMKey()
{
	// Nothing to do...
}

const std::string QMKey::str() const
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
			theKeyString += ":" + QMMode(m_Mode).str();
		}
	}
	return theKeyString;
}

QMMode::QMMode()
{
}

QMMode::QMMode(const Mode& inMode)
: Mode(inMode)
{
}

QMMode::QMMode(const std::string& inString)
{
	if (!inString.compare("") || !inString.compare("major"))
	{
		*this = major();
	}
	else if (!inString.compare("minor"))
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

const std::string QMMode::str() const
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

std::ostream& operator<<(std::ostream& inOutputStream, const QMKey& inKey)
{
	inOutputStream << inKey.str();
	return inOutputStream;
}

std::ostream& operator<<(std::ostream& inOutputStream, const QMMode& inMode)
{
	inOutputStream << inMode.str();
	return inOutputStream;
}
