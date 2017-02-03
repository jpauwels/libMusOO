//============================================================================
/**
Implementation file for ChordQM.h

@author		Johan Pauwels
@date		20090119
*/
//============================================================================

// Includes
#include <stdexcept>
#include <algorithm>
#include <sstream>
#include "MusOO/ChordQM.h"

using std::string;
using std::vector;
using std::map;
using std::pair;
using std::invalid_argument;
using std::istringstream;
using std::ostringstream;
using std::min;
using std::set;
using namespace MusOO;

//----------------------------------------------------------------------------//
// ChordQM                                                                    //
//----------------------------------------------------------------------------//
ChordQM::ChordQM()
{
}

ChordQM::ChordQM(const std::string& inChordString)
{
	if (!inChordString.compare(0,1,"S"))
	{
		// Silence
		*this = Chord::silence();
	}
	else if (!inChordString.compare(0,1,"N"))
	{
		// No-chord
		*this = Chord::none();
	}
	else if (inChordString == "X")
	{
		// Undefined
		*this = Chord::undefined();
	}
	else
	{
		//find colon which separates root and type
		size_t theColon = inChordString.find(":");
		size_t theSlash = inChordString.find("/");
		m_Root = Chroma(inChordString.substr(0,min(theColon, theSlash)));
		
		if (theColon != string::npos)
		{
			//explicit type, optional slash
			m_Type = ChordTypeQM(inChordString.substr(theColon+1));
		}
		else
		{
			if (theSlash == string::npos)
			{
				//no explicit type, no slash
				m_Type = ChordType::major();
			}
			else
			{
				//no explicit type, with slash
				m_Type = ChordTypeQM("maj"+inChordString.substr(theSlash));
			}
		}
	}
}

ChordQM::ChordQM(const Chord& inChord)
: Chord(inChord)
{
}

ChordQM::~ChordQM()
{
	// Nothing to do...
}

const std::string ChordQM::str() const
{
	string theChordString = m_Root.str();
	if (m_Type != ChordType::none())
	{
		theChordString += ":" + ChordTypeQM(m_Type).str();
	}
	return theChordString;
}

//----------------------------------------------------------------------------//
// ChordChordino                                                                 //
//----------------------------------------------------------------------------//
ChordChordino::ChordChordino()
{
}

ChordChordino::ChordChordino(std::string inChordString)
{
	if (!inChordString.compare(0,1,"S"))
	{
		// Silence
		*this = Chord::silence();
	}
	else if (!inChordString.compare(0,1,"N"))
	{
		// No-chord
		*this = Chord::none();
	}
	else
	{
		//find colon which separates root and type
		size_t theTypeStart = inChordString.find_first_not_of("ABCDEFGb#");
		size_t theSlash = inChordString.find("/");
		m_Root = Chroma(inChordString.substr(0,theTypeStart));
		//replace bass note name by circle steps
		if (theSlash != string::npos)
		{
			ostringstream theDistanceStream;
			theDistanceStream << Interval(m_Root, Chroma(inChordString.substr(theSlash+1,1))).circleStepsCW();
			inChordString.replace(theSlash+1,string::npos,theDistanceStream.str());
		}
		if (theTypeStart != string::npos && theSlash == string::npos)
		{
			//explicit type, optional slash
			m_Type = ChordTypeQM(inChordString.substr(theTypeStart));
		}
		else
		{
			if (theSlash == string::npos)
			{
				//no explicit type, no slash
				m_Type = ChordType::major();
			}
			else
			{
				//no explicit type, with slash
				m_Type = ChordTypeQM("maj"+inChordString.substr(theSlash));
			}
		}
	}
}

ChordChordino::ChordChordino(const Chord& inChord)
: Chord(inChord)
{
}

ChordChordino::~ChordChordino()
{
}

const std::string ChordChordino::str() const
{
	string theChordString = m_Root.str();
	if (m_Type != ChordType::none() && m_Type != ChordType::major())
	{
		theChordString += ChordTypeQM(m_Type).str();
	}
	return theChordString;
}

