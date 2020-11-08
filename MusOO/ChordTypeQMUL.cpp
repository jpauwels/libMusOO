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
#include "MusOO/ComplexInterval.h"

using std::pair;
using std::min;
using std::set;
using namespace MusOO;


static const pair<std::string,ChordTypeQMUL> typeStringMap[] = {
	pair<std::string,ChordTypeQMUL>("",ChordTypeQMUL::none()),
	//triads
	pair<std::string,ChordTypeQMUL>("maj",ChordTypeQMUL::major()),
	pair<std::string,ChordTypeQMUL>("min",ChordTypeQMUL::minor()),
	pair<std::string,ChordTypeQMUL>("dim",ChordTypeQMUL::diminished()),
	pair<std::string,ChordTypeQMUL>("aug",ChordTypeQMUL::augmented()),
	//seventh chords
	pair<std::string,ChordTypeQMUL>("maj7",ChordTypeQMUL::majorSeventh()),
	pair<std::string,ChordTypeQMUL>("min7",ChordTypeQMUL::minorSeventh()),
	pair<std::string,ChordTypeQMUL>("7",ChordTypeQMUL::dominantSeventh()),
	pair<std::string,ChordTypeQMUL>("dim7",ChordTypeQMUL::diminishedSeventh()),
	pair<std::string,ChordTypeQMUL>("hdim7",ChordTypeQMUL::halfDiminished()),
	pair<std::string,ChordTypeQMUL>("minmaj7",ChordTypeQMUL::minorMajorSeventh()),
	//sixth chords
	pair<std::string,ChordTypeQMUL>("maj6",ChordTypeQMUL::majorSixth()),
	pair<std::string,ChordTypeQMUL>("min6",ChordTypeQMUL::minorSixth()),
	//extended chords
	pair<std::string,ChordTypeQMUL>("9",ChordTypeQMUL::dominantNinth()),
	pair<std::string,ChordTypeQMUL>("maj9",ChordTypeQMUL::majorNinth()),
	pair<std::string,ChordTypeQMUL>("min9",ChordTypeQMUL::minorNinth()),
	//suspended chords
	pair<std::string,ChordTypeQMUL>("sus4",ChordTypeQMUL::suspendedFourth()),
	//additions Rik
	pair<std::string,ChordTypeQMUL>("sus2",ChordTypeQMUL::suspendedSecond()),
	pair<std::string,ChordTypeQMUL>("7sus4",ChordTypeQMUL::suspendedFourthSeventh()),
	pair<std::string,ChordTypeQMUL>("aug7",ChordTypeQMUL::augmentedSeventh()),
    //billboard additions
    pair<std::string,ChordTypeQMUL>("1",ChordTypeQMUL::rootOnly()),
    pair<std::string,ChordTypeQMUL>("5",ChordTypeQMUL::power()),
    pair<std::string,ChordTypeQMUL>("maj11",ChordTypeQMUL::majorEleventh()),
    pair<std::string,ChordTypeQMUL>("11",ChordTypeQMUL::dominantEleventh()),
    pair<std::string,ChordTypeQMUL>("min11",ChordTypeQMUL::minorEleventh()),
    pair<std::string,ChordTypeQMUL>("maj13",ChordTypeQMUL::majorThirteenth()),
    pair<std::string,ChordTypeQMUL>("13",ChordTypeQMUL::dominantThirteenth()),
    pair<std::string,ChordTypeQMUL>("min13",ChordTypeQMUL::minorThirteenth())};
const std::map<std::string,ChordTypeQMUL> ChordTypeQMUL::s_TypeStringMap(typeStringMap, typeStringMap+28);

