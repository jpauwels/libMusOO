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

static const pair<string,ModeQuaero> modeStringMap[] =
{
	pair<string,ModeQuaero>("M", ModeQuaero::major()),
	pair<string,ModeQuaero>("mix", ModeQuaero::mixolydian()),
	pair<string,ModeQuaero>("m", ModeQuaero::minorNatural()),
	pair<string,ModeQuaero>("harmo", ModeQuaero::minorHarmonic()),
	pair<string,ModeQuaero>("meloa", ModeQuaero::minorMelodic()),
	pair<string,ModeQuaero>("melod", ModeQuaero::minorNatural().addInterval(SimpleInterval::majorSixth())),
	pair<string,ModeQuaero>("dor", ModeQuaero::dorian()),
	pair<string,ModeQuaero>("blues", ModeQuaero::mixolydian().addInterval(SimpleInterval::minorThird()).addInterval(SimpleInterval::diminishedFifth())),
	pair<string,ModeQuaero>("bluesm", ModeQuaero::dorian().addInterval(SimpleInterval::diminishedFifth()))
};
const map<string,ModeQuaero> ModeQuaero::s_ModeStringMap(modeStringMap, modeStringMap+9);

ModeQuaero::ModeQuaero(const std::string& inString)
{
    const map<string,ModeQuaero>::const_iterator theMapPos = s_ModeStringMap.find(inString);
	if (theMapPos != s_ModeStringMap.end())
	{
		*this = theMapPos->second;
	}
	else
	{
		throw std::invalid_argument("Unknown Quaero mode '" + inString + "'");
	}
}

const std::string ModeQuaero::str() const
{
    return str(ChromaSolfege::undefined());
}

const std::string ModeQuaero::str(const ChromaSolfege& inTonicChroma) const
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
	if (*this == minorNatural().addInterval(SimpleInterval::majorSixth()))
	{
		return "melod";
	}
	if (*this == dorian())
	{
		return "dor";
	}
	if (*this == mixolydian().addInterval(SimpleInterval::minorThird()).addInterval(SimpleInterval::diminishedFifth()))
	{
		return "blues";
	}
	if (*this == dorian().addInterval(SimpleInterval::diminishedFifth()))
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
        for (std::set<SimpleInterval>::const_iterator i = m_set.begin(); i != m_set.end(); ++i)
        {
            theModeStream << " + " << ChordTypeQuaero::getConstrainedString(ChromaSolfege(inTonicChroma, *i));
        }
        return theModeStream.str();
	}
}