//----------------------------------------------------------------------------//
// ChordTypeQM                                                                //
//----------------------------------------------------------------------------//
static const pair<string,ChordType> typeStringMap[] = {
	pair<string,ChordType>("",ChordType::none()),
	//triads
	pair<string,ChordType>("maj",ChordType::major()), 
	pair<string,ChordType>("min",ChordType::minor()),
	pair<string,ChordType>("dim",ChordType::diminished()), 
	pair<string,ChordType>("aug",ChordType::augmented()),
	//seventh chords
	pair<string,ChordType>("maj7",ChordType::majorSeventh()), 
	pair<string,ChordType>("min7",ChordType::minorSeventh()),
	pair<string,ChordType>("7",ChordType::dominantSeventh()), 
	pair<string,ChordType>("dim7",ChordType::diminishedSeventh()),
	pair<string,ChordType>("hdim7",ChordType::halfDiminished()), 
	pair<string,ChordType>("minmaj7",ChordType::minorMajorSeventh()),
	//sixth chords
	pair<string,ChordType>("maj6",ChordType::majorSixth()), 
	pair<string,ChordType>("min6",ChordType::minorSixth()),
	//extended chords
	pair<string,ChordType>("9",ChordType::dominantNinth()), 
	pair<string,ChordType>("maj9",ChordType::majorNinth()),
	pair<string,ChordType>("min9",ChordType::minorNinth()),
	//suspended chords
	pair<string,ChordType>("sus4",ChordType::suspendedFourth()),
	//additions Rik
	pair<string,ChordType>("sus2",ChordType::suspendedSecond()), 
	pair<string,ChordType>("7sus4",ChordType::suspendedFourthSeventh()),
	pair<string,ChordType>("aug7",ChordType::augmentedSeventh()),
    //billboard additions
    pair<string,ChordType>("1",ChordType::rootOnly()),
    pair<string,ChordType>("5",ChordType::power()),
    pair<string,ChordType>("maj11",ChordType::majorEleventh()),
    pair<string,ChordType>("11",ChordType::dominantEleventh()),
    pair<string,ChordType>("min11",ChordType::minorEleventh()),
    pair<string,ChordType>("maj13",ChordType::majorThirteenth()),
    pair<string,ChordType>("13",ChordType::dominantEleventh()),
    pair<string,ChordType>("min13",ChordType::minorEleventh())};
const map<string,ChordType> ChordTypeQM::s_TypeStringMap(typeStringMap, typeStringMap+28);

ChordTypeQM::ChordTypeQM(std::string inName)
{
	//find borders of base type
	size_t theBaseNameEnd = inName.find_first_of("(/");
	//convert basic type to circle steps formula
	map<string,ChordType>::const_iterator theMapPos = 
		s_TypeStringMap.find(inName.substr(0,theBaseNameEnd));
	if (theMapPos != s_TypeStringMap.end()) {
		*this = theMapPos->second;
	} else {
		throw invalid_argument("Unknown QM chord type '" + inName.substr(0,theBaseNameEnd) + "'");
	}
	//check for formula modifiers
	size_t theOpenBracket = inName.find("(");
	if (theOpenBracket != string::npos)
	{
		//isolate formula modifiers and parse them
		size_t theCloseBracket = inName.find(")");
		if (theCloseBracket == string::npos)
		{
			throw invalid_argument("No closing bracket present in '" + inName + "'");
		}
		string theFormulaModifiers = inName.substr(theOpenBracket+1,theCloseBracket-theOpenBracket-1);
		size_t theComma = theFormulaModifiers.find(",");
		while (theComma != string::npos)
		{
			parseFormulaModifier(theFormulaModifiers.substr(0,theComma));
			theFormulaModifiers = theFormulaModifiers.substr(theComma+1,string::npos);
			theComma = theFormulaModifiers.find(",");
		}
		parseFormulaModifier(theFormulaModifiers);
	}
	//check if there is a bass note after a forward slash
	size_t theSlash = inName.find("/");
	if (theSlash != string::npos)
	{
		addBassNote(inName.substr(theSlash+1,string::npos));
	}
}

ChordTypeQM::ChordTypeQM()
{
}

