//============================================================================
/**
 Implementation file for ChordQuaero.h
 
 @author		Johan Pauwels
 @date		20101220
 */
//============================================================================

// Includes
#include <map>
#include <stdexcept>
#include "ChordQuaero.h"
#include "ChromaSolfege.h"

using std::map;
using std::pair;
using std::string;
using std::vector;
using std::min;

//----------------------------------------------------------------------------//
// ChordQuaero                                                                //
//----------------------------------------------------------------------------//
ChordQuaero::ChordQuaero()
{
}

ChordQuaero::ChordQuaero(const std::string& inChordName)
{
	m_Root = Chroma(trimRight(inChordName.substr(0,2)));
	size_t theTypeEndPosition = inChordName.substr(0,2).find_first_of(" ");
	m_Type = ChordTypeQuaero(inChordName.substr(2,theTypeEndPosition));
	size_t theSlashPosition = inChordName.find_first_of("/");
	for (size_t theModBeginPosition = theTypeEndPosition+2; theModBeginPosition < min(theSlashPosition-1,inChordName.size()); theModBeginPosition+=6)
	{
		if (inChordName[theModBeginPosition+1] == '+')
		{
			addChroma(ChromaSolfege(trimRight(inChordName.substr(theModBeginPosition+3, 3))));
		}
		else if (inChordName[theModBeginPosition+1] == '-')
		{
			deleteChroma(ChromaSolfege(trimRight(inChordName.substr(theModBeginPosition+3, 3))));
		}
		else
		{
			throw std::invalid_argument("Malformed Quaero chord " + inChordName);
		}
	}
	if (theSlashPosition != string::npos)
	{
		addBass(ChromaSolfege(trimRight(inChordName.substr(theSlashPosition+2))));
	}
}

ChordQuaero::ChordQuaero(const Chord& inChord)
: Chord(inChord)
{
}

ChordQuaero::~ChordQuaero()
{
}

const std::string ChordQuaero::str() const
{
	return m_Root.str() + ChordTypeQuaero(m_Type).str(m_Root);
}

const std::string ChordQuaero::trimRight(const std::string& inString)
{
	const size_t theEndIdx = inString.find_last_not_of(" ");
    return inString.substr(0, theEndIdx+1);
}

std::ostream& operator<<(std::ostream& inOutputStream, const ChordQuaero& inChord)
{
	inOutputStream << inChord.str();
	return inOutputStream;
}

std::istream& operator>>(std::istream& inInputStream, ChordQuaero& inChord)
{
	string theChordString;
	inInputStream >> theChordString;
	inChord = ChordQuaero(theChordString);
	return inInputStream;
}

//----------------------------------------------------------------------------
// ChordTypeQuaero
//----------------------------------------------------------------------------
static const pair<string,ChordType> typeStringMap[] =
{
	pair<string,ChordType>("5th",ChordType::power()),
	//triads
	pair<string,ChordType>("M",ChordType::major()),
	pair<string,ChordType>("m",ChordType::minor()),
	pair<string,ChordType>("d",ChordType::diminished()),
	pair<string,ChordType>("a",ChordType::augmented()),
	pair<string,ChordType>("sus2",ChordType::suspendedSecond()),
	pair<string,ChordType>("sus4",ChordType::suspendedFourth()),
	//tetrads
	pair<string,ChordType>("7M",ChordType::majorSeventh()),
	pair<string,ChordType>("m7",ChordType::minorSeventh()),
	pair<string,ChordType>("7",ChordType::dominantSeventh()),
	pair<string,ChordType>("m7M",ChordType::minorMajorSeventh()),
	pair<string,ChordType>("d7",ChordType::halfDiminished()),
	pair<string,ChordType>("7d",ChordType::diminishedSeventh()),
	pair<string,ChordType>("7sus2",ChordType::suspendedSecond().addInterval(Interval::minorSeventh())),
	pair<string,ChordType>("7sus4",ChordType::suspendedFourth().addInterval(Interval::minorSeventh())),
	pair<string,ChordType>("7Msus2",ChordType::suspendedSecond().addInterval(Interval::majorSeventh())),
	pair<string,ChordType>("7Msus4",ChordType::suspendedFourth().addInterval(Interval::majorSeventh())),
	pair<string,ChordType>("6",ChordType::majorSixth()),
	pair<string,ChordType>("m6",ChordType::minor().addInterval(Interval::minorSixth())),
	pair<string,ChordType>("m6M",ChordType::minorSixth()),
	//pentads
	pair<string,ChordType>("9",ChordType::dominantNinth()),
	pair<string,ChordType>("m9",ChordType::minorNinth()),
	pair<string,ChordType>("9(7M)",ChordType::majorNinth()),
	pair<string,ChordType>("m9(7M)",ChordType::minorMajorSeventh().addInterval(Interval::majorNinth()))
};
const map<string,ChordType> ChordTypeQuaero::s_TypeStringMap(typeStringMap, typeStringMap+24);

