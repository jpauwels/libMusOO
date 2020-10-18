//============================================================================
/**
 Implementation file for KeyQuaero.h
 
 @author	Johan Pauwels
 @date		20130417
 */
//============================================================================

// Includes
#include <sstream>
#include <stdexcept>
#include "MusOO/ModeQuaero.h"
#include "MusOO/ChromaLetter.h"
#include "MusOO/ChromaSolfege.h"
#include "MusOO/ChordQuaero.h"
#include "MusOO/KeyQuaero.h"

using std::pair;
using std::map;
using std::istringstream;
using std::ostringstream;
using std::invalid_argument;
using std::string;
using namespace MusOO;

KeyQuaero::KeyQuaero()
{
}

KeyQuaero::KeyQuaero(const std::string& inKeyString)
{
    if (inKeyString == "I ")
    {
        *this = Key::undefined();
    }
    else if (inKeyString == "M ")
    {
        *this = Key::none();
    }
    else
    {
        m_Tonic = ChromaLetter(ChordQuaero::trimRight(inKeyString.substr(0,2)));
        size_t theModeEndPosition = inKeyString.substr(2).find_first_of(" ");
        m_Mode = ModeQuaero(inKeyString.substr(2,theModeEndPosition));
        for (size_t theModBeginPosition = theModeEndPosition; theModBeginPosition < inKeyString.size()-2; theModBeginPosition+=6)
        {
            if (inKeyString[theModBeginPosition+3] == '+')
            {
                addChroma(ChromaSolfege(ChordQuaero::trimRight(inKeyString.substr(theModBeginPosition+5, 3))));
            }
            else if (inKeyString[theModBeginPosition+3] == '-')
            {
                deleteChroma(ChromaSolfege(ChordQuaero::trimRight(inKeyString.substr(theModBeginPosition+5, 3))));
            }
            else
            {
                throw std::invalid_argument("Malformed Quaero key '" + inKeyString + "'");
            }
        }
    }
}

KeyQuaero::KeyQuaero(const Key& inKey)
: Key(inKey.tonic(), ModeQuaero(inKey.mode()))
{
}

KeyQuaero::KeyQuaero(const Chroma& inTonic, const Mode& inMode)
: Key(inTonic, ModeQuaero(inMode))
{
}

KeyQuaero::~KeyQuaero()
{
	// Nothing to do...
}

const std::string KeyQuaero::str() const
{
	if (*this == Key::undefined())
	{
		return "I ";
	}
    else if (*this == Key::none())
	{
		return "M ";
	}
	else
	{
        return ChromaLetter(m_Tonic).str() + ModeQuaero(m_Mode).str(m_Tonic);
	}
}

std::ostream& MusOO::operator<<(std::ostream& inOutputStream, const KeyQuaero& inKey)
{
	inOutputStream << inKey.str();
	return inOutputStream;
}
