//============================================================================
/**
 Implementation file for ChordTypeQuaero.h
 
 @author		Johan Pauwels
 @date		20101220
 */
//============================================================================

// Includes
#include "MusOO/ChordTypeQuaero.h"
#include "MusOO/ChromaSolfege.h"
#include <stdexcept>
#include <algorithm>

using std::pair;
using std::string;
using std::min;
using std::set;
using namespace MusOO;

static const pair<std::string,ChordTypeQuaero> typeStringMap[] =
{
	pair<std::string,ChordTypeQuaero>("5th",ChordTypeQuaero::power()),
	//triads
	pair<std::string,ChordTypeQuaero>("M",ChordTypeQuaero::major()),
	pair<std::string,ChordTypeQuaero>("m",ChordTypeQuaero::minor()),
	pair<std::string,ChordTypeQuaero>("d",ChordTypeQuaero::diminished()),
	pair<std::string,ChordTypeQuaero>("a",ChordTypeQuaero::augmented()),
	pair<std::string,ChordTypeQuaero>("sus2",ChordTypeQuaero::suspendedSecond()),
	pair<std::string,ChordTypeQuaero>("sus4",ChordTypeQuaero::suspendedFourth()),
	//tetrads
	pair<std::string,ChordTypeQuaero>("7M",ChordTypeQuaero::majorSeventh()),
	pair<std::string,ChordTypeQuaero>("m7",ChordTypeQuaero::minorSeventh()),
	pair<std::string,ChordTypeQuaero>("7",ChordTypeQuaero::dominantSeventh()),
	pair<std::string,ChordTypeQuaero>("m7M",ChordTypeQuaero::minorMajorSeventh()),
	pair<std::string,ChordTypeQuaero>("d7",ChordTypeQuaero::halfDiminished()),
	pair<std::string,ChordTypeQuaero>("7d",ChordTypeQuaero::diminishedSeventh()),
	pair<std::string,ChordTypeQuaero>("7sus2",ChordTypeQuaero::suspendedSecond().addInterval(SimpleInterval::minorSeventh())),
	pair<std::string,ChordTypeQuaero>("7sus4",ChordTypeQuaero::suspendedFourth().addInterval(SimpleInterval::minorSeventh())),
	pair<std::string,ChordTypeQuaero>("7Msus2",ChordTypeQuaero::suspendedSecond().addInterval(SimpleInterval::majorSeventh())),
	pair<std::string,ChordTypeQuaero>("7Msus4",ChordTypeQuaero::suspendedFourth().addInterval(SimpleInterval::majorSeventh())),
	pair<std::string,ChordTypeQuaero>("6",ChordTypeQuaero::majorSixth()),
	pair<std::string,ChordTypeQuaero>("m6",ChordTypeQuaero::minor().addInterval(SimpleInterval::minorSixth())),
	pair<std::string,ChordTypeQuaero>("m6M",ChordTypeQuaero::minorSixth()),
	//pentads
	pair<std::string,ChordTypeQuaero>("9",ChordTypeQuaero::dominantNinth()),
	pair<std::string,ChordTypeQuaero>("m9",ChordTypeQuaero::minorNinth()),
	pair<std::string,ChordTypeQuaero>("9(7M)",ChordTypeQuaero::majorNinth()),
	pair<std::string,ChordTypeQuaero>("m9(7M)",ChordTypeQuaero::minorMajorSeventh().addInterval(SimpleInterval::majorSecond()))
};
const std::map<std::string,ChordTypeQuaero> ChordTypeQuaero::s_TypeStringMap(typeStringMap, typeStringMap+24);


ChordTypeQuaero::ChordTypeQuaero(std::string inName)
{
	const std::map<std::string,ChordTypeQuaero>::const_iterator theMapPos = s_TypeStringMap.find(inName);
	if (theMapPos != s_TypeStringMap.end())
	{
		*this = theMapPos->second;
	}
	else
	{
		throw std::invalid_argument("Unknown Quaero chord type '" + inName + "'");
	}
}

const std::string ChordTypeQuaero::str() const
{
    return str(ChromaSolfege::undefined());
}