ChordTypeQuaero::ChordTypeQuaero()
{
}

ChordTypeQuaero::ChordTypeQuaero(std::string inName)
{
	const map<string,ChordType>::const_iterator theMapPos = s_TypeStringMap.find(inName);
	if (theMapPos != s_TypeStringMap.end())
	{
		*this = theMapPos->second;
	}
	else
	{
		throw std::invalid_argument("Unknown Quaero chord type " + inName);
	}
}

ChordTypeQuaero::ChordTypeQuaero(const ChordType& inChordType)
: ChordType(inChordType)
{
}

ChordTypeQuaero::~ChordTypeQuaero()
{
}

const std::string ChordTypeQuaero::str(const Chroma& inRootChroma /*= Chroma::undefined()*/) const
{	
	string theString = "";
	vector<Interval> theRestIntervals;
	vector<Interval> theMissingIntervals;
	if (*this == ChordType::none())
	{
		//initialised values are correct
	}
	//if the formula contains major third
	else if (m_Formula.count(Interval::majorThird()) > 0)
	{
		//if formula contains augmented fifth
		if (m_Formula.count(Interval::augmentedFifth()) > 0)
		{
			theString = "a";
			subtract(ChordType::augmented(), theRestIntervals, theMissingIntervals);
		}
		//if formula contains minor seventh
		else if (m_Formula.count(Interval::minorSeventh()) > 0)
		{
			//if formula contains major ninth
			if (m_Formula.count(Interval::majorNinth()) > 0)
			{
				theString = "9";
				subtract(ChordType::dominantNinth(), theRestIntervals, theMissingIntervals);
			}
			else
			{
				theString = "7";
				subtract(ChordType::dominantSeventh(), theRestIntervals, theMissingIntervals);
			}
		}
		//if formula contains major seventh
		else if (m_Formula.count(Interval::majorSeventh()) > 0)
		{
			//if formula contains major ninth
			if (m_Formula.count(Interval::majorNinth()) > 0)
			{
				theString = "9(7M)";
				subtract(ChordType::majorNinth(), theRestIntervals, theMissingIntervals);
			}
			else
			{
				theString = "7M";
				subtract(ChordType::majorSeventh(), theRestIntervals, theMissingIntervals);
			}
		}
		//if formula contains major sixth
		else if (m_Formula.count(Interval::majorSixth()) > 0)
		{
			theString = "6";
			subtract(ChordType::majorSixth(), theRestIntervals, theMissingIntervals);
		}
		else 
		{
			theString = "M";
			subtract(ChordType::major(), theRestIntervals, theMissingIntervals);
		}
	}
	//if the formula contains minor third
	else if (m_Formula.count(Interval::minorThird()) > 0)
	{
		//if formula contains diminished fifth
		if (m_Formula.count(Interval::diminishedFifth()) > 0)
		{
			//if formula contains minor seventh
			if (m_Formula.count(Interval::minorSeventh()) > 0)
			{
				theString = "d7";
				subtract(ChordType::halfDiminished(), theRestIntervals, theMissingIntervals);
			}
			//if formula contains diminished seventh
			else if (m_Formula.count(Interval::diminishedSeventh()) > 0)
			{
				theString = "7d";
				subtract(ChordType::diminishedSeventh(), theRestIntervals, theMissingIntervals);
			}
			else
			{
				theString = "d";
				subtract(ChordType::diminished(), theRestIntervals, theMissingIntervals);
			}
		}
		//if formula contains minor seventh
		else if (m_Formula.count(Interval::minorSeventh()) > 0)
		{
			//if formula contains major ninth
			if (m_Formula.count(Interval::majorNinth()) > 0)
			{
				theString = "m9";
				subtract(ChordType::minorNinth(), theRestIntervals, theMissingIntervals);
			}
			else
			{
				theString = "m7";
				subtract(ChordType::minorSeventh(), theRestIntervals, theMissingIntervals);
			}
		}
		//if formula contains major seventh
		else if (m_Formula.count(Interval::majorSeventh()) > 0)
		{
			//if formula contains major ninth
			if (m_Formula.count(Interval::majorNinth()) > 0)
			{
				theString = "m9(7M)";
				subtract(ChordType::minorMajorSeventh().addInterval(Interval::majorNinth()), theRestIntervals, theMissingIntervals);
			}
			else
			{
				theString = "m7M";
				subtract(ChordType::minorMajorSeventh(), theRestIntervals, theMissingIntervals);
			}
		}
		//if formula contains major sixth
		else if (m_Formula.count(Interval::majorSixth()) > 0)
		{
			theString = "m6M";
			subtract(ChordType::minorSixth(), theRestIntervals, theMissingIntervals);
		}
		//if formula contains minor sixth
		else if (m_Formula.count(Interval::majorSixth()) > 0)
		{
			theString = "m6";
			subtract(ChordType::minor().addInterval(Interval::minorSixth()), theRestIntervals, theMissingIntervals);
		}
		else 
		{
			theString = "m";
			subtract(ChordType::minor(), theRestIntervals, theMissingIntervals);
		}
	}
	//if the formula contains perfect fourth
	else if (m_Formula.count(Interval::perfectFourth()) > 0)
	{
		//if formula contains minor seventh
		if (m_Formula.count(Interval::minorSeventh()) > 0)
		{
			theString = "7sus4";
			subtract(ChordType::suspendedFourthSeventh(), theRestIntervals, theMissingIntervals);
		}
		//if formula contains major seventh
		else if (m_Formula.count(Interval::majorSeventh()) > 0)
		{
			theString = "7Msus4";
			subtract(ChordType::suspendedFourth().addInterval(Interval::majorSeventh()), theRestIntervals, theMissingIntervals);
		}
		else
		{
			theString = "sus4";
			subtract(ChordType::suspendedFourth(), theRestIntervals, theMissingIntervals);
		}

	}
	//if the formula contains major second
	else if (m_Formula.count(Interval::majorSecond()) > 0)
	{
		//if formula contains minor seventh
		if (m_Formula.count(Interval::minorSeventh()) > 0)
		{
			theString = "7sus2";
			subtract(ChordType::suspendedSecond().addInterval(Interval::minorSeventh()), theRestIntervals, theMissingIntervals);
		}
		//if formula contains major seventh
		else if (m_Formula.count(Interval::majorSeventh()) > 0)
		{
			theString = "7Msus2";
			subtract(ChordType::suspendedSecond().addInterval(Interval::majorSeventh()), theRestIntervals, theMissingIntervals);
		}
		else
		{
			theString = "sus2";
			subtract(ChordType::suspendedSecond(), theRestIntervals, theMissingIntervals);
		}

	}
	//if the formula contains perfect fifth
	else if (m_Formula.count(Interval::perfectFifth()) > 0)
	{
		theString = "5th";
		subtract(ChordType::power(), theRestIntervals, theMissingIntervals);
	}
	
	for (vector<Interval>::const_iterator theRestIt = theRestIntervals.begin(); theRestIt != theRestIntervals.end(); ++theRestIt)
	{
		theString += " + " + getConstrainedString(ChromaSolfege(inRootChroma, *theRestIt));
	}
	for (vector<Interval>::const_iterator theMissingIt = theMissingIntervals.begin(); theMissingIt != theMissingIntervals.end(); ++theMissingIt)
	{
		theString += " - " + getConstrainedString(ChromaSolfege(inRootChroma, *theMissingIt));
	}
	if (m_Bass != Interval::undefined())
	{
		theString += " / " + getConstrainedString(ChromaSolfege(inRootChroma, m_Bass));
	}

	return theString;
}

const std::string ChordTypeQuaero::getConstrainedString(const ChromaSolfege& inChromaSolfege) const
{
	string theConstrainedString = inChromaSolfege.str();
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

std::istream& operator>>(std::istream& inInputStream, ChordTypeQuaero& outChordType)
{
	std::string theString;
	inInputStream >> theString;
	outChordType = ChordTypeQuaero(theString);
	return inInputStream;
}

std::ostream& operator<<(std::ostream& inOutputStream, const ChordTypeQuaero& inChordType)
{
	inOutputStream << inChordType.str();
	return inOutputStream;
}