ChordTypeQMUL::ChordTypeQMUL(std::string inName)
{
	//find borders of base type
	size_t theBaseNameEnd = inName.find_first_of("(/");
	//convert basic type to circle steps formula
	std::map<std::string,ChordTypeQMUL>::const_iterator theMapPos =
		s_TypeStringMap.find(inName.substr(0,theBaseNameEnd));
	if (theMapPos != s_TypeStringMap.end()) {
		*this = theMapPos->second;
	} else {
		throw std::invalid_argument("Unknown QMUL chord type '" + inName.substr(0,theBaseNameEnd) + "'");
	}
	//check for formula modifiers
	size_t theOpenBracket = inName.find("(");
	if (theOpenBracket != std::string::npos)
	{
		//isolate formula modifiers and parse them
		size_t theCloseBracket = inName.find(")");
		if (theCloseBracket == std::string::npos)
		{
			throw std::invalid_argument("No closing bracket present in '" + inName + "'");
		}
		std::string theFormulaModifiers = inName.substr(theOpenBracket+1,theCloseBracket-theOpenBracket-1);
		size_t theComma = theFormulaModifiers.find(",");
		while (theComma != std::string::npos)
		{
			parseFormulaModifier(theFormulaModifiers.substr(0,theComma));
			theFormulaModifiers = theFormulaModifiers.substr(theComma+1,std::string::npos);
			theComma = theFormulaModifiers.find(",");
		}
		parseFormulaModifier(theFormulaModifiers);
	}
	//check if there is a bass note after a forward slash
	size_t theSlash = inName.find("/");
    if (theSlash == 0)
    {
        *this = ChordTypeQMUL::major();
    }
	if (theSlash != std::string::npos)
	{
		addBassNote(inName.substr(theSlash+1));
	}
}

void ChordTypeQMUL::parseFormulaModifier(std::string inFormulaModifier)
{
	if (!inFormulaModifier.substr(0,1).compare("*"))
	{
		deleteNote(inFormulaModifier.substr(1,std::string::npos));
	}
	else
	{
		addNote(inFormulaModifier);
	}
}

void ChordTypeQMUL::addNote(const std::string& inDegree)
{
	*this = addInterval(ComplexInterval(inDegree).simpleInterval());
}

void ChordTypeQMUL::addBassNote(const std::string& inDegree)
{
	*this = addBass(ComplexInterval(inDegree).simpleInterval());
}

void ChordTypeQMUL::replaceNote(const std::string& inToBeReplaced, const std::string& inReplacement)
{
	*this = replaceInterval(ComplexInterval(inToBeReplaced).simpleInterval(), ComplexInterval(inReplacement).simpleInterval());
}

void ChordTypeQMUL::deleteNote(const std::string& inDegree)
{
	*this = deleteInterval(ComplexInterval(inDegree).simpleInterval());
}

