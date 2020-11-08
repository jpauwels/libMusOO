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

using std::map;
using std::istringstream;
using std::ostringstream;
using std::invalid_argument;
using std::string;
using namespace MusOO;

KeyQuaero::KeyQuaero(const std::string& inKeyString)
{
    if (inKeyString == "I ")
    {
        *this = KeyQuaero::undefined();
    }
    else if (inKeyString == "M ")
    {
        *this = KeyQuaero::none();
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

const std::string KeyQuaero::str() const
{
	if (*this == KeyQuaero::undefined())
	{
		return "I ";
	}
    else if (*this == KeyQuaero::none())
	{
		return "M ";
	}
	else
	{
        return ChromaLetter(m_Tonic).str() + ModeQuaero(m_Mode).str(m_Tonic);
	}
}
