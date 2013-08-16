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
#include "MusOO/KeyQuaero.h"
#include "MusOO/ChromaSolfege.h"
#include "MusOO/ChordQuaero.h"

using std::pair;
using std::map;
using std::istringstream;
using std::ostringstream;
using std::invalid_argument;
using std::string;
using namespace MusOO;

//----------------------------------------------------------------------------
// KeyQuaero
//----------------------------------------------------------------------------
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
        m_Tonic = Chroma(ChordQuaero::trimRight(inKeyString.substr(0,2)));
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
                throw std::invalid_argument("Malformed Quaero key \"" + inKeyString + "\"");
            }
        }
    }
}

KeyQuaero::KeyQuaero(const Key& inKey)
: Key(inKey.tonic(), ModeQuaero(inKey.mode()))
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
        return m_Tonic.str() + ModeQuaero(m_Mode).str(m_Tonic);
	}
}

//----------------------------------------------------------------------------
// ModeQuaero
//----------------------------------------------------------------------------
static const pair<string,Mode> modeStringMap[] =
{
	pair<string,Mode>("M", Mode::major()),
	pair<string,Mode>("mix", Mode::mixolydian()),
	pair<string,Mode>("m", Mode::minorNatural()),
	pair<string,Mode>("harmo", Mode::minorHarmonic()),
	pair<string,Mode>("meloa", Mode::minorMelodic()),
	pair<string,Mode>("melod", Mode::minorNatural().addInterval(Interval::majorSixth())),
	pair<string,Mode>("dor", Mode::dorian()),
	pair<string,Mode>("blues", Mode::mixolydian().addInterval(Interval::minorThird()).addInterval(Interval::diminishedFifth())),
	pair<string,Mode>("bluesm", Mode::dorian().addInterval(Interval::diminishedFifth()))
};
const map<string,Mode> ModeQuaero::s_ModeStringMap(modeStringMap, modeStringMap+9);

ModeQuaero::ModeQuaero()
{
    Mode t(Mode::minorNatural().addInterval(Interval::majorSixth()));
}

ModeQuaero::ModeQuaero(const Mode& inMode)
: Mode(inMode)
{
}

ModeQuaero::ModeQuaero(const std::string& inString)
{
    const map<string,Mode>::const_iterator theMapPos = s_ModeStringMap.find(inString);
	if (theMapPos != s_ModeStringMap.end())
	{
		*this = theMapPos->second;
	}
	else
	{
		throw std::invalid_argument("Unknown Quaero mode " + inString);
	}
}

const std::string ModeQuaero::str(const Chroma& inTonicChroma /*= Chroma::undefined()*/) const
{
	if (*this == major())
	{
		return "M";
	}
	if (*this == mixolydian())
	{
		return "mix";
	}
	if (*this == minorNatural())
	{
		return "m";
	}
	if (*this == minorHarmonic())
	{
		return "harmo";
	}
	if (*this == minorMelodic())
	{
		return "meloa";
	}
	if (*this == minorNatural().addInterval(Interval::majorSixth()))
	{
		return "melod";
	}
	if (*this == dorian())
	{
		return "dor";
	}
	if (*this == mixolydian().addInterval(Interval::minorThird()).addInterval(Interval::diminishedFifth()))
	{
		return "blues";
	}
	if (*this == dorian().addInterval(Interval::diminishedFifth()))
	{
		return "bluesm";
	}
	if (*this == none())
	{
		return "none";
	}
	else
	{
		ostringstream theModeStream;
        for (std::set<Interval>::const_iterator i = m_IntervalList.begin(); i != m_IntervalList.end(); ++i)
        {
            theModeStream << " + " << ChordTypeQuaero::getConstrainedString(ChromaSolfege(inTonicChroma, *i));
        }
        return theModeStream.str();
	}
}

std::ostream& MusOO::operator<<(std::ostream& inOutputStream, const KeyQuaero& inKey)
{
	inOutputStream << inKey.str();
	return inOutputStream;
}

std::ostream& MusOO::operator<<(std::ostream& inOutputStream, const ModeQuaero& inMode)
{
	inOutputStream << inMode.str();
	return inOutputStream;
}
