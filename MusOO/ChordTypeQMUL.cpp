//============================================================================
/**
Implementation file for ChordTypeQMUL.h

@author		Johan Pauwels
@date		20090119
*/
//============================================================================

// Includes
#include <stdexcept>
#include <algorithm>
#include <sstream>
#include "MusOO/ChordTypeQMUL.h"

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
const map<string,ChordType> ChordTypeQMUL::s_TypeStringMap(typeStringMap, typeStringMap+28);

ChordTypeQMUL::ChordTypeQMUL(std::string inName)
{
	//find borders of base type
	size_t theBaseNameEnd = inName.find_first_of("(/");
	//convert basic type to circle steps formula
	map<string,ChordType>::const_iterator theMapPos = 
		s_TypeStringMap.find(inName.substr(0,theBaseNameEnd));
	if (theMapPos != s_TypeStringMap.end()) {
		*this = theMapPos->second;
	} else {
		throw invalid_argument("Unknown QMUL chord type '" + inName.substr(0,theBaseNameEnd) + "'");
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

ChordTypeQMUL::ChordTypeQMUL()
{
}

ChordTypeQMUL::ChordTypeQMUL(const ChordType& inChordType)
: ChordType(inChordType)
{
}

ChordTypeQMUL::~ChordTypeQMUL()
{
	// Nothing to do...
}

void ChordTypeQMUL::parseFormulaModifier(std::string inFormulaModifier)
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

void ChordTypeQMUL::addNote(const std::string& inDegree)
{
	addInterval(Interval(inDegree));
}

void ChordTypeQMUL::addBassNote(const std::string& inDegree)
{
	addBass(SimpleInterval(inDegree));
}

void ChordTypeQMUL::replaceNote(const std::string& inToBeReplaced, const std::string& inReplacement)
{
	replaceInterval(Interval(inToBeReplaced), Interval(inReplacement));
}

void ChordTypeQMUL::deleteNote(const std::string& inDegree)
{
	deleteInterval(Interval(inDegree));
}

const std::string ChordTypeQMUL::str() const
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
        if (m_set.count(Interval::majorThird()) > 0)
        {
            //if formula contains only augmented fifth
            if (m_set.count(Interval::augmentedFifth()) > 0 && m_set.count(Interval::perfectFifth()) == 0)
            {
                theString = "aug";
                subtract(augmented(), theRestIntervals, theMissingIntervals);
            }
            //if formula contains minor seventh (no fifth necessary)
            else if (m_set.count(Interval::minorSeventh()) > 0)
            {
                if (m_set.count(Interval::majorSecond()) > 0)
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
            else if (m_set.count(Interval::majorSeventh()) > 0)
            {
                if (m_set.count(Interval::majorSecond()) > 0)
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
            else if (m_set.count(Interval::majorSixth()) > 0)
            {
                theString = "maj6";
                subtract(majorSixth(), theRestIntervals, theMissingIntervals);
            }
            //if formula contains perfect fifth
            else //if (m_set.count(Interval::perfectFifth()) > 0)
            {
                //major triad
                theString = "maj";
                subtract(major(), theRestIntervals, theMissingIntervals);
            }
        }
        //if formula contains minor third
        else if (m_set.count(Interval::minorThird()) > 0)
        {
            //if formula contains only diminished fifth
            if (m_set.count(Interval::diminishedFifth()) > 0 && m_set.count(Interval::perfectFifth()) == 0)
            {
                if (m_set.count(Interval::minorSeventh()) > 0)
                {
                    theString = "hdim7";
                    subtract(halfDiminished(), theRestIntervals, theMissingIntervals);
                }
                else if (m_set.count(Interval::diminishedSeventh()) > 0)
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
            else if (m_set.count(Interval::minorSeventh()) > 0)
            {
                if (m_set.count(Interval::majorSecond()) > 0)
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
            else if (m_set.count(Interval::majorSeventh()) > 0)
            {
                theString = "minmaj7";
                subtract(minorMajorSeventh(), theRestIntervals, theMissingIntervals);
            }
            //if formula contains major sixth (no fifth necessary)
            else if (m_set.count(Interval::majorSixth()) > 0)
            {
                theString = "min6";
                subtract(minorSixth(), theRestIntervals, theMissingIntervals);
            }
            //if the formula contains perfect fifth
            else //if (m_set.count(Interval::perfectFifth()) > 0)
            {
                //minor triad
                theString = "min";
                subtract(minor(), theRestIntervals, theMissingIntervals);
            }
        }
        //if the formula contains perfect fourth (and no third or major second)
        else if (m_set.count(Interval::perfectFourth()) > 0 && m_set.count(Interval::majorSecond()) == 0)
        {
            theString = "sus4";
            subtract(suspendedFourth(), theRestIntervals, theMissingIntervals);
        }
        //if the formula contains major second (and no third or perfect fourth)
        else if (m_set.count(Interval::majorSecond()) > 0 && m_set.count(Interval::perfectFourth()) == 0)
        {
            theString = "sus2";
            subtract(suspendedSecond(), theRestIntervals, theMissingIntervals);
        }
        else
        {
            theString = "";
            theRestIntervals = m_set;
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
	if (this->m_Bass != SimpleInterval::undefined())
	{
		theString += "/" + this->m_Bass.majorDegree();
	}
	return theString;
}

std::istream& MusOO::operator>>(std::istream& inInputStream, ChordTypeQMUL& outChordType)
{
	std::string theString;
	inInputStream >> theString;
	outChordType = ChordTypeQMUL(theString);
	return inInputStream;
}

std::ostream& MusOO::operator<<(std::ostream& inOutputStream, const ChordTypeQMUL& inChordType)
{
	inOutputStream << inChordType.str();
	return inOutputStream;
}
