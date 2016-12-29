//============================================================================
/**
 Implementation file for ModeQuaero.h
 
 @author	Johan Pauwels
 @date		20130417
 */
//============================================================================

// Includes
#include <sstream>
#include <stdexcept>
#include "MusOO/ModeQuaero.h"
#include "MusOO/ChordTypeQuaero.h"
#include "MusOO/ChromaSolfege.h"



using std::pair;
using std::map;
using std::istringstream;
using std::ostringstream;
using std::invalid_argument;
using std::string;
using namespace MusOO;

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
		throw std::invalid_argument("Unknown Quaero mode '" + inString + "'");
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

std::ostream& MusOO::operator<<(std::ostream& inOutputStream, const ModeQuaero& inMode)
{
	inOutputStream << inMode.str();
	return inOutputStream;
}