ChordTypeQM::ChordTypeQM(const ChordType& inChordType)
: ChordType(inChordType)
{
}

ChordTypeQM::~ChordTypeQM()
{
	// Nothing to do...
}

void ChordTypeQM::parseFormulaModifier(std::string inFormulaModifier)
{
	if (!inFormulaModifier.substr(0,1).compare("*"))
	{
		deleteNote(inFormulaModifier.substr(1,string::npos));
	}
	else
	{
		addNote(inFormulaModifier);
	}
}

void ChordTypeQM::addNote(const std::string& inDegree)
{
	addInterval(Interval(inDegree));
}

void ChordTypeQM::addBassNote(const std::string& inDegree)
{
	addBass(Interval(inDegree));
}

void ChordTypeQM::replaceNote(const std::string& inToBeReplaced, const std::string& inReplacement)
{
	replaceInterval(Interval(inToBeReplaced), Interval(inReplacement));
}

void ChordTypeQM::deleteNote(const std::string& inDegree)
{
	deleteInterval(Interval(inDegree));
}

const std::string ChordTypeQM::str() const
{
 	string theString;
    set<Interval> theRestIntervals;
    set<Interval> theMissingIntervals;

    if (*this == ChordType::none())
	{
		return "";
	}
	else
    {
        //if the formula contains major third
        if (m_IntervalList.count(Interval::majorThird()) > 0)
        {
            //if formula contains only augmented fifth
            if (m_IntervalList.count(Interval::augmentedFifth()) > 0 && m_IntervalList.count(Interval::perfectFifth()) == 0)
            {
                theString = "aug";
                subtract(augmented(), theRestIntervals, theMissingIntervals);
            }
            //if formula contains minor seventh (no fifth necessary)
            else if (m_IntervalList.count(Interval::minorSeventh()) > 0)
            {
                if (m_IntervalList.count(Interval::majorSecond()) > 0)
                {
                    theString = "9";
                    subtract(dominantNinth(), theRestIntervals, theMissingIntervals);
                }
                else
                {
                    theString = "7";
                    subtract(dominantSeventh(), theRestIntervals, theMissingIntervals);
                }
            }
            //if formula contains major seventh (no fifth necessary)
            else if (m_IntervalList.count(Interval::majorSeventh()) > 0)
            {
                if (m_IntervalList.count(Interval::majorSecond()) > 0)
                {
                    theString = "maj9";
                    subtract(majorNinth(), theRestIntervals, theMissingIntervals);
                }
                else
                {
                    theString = "maj7";
                    subtract(majorSeventh(), theRestIntervals, theMissingIntervals);
                }
            }
            //if formula contains major sixth (no fifth necessary)
            else if (m_IntervalList.count(Interval::majorSixth()) > 0)
            {
                theString = "maj6";
                subtract(majorSixth(), theRestIntervals, theMissingIntervals);
            }
            //if formula contains perfect fifth
            else //if (m_IntervalList.count(Interval::perfectFifth()) > 0)
            {
                //major triad
                theString = "maj";
                subtract(major(), theRestIntervals, theMissingIntervals);
            }
        }
        //if formula contains minor third
        else if (m_IntervalList.count(Interval::minorThird()) > 0)
        {
            //if formula contains only diminished fifth
            if (m_IntervalList.count(Interval::diminishedFifth()) > 0 && m_IntervalList.count(Interval::perfectFifth()) == 0)
            {
                if (m_IntervalList.count(Interval::minorSeventh()) > 0)
                {
                    theString = "hdim7";
                    subtract(halfDiminished(), theRestIntervals, theMissingIntervals);
                }
                else if (m_IntervalList.count(Interval::diminishedSeventh()) > 0)
                {
                    theString = "dim7";
                    subtract(diminishedSeventh(), theRestIntervals, theMissingIntervals);
                }
                else
                {
                    //diminished triad
                    theString = "dim";
                    subtract(diminished(), theRestIntervals, theMissingIntervals);
                }
            }
            //if formula contains minor seventh (no fifth necessary)
            else if (m_IntervalList.count(Interval::minorSeventh()) > 0)
            {
                if (m_IntervalList.count(Interval::majorSecond()) > 0)
                {
                    theString = "min9";
                    subtract(minorNinth(), theRestIntervals, theMissingIntervals);
                }
                else
                {
                    theString = "min7";
                    subtract(minorSeventh(), theRestIntervals, theMissingIntervals);
                }
            }
            //if formula contains major seventh (no fifth necessary)
            else if (m_IntervalList.count(Interval::majorSeventh()) > 0)
            {
                theString = "minmaj7";
                subtract(minorMajorSeventh(), theRestIntervals, theMissingIntervals);
            }
            //if formula contains major sixth (no fifth necessary)
            else if (m_IntervalList.count(Interval::majorSixth()) > 0)
            {
                theString = "min6";
                subtract(minorSixth(), theRestIntervals, theMissingIntervals);
            }
            //if the formula contains perfect fifth
            else //if (m_IntervalList.count(Interval::perfectFifth()) > 0)
            {
                //minor triad
                theString = "min";
                subtract(minor(), theRestIntervals, theMissingIntervals);
            }
        }
        //if the formula contains perfect fourth (and no third or major second)
        else if (m_IntervalList.count(Interval::perfectFourth()) > 0 && m_IntervalList.count(Interval::majorSecond()) == 0)
        {
            theString = "sus4";
            subtract(suspendedFourth(), theRestIntervals, theMissingIntervals);
        }
        //if the formula contains major second (and no third or perfect fourth)
        else if (m_IntervalList.count(Interval::majorSecond()) > 0 && m_IntervalList.count(Interval::perfectFourth()) == 0)
        {
            theString = "sus2";
            subtract(suspendedSecond(), theRestIntervals, theMissingIntervals);
        }
        else
        {
            theString = "";
            theRestIntervals = m_IntervalList;
        }
    }
    
    if (!theRestIntervals.empty() || !theMissingIntervals.empty())
    {
        theString += "(";
        if (!theRestIntervals.empty())
        {
            theString += theRestIntervals.begin()->majorDegree();
            for (set<Interval>::const_iterator it = ++theRestIntervals.begin(); it != theRestIntervals.end(); ++it)
            {
                theString += "," + it->majorDegree();
            }
        }
        if (!theMissingIntervals.empty())
        {
            if (!theRestIntervals.empty())
            {
                theString += ",";
            }
            theString += "*" + theMissingIntervals.begin()->majorDegree();
            for (set<Interval>::const_iterator it = ++theMissingIntervals.begin(); it != theMissingIntervals.end(); ++it)
            {
                theString += ",*" + it->majorDegree();
            }
        }
        theString += ")";
    }
	if (this->m_Bass != Interval::undefined())
	{
		theString += "/" + this->m_Bass.majorDegree();
	}
	return theString;
}