const std::string ChordTypeQuaero::str(const ChromaSolfege& inRootChroma) const
{	
	string theString = "";
	set<SimpleInterval> theRestIntervals;
	set<SimpleInterval> theMissingIntervals;
	if (*this == ChordTypeQuaero::none())
	{
		//initialised values are correct
	}
	//if the formula contains major third
	else if (m_set.count(SimpleInterval::majorThird()) > 0)
	{
		//if formula contains only augmented fifth
		if (m_set.count(SimpleInterval::augmentedFifth()) > 0 && m_set.count(SimpleInterval::perfectFifth()) == 0)
		{
			theString = "a";
			subtract(ChordTypeQuaero::augmented(), theRestIntervals, theMissingIntervals);
		}
		//if formula contains minor seventh
		else if (m_set.count(SimpleInterval::minorSeventh()) > 0)
		{
			//if formula contains major ninth
			if (m_set.count(SimpleInterval::majorSecond()) > 0)
			{
				theString = "9";
				subtract(ChordTypeQuaero::dominantNinth(), theRestIntervals, theMissingIntervals);
			}
			else
			{
				theString = "7";
				subtract(ChordTypeQuaero::dominantSeventh(), theRestIntervals, theMissingIntervals);
			}
		}
		//if formula contains major seventh
		else if (m_set.count(SimpleInterval::majorSeventh()) > 0)
		{
			//if formula contains major ninth
			if (m_set.count(SimpleInterval::majorSecond()) > 0)
			{
				theString = "9(7M)";
				subtract(ChordTypeQuaero::majorNinth(), theRestIntervals, theMissingIntervals);
			}
			else
			{
				theString = "7M";
				subtract(ChordTypeQuaero::majorSeventh(), theRestIntervals, theMissingIntervals);
			}
		}
		//if formula contains major sixth
		else if (m_set.count(SimpleInterval::majorSixth()) > 0)
		{
			theString = "6";
			subtract(ChordTypeQuaero::majorSixth(), theRestIntervals, theMissingIntervals);
		}
		else 
		{
			theString = "M";
			subtract(ChordTypeQuaero::major(), theRestIntervals, theMissingIntervals);
		}
	}
	//if the formula contains minor third
	else if (m_set.count(SimpleInterval::minorThird()) > 0)
	{
		//if formula contains only diminished fifth
		if (m_set.count(SimpleInterval::diminishedFifth()) > 0 && m_set.count(SimpleInterval::perfectFifth()) == 0)
		{
			//if formula contains minor seventh
			if (m_set.count(SimpleInterval::minorSeventh()) > 0)
			{
				theString = "d7";
				subtract(ChordTypeQuaero::halfDiminished(), theRestIntervals, theMissingIntervals);
			}
			//if formula contains diminished seventh
			else if (m_set.count(SimpleInterval::diminishedSeventh()) > 0)
			{
				theString = "7d";
				subtract(ChordTypeQuaero::diminishedSeventh(), theRestIntervals, theMissingIntervals);
			}
			else
			{
				theString = "d";
				subtract(ChordTypeQuaero::diminished(), theRestIntervals, theMissingIntervals);
			}
		}
		//if formula contains minor seventh
		else if (m_set.count(SimpleInterval::minorSeventh()) > 0)
		{
			//if formula contains major ninth
			if (m_set.count(SimpleInterval::majorSecond()) > 0)
			{
				theString = "m9";
				subtract(ChordTypeQuaero::minorNinth(), theRestIntervals, theMissingIntervals);
			}
			else
			{
				theString = "m7";
				subtract(ChordTypeQuaero::minorSeventh(), theRestIntervals, theMissingIntervals);
			}
		}
		//if formula contains major seventh
		else if (m_set.count(SimpleInterval::majorSeventh()) > 0)
		{
			//if formula contains major ninth
			if (m_set.count(SimpleInterval::majorSecond()) > 0)
			{
				theString = "m9(7M)";
				subtract(ChordTypeQuaero::minorMajorSeventh().addInterval(SimpleInterval::majorSecond()), theRestIntervals, theMissingIntervals);
			}
			else
			{
				theString = "m7M";
				subtract(ChordTypeQuaero::minorMajorSeventh(), theRestIntervals, theMissingIntervals);
			}
		}
		//if formula contains major sixth
		else if (m_set.count(SimpleInterval::majorSixth()) > 0)
		{
			theString = "m6M";
			subtract(ChordTypeQuaero::minorSixth(), theRestIntervals, theMissingIntervals);
		}
		//if formula contains minor sixth
		else if (m_set.count(SimpleInterval::majorSixth()) > 0)
		{
			theString = "m6";
			subtract(ChordTypeQuaero::minor().addInterval(SimpleInterval::minorSixth()), theRestIntervals, theMissingIntervals);
		}
		else 
		{
			theString = "m";
			subtract(ChordTypeQuaero::minor(), theRestIntervals, theMissingIntervals);
		}
	}
	//if the formula contains perfect fourth (and no third or major second)
	else if (m_set.count(SimpleInterval::perfectFourth()) > 0 && m_set.count(SimpleInterval::majorSecond()) == 0)
	{
		//if formula contains minor seventh
		if (m_set.count(SimpleInterval::minorSeventh()) > 0)
		{
			theString = "7sus4";
			subtract(ChordTypeQuaero::suspendedFourthSeventh(), theRestIntervals, theMissingIntervals);
		}
		//if formula contains major seventh
		else if (m_set.count(SimpleInterval::majorSeventh()) > 0)
		{
			theString = "7Msus4";
			subtract(ChordTypeQuaero::suspendedFourth().addInterval(SimpleInterval::majorSeventh()), theRestIntervals, theMissingIntervals);
		}
		else
		{
			theString = "sus4";
			subtract(ChordTypeQuaero::suspendedFourth(), theRestIntervals, theMissingIntervals);
		}
	}
	//if the formula contains major second (and no third or perfect fourth)
	else if (m_set.count(SimpleInterval::majorSecond()) > 0 && m_set.count(SimpleInterval::perfectFourth()) == 0)
	{
		//if formula contains minor seventh
		if (m_set.count(SimpleInterval::minorSeventh()) > 0)
		{
			theString = "7sus2";
			subtract(ChordTypeQuaero::suspendedSecond().addInterval(SimpleInterval::minorSeventh()), theRestIntervals, theMissingIntervals);
		}
		//if formula contains major seventh
		else if (m_set.count(SimpleInterval::majorSeventh()) > 0)
		{
			theString = "7Msus2";
			subtract(ChordTypeQuaero::suspendedSecond().addInterval(SimpleInterval::majorSeventh()), theRestIntervals, theMissingIntervals);
		}
		else
		{
			theString = "sus2";
			subtract(ChordTypeQuaero::suspendedSecond(), theRestIntervals, theMissingIntervals);
		}

	}
	//if the formula contains perfect fifth
	else if (m_set.count(SimpleInterval::perfectFifth()) > 0)
	{
		theString = "5th";
		subtract(ChordTypeQuaero::power(), theRestIntervals, theMissingIntervals);
	}
	
	for (set<SimpleInterval>::const_iterator theRestIt = theRestIntervals.begin(); theRestIt != theRestIntervals.end(); ++theRestIt)
	{
		theString += " + " + getConstrainedString(ChromaSolfege(inRootChroma, *theRestIt));
	}
	for (set<SimpleInterval>::const_iterator theMissingIt = theMissingIntervals.begin(); theMissingIt != theMissingIntervals.end(); ++theMissingIt)
	{
		theString += " - " + getConstrainedString(ChromaSolfege(inRootChroma, *theMissingIt));
	}
	if (m_Bass != SimpleInterval::undefined())
	{
		theString += " / " + getConstrainedString(ChromaSolfege(inRootChroma, m_Bass));
	}

	return theString;
}

const std::string ChordTypeQuaero::getConstrainedString(const ChromaSolfege& inChroma)
{
	string theConstrainedString = inChroma.str();
	if (theConstrainedString.size() == 2)
	{
		theConstrainedString += " ";
	}
	else if (theConstrainedString.size() > 3)
	{
		theConstrainedString = theConstrainedString.substr(0,2) + theConstrainedString[theConstrainedString.size()-1];
	}
	return theConstrainedString;
}
