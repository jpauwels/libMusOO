//============================================================================
/**
 Implementation file for ChordQuaero.h
 
 @author		Johan Pauwels
 @date		20101220
 */
//============================================================================

// Includes
#include "MusOO/ChordQuaero.h"
#include "MusOO/ChromaLetter.h"
#include "MusOO/ChromaSolfege.h"
#include "MusOO/ChordTypeQuaero.h"
#include <map>
#include <stdexcept>
#include <algorithm>

using std::map;
using std::string;
using std::min;
using std::set;
using namespace MusOO;

ChordQuaero::ChordQuaero(const std::string& inChordName)
{
    if (inChordName == "I ")
    {
        *this = ChordQuaero::undefined();
        return;
    }
    else
    {
        m_Root = ChromaLetter(trimRight(inChordName.substr(0,2)));
        size_t theTypeEndPosition = inChordName.substr(2).find_first_of(" ");
        m_Type = ChordTypeQuaero(inChordName.substr(2,theTypeEndPosition));
        size_t theSlashPosition = inChordName.substr(2).find_first_of("/");
        for (size_t theModBeginPosition = theTypeEndPosition; theModBeginPosition < min(theSlashPosition-1,inChordName.size()-2); theModBeginPosition+=6)
        {
            if (inChordName[theModBeginPosition+3] == '+')
            {
                addChroma(ChromaSolfege(trimRight(inChordName.substr(theModBeginPosition+5, 3))));
            }
            else if (inChordName[theModBeginPosition+3] == '-')
            {
                deleteChroma(ChromaSolfege(trimRight(inChordName.substr(theModBeginPosition+5, 3))));
            }
            else
            {
                throw std::invalid_argument("Malformed Quaero chord '" + inChordName + "'");
            }
        }
        if (theSlashPosition != string::npos)
        {
            addBass(ChromaSolfege(trimRight(inChordName.substr(theSlashPosition+4))));
        }
    }
}

const std::string ChordQuaero::str() const
{
	return ChromaLetter(m_Root).str() + ChordTypeQuaero(m_Type).str(m_Root);
}

const std::string ChordQuaero::trimRight(const std::string& inString)
{
	const size_t theEndIdx = inString.find_last_not_of(" ");
    return inString.substr(0, theEndIdx+1);
}
