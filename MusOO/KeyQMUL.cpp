//============================================================================
/**
	Implementation file for KeyQMUL.h
	
	@author		Johan Pauwels
	@date		20100330
*/
//============================================================================

// Includes
#include <sstream>
#include <stdexcept>
#include "MusOO/KeyQMUL.h"
#include "MusOO/ModeQMUL.h"

using std::string;
using std::istringstream;
using std::ostringstream;
using std::invalid_argument;
using namespace MusOO;

KeyQMUL::KeyQMUL()
{
}

KeyQMUL::KeyQMUL(std::string inKeyString)
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
				m_Mode = ModeQMUL(inKeyString.substr(theColon+1));
			}
		}
	}
}

KeyQMUL::KeyQMUL(const Key& inKey)
: Key(inKey.tonic(), ModeQMUL(inKey.mode()))
{
}

KeyQMUL::~KeyQMUL()
{
	// Nothing to do...
}

const std::string KeyQMUL::str() const
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
			theKeyString += ":" + ModeQMUL(m_Mode).str();
		}
	}
	return theKeyString;
}

std::ostream& MusOO::operator<<(std::ostream& inOutputStream, const KeyQMUL& inKey)
{
	inOutputStream << inKey.str();
	return inOutputStream;
}