//----------------------------------------------------------------------------//
// Non-member stream operators                                                //
//----------------------------------------------------------------------------//
std::ostream& MusOO::operator<<(std::ostream& inOutputStream, const ChordQM& inChord)
{
	inOutputStream << inChord.str();
	return inOutputStream;
}

std::istream& MusOO::operator>>(std::istream& inInputStream, ChordQM& inChord)
{
	string theChordString;
	inInputStream >> theChordString;
	inChord = ChordQM(theChordString);
	return inInputStream;
}

std::istream& MusOO::operator>>(std::istream& inInputStream, ChordTypeQM& outChordType)
{
	std::string theString;
	inInputStream >> theString;
	outChordType = ChordTypeQM(theString);
	return inInputStream;
}

std::ostream& MusOO::operator<<(std::ostream& inOutputStream, const ChordTypeQM& inChordType)
{
	inOutputStream << inChordType.str();
	return inOutputStream;
}

std::ostream& MusOO::operator<<(std::ostream& inOutputStream, const ChordChordino& inChord)
{
	inOutputStream << inChord.str();
	return inOutputStream;
}

std::istream& MusOO::operator>>(std::istream& inInputStream, ChordChordino& inChord)
{
	string theChordString;
	inInputStream >> theChordString;
	inChord = ChordChordino(theChordString);
	return inInputStream;
}