const std::string ChordTypeQMUL::str() const
{
 	std::string theString;
    std::set<SimpleInterval> theRestIntervals;
    std::set<SimpleInterval> theMissingIntervals;

    if (*this == ChordTypeQMUL::none())
	{
		return "";
	}
	else
    {
        //if the formula contains major third
        if (m_set.count(SimpleInterval::majorThird()) > 0)
        {
            //if formula contains only augmented fifth
            if (m_set.count(SimpleInterval::augmentedFifth()) > 0 && m_set.count(SimpleInterval::perfectFifth()) == 0)
            {
                theString = "aug";
                subtract(augmented(), theRestIntervals, theMissingIntervals);
            }
            //if formula contains minor seventh (no fifth necessary)
            else if (m_set.count(SimpleInterval::minorSeventh()) > 0)
            {
                if (m_set.count(SimpleInterval::majorSecond()) > 0)
                {
                    if (m_set.count(SimpleInterval::perfectFourth()) > 0)
                    {
                        if (m_set.count(SimpleInterval::majorSixth()) > 0)
                        {
                            theString = "13";
                            subtract(dominantThirteenth(), theRestIntervals, theMissingIntervals);
                        }
                        else
                        {
                            theString = "11";
                            subtract(dominantEleventh(), theRestIntervals, theMissingIntervals);
                        }
                    }
                    else
                    {
                        theString = "9";
                        subtract(dominantNinth(), theRestIntervals, theMissingIntervals);
                    }
                }
                else
                {
                    theString = "7";
                    subtract(dominantSeventh(), theRestIntervals, theMissingIntervals);
                }
            }
            //if formula contains major seventh (no fifth necessary)
            else if (m_set.count(SimpleInterval::majorSeventh()) > 0)
            {
                if (m_set.count(SimpleInterval::majorSecond()) > 0)
                {
                    if (m_set.count(SimpleInterval::perfectFourth()) > 0)
                    {
                        if (m_set.count(SimpleInterval::majorSixth()) > 0)
                        {
                            theString = "maj13";
                            subtract(majorThirteenth(), theRestIntervals, theMissingIntervals);
                        }
                        else
                        {
                            theString = "maj11";
                            subtract(majorEleventh(), theRestIntervals, theMissingIntervals);
                        }
                    }
                    else
                    {
                        theString = "maj9";
                        subtract(majorNinth(), theRestIntervals, theMissingIntervals);
                    }
                }
                else
                {
                    theString = "maj7";
                    subtract(majorSeventh(), theRestIntervals, theMissingIntervals);
                }
            }
            //if formula contains major sixth (no fifth necessary)
            else if (m_set.count(SimpleInterval::majorSixth()) > 0)
            {
                theString = "maj6";
                subtract(majorSixth(), theRestIntervals, theMissingIntervals);
            }
            //if formula contains perfect fifth
            else //if (m_set.count(SimpleInterval::perfectFifth()) > 0)
            {
                //major triad
                theString = "maj";
                subtract(major(), theRestIntervals, theMissingIntervals);
            }
        }
        //if formula contains minor third
        else if (m_set.count(SimpleInterval::minorThird()) > 0)
        {
            //if formula contains only diminished fifth
            if (m_set.count(SimpleInterval::diminishedFifth()) > 0 && m_set.count(SimpleInterval::perfectFifth()) == 0)
            {
                if (m_set.count(SimpleInterval::minorSeventh()) > 0)
                {
                    theString = "hdim7";
                    subtract(halfDiminished(), theRestIntervals, theMissingIntervals);
                }
                else if (m_set.count(SimpleInterval::diminishedSeventh()) > 0)
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
            else if (m_set.count(SimpleInterval::minorSeventh()) > 0)
            {
                if (m_set.count(SimpleInterval::majorSecond()) > 0)
                {
                    if (m_set.count(SimpleInterval::perfectFourth()) > 0)
                    {
                        if (m_set.count(SimpleInterval::majorSixth()) > 0)
                        {
                            theString = "min13";
                            subtract(minorThirteenth(), theRestIntervals, theMissingIntervals);
                        }
                        else
                        {
                            theString = "min11";
                            subtract(minorEleventh(), theRestIntervals, theMissingIntervals);
                        }
                    }
                    else
                    {
                        theString = "min9";
                        subtract(minorNinth(), theRestIntervals, theMissingIntervals);
                    }
                }
                else
                {
                    theString = "min7";
                    subtract(minorSeventh(), theRestIntervals, theMissingIntervals);
                }
            }
            //if formula contains major seventh (no fifth necessary)
            else if (m_set.count(SimpleInterval::majorSeventh()) > 0)
            {
                theString = "minmaj7";
                subtract(minorMajorSeventh(), theRestIntervals, theMissingIntervals);
            }
            //if formula contains major sixth (no fifth necessary)
            else if (m_set.count(SimpleInterval::majorSixth()) > 0)
            {
                theString = "min6";
                subtract(minorSixth(), theRestIntervals, theMissingIntervals);
            }
            //if the formula contains perfect fifth
            else //if (m_set.count(SimpleInterval::perfectFifth()) > 0)
            {
                //minor triad
                theString = "min";
                subtract(minor(), theRestIntervals, theMissingIntervals);
            }
        }
        //if the formula contains perfect fourth (and no third or major second)
        else if (m_set.count(SimpleInterval::perfectFourth()) > 0 && m_set.count(SimpleInterval::majorSecond()) == 0)
        {
            theString = "sus4";
            subtract(suspendedFourth(), theRestIntervals, theMissingIntervals);
        }
        //if the formula contains major second (and no third or perfect fourth)
        else if (m_set.count(SimpleInterval::majorSecond()) > 0 && m_set.count(SimpleInterval::perfectFourth()) == 0)
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
            theString += autoVoicing(*(theRestIntervals.begin())).majorDegreeString();
            for (set<SimpleInterval>::const_iterator it = ++theRestIntervals.begin(); it != theRestIntervals.end(); ++it)
            {
                theString += "," + autoVoicing(*it).majorDegreeString();
            }
        }
        if (!theMissingIntervals.empty())
        {
            if (!theRestIntervals.empty())
            {
                theString += ",";
            }
            theString += "*" + theMissingIntervals.begin()->majorDegreeString();
            for (set<SimpleInterval>::const_iterator it = ++theMissingIntervals.begin(); it != theMissingIntervals.end(); ++it)
            {
                theString += ",*" + it->majorDegreeString();
            }
        }
        theString += ")";
    }
	if (this->m_Bass != SimpleInterval::undefined())
	{
		theString += "/" + this->m_Bass.majorDegreeString();
	}
	return theString;
}
