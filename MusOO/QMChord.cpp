//============================================================================
/**
Implementation file for QMChord.h

@author		Johan Pauwels
@date		20090119
*/
//============================================================================

// Includes
#include <stdexcept>
#include <algorithm>
#include <sstream>
#include "QMChord.h"

using std::string;
using std::vector;
using std::map;
using std::pair;
using std::invalid_argument;
using std::istringstream;
using std::ostringstream;
using std::min;
using std::set;


//----------------------------------------------------------------------------//
// QMChord                                                                    //
//----------------------------------------------------------------------------//
QMChord::QMChord()
{
}

QMChord::QMChord(const std::string& inChordString)
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
		size_t theColon = inChordString.find(":");
		size_t theSlash = inChordString.find("/");
		m_Root = Chroma(inChordString.substr(0,min(theColon, theSlash)));
		
		if (theColon != string::npos)
		{
			//explicit type, optional slash
			m_Type = QMChordType(inChordString.substr(theColon+1));
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
				m_Type = QMChordType("maj"+inChordString.substr(theSlash));
			}
		}
	}
}

QMChord::QMChord(const Chord& inChord)
: Chord(inChord)
{
}

QMChord::~QMChord()
{
	// Nothing to do...
}

const std::string QMChord::str() const
{
	string theChordString = m_Root.str();
	if (*this != Chord::silence() && *this != Chord::none() && m_Type != ChordType::major())
	{
		theChordString += ":" + QMChordType(m_Type).str();
	}
	return theChordString;
}

//----------------------------------------------------------------------------//
// ChordinoChord                                                                 //
//----------------------------------------------------------------------------//
ChordinoChord::ChordinoChord()
{
}

ChordinoChord::ChordinoChord(std::string inChordString)
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
			m_Type = QMChordType(inChordString.substr(theTypeStart));
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
				m_Type = QMChordType("maj"+inChordString.substr(theSlash));
			}
		}
	}
}

ChordinoChord::ChordinoChord(const Chord& inChord)
: Chord(inChord)
{
}

ChordinoChord::~ChordinoChord()
{
}

const std::string ChordinoChord::str() const
{
	string theChordString = m_Root.str();
	if (*this != Chord::silence() && *this != Chord::none() && m_Type != ChordType::major())
	{
		theChordString += QMChordType(m_Type).str();
	}
	return theChordString;
}

//----------------------------------------------------------------------------//
// QMChordType                                                                //
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
const map<string,ChordType> QMChordType::s_TypeStringMap(typeStringMap, typeStringMap+28);

QMChordType::QMChordType(std::string inName)
{
	//find borders of base type
	size_t theBaseNameEnd = inName.find_first_of("(/");
	//convert basic type to circle steps formula
	map<string,ChordType>::const_iterator theMapPos = 
		s_TypeStringMap.find(inName.substr(0,theBaseNameEnd));
	if (theMapPos != s_TypeStringMap.end()) {
		*this = theMapPos->second;
	} else {
		throw invalid_argument("Unknown QM chord type " + inName.substr(0,theBaseNameEnd));
	}
	//check for formula modifiers
	size_t theOpenBracket = inName.find("(");
	if (theOpenBracket != string::npos)
	{
		//isolate formula modifiers and parse them
		size_t theCloseBracket = inName.find(")");
		if (theCloseBracket == string::npos)
		{
			throw invalid_argument("No closing bracket present in " + inName);
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

QMChordType::QMChordType()
{
}

QMChordType::QMChordType(const ChordType& inChordType)
: ChordType(inChordType)
{
}

QMChordType::~QMChordType()
{
	// Nothing to do...
}

void QMChordType::parseFormulaModifier(std::string inFormulaModifier)
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

void QMChordType::addNote(const std::string& inDegree)
{
	addInterval(Interval(inDegree));
}

void QMChordType::addBassNote(const std::string& inDegree)
{
	addBass(Interval(inDegree));
}

void QMChordType::replaceNote(const std::string& inToBeReplaced, const std::string& inReplacement)
{
	replaceInterval(Interval(inToBeReplaced), Interval(inReplacement));
}

void QMChordType::deleteNote(const std::string& inDegree)
{
	deleteInterval(Interval(inDegree));
}

const std::string QMChordType::str() const
{
 	string theString;
	QMChordType theChordType(*this);

	for (map<string,ChordType>::const_reverse_iterator theCurType = s_TypeStringMap.rbegin();
		theCurType != s_TypeStringMap.rend(); theCurType++)
	{
		if (theChordType == theCurType->second)
		{
			theString = theCurType->first;
			theChordType = ChordType::none();
			break;
		}
 		if (theChordType.contains(theCurType->second))
 		{
 			theString = theCurType->first;
			theChordType.subtract(theCurType->second);
			break;
 		}
	}
	if (theChordType.cardinality() != 0)
	{
		theString += "(" + theChordType.m_IntervalList.begin()->majorDegree();
		for (set<Interval>::const_iterator it = ++theChordType.m_IntervalList.begin(); it != theChordType.m_IntervalList.end(); ++it)
		{
			theString += "," + it->majorDegree();
		}
		theString += ")";
	}
	if (this->m_Bass != Interval::unison() && this->m_Bass != Interval::undefined())
	{
		theString += "/" + this->m_Bass.majorDegree();
	}
	return theString;
}

std::ostream& operator<<(std::ostream& inOutputStream, const QMChord& inChord)
{
	inOutputStream << inChord.str();
	return inOutputStream;
}

std::istream& operator>>(std::istream& inInputStream, QMChord& inChord)
{
	string theChordString;
	inInputStream >> theChordString;
	inChord = QMChord(theChordString);
	return inInputStream;
}

std::istream& operator>>(std::istream& inInputStream, QMChordType& outChordType)
{
	std::string theString;
	inInputStream >> theString;
	outChordType = QMChordType(theString);
	return inInputStream;
}

std::ostream& operator<<(std::ostream& inOutputStream, const QMChordType& inChordType)
{
	inOutputStream << inChordType.str();
	return inOutputStream;
}

std::ostream& operator<<(std::ostream& inOutputStream, const ChordinoChord& inChord)
{
	inOutputStream << inChord.str();
	return inOutputStream;
}

std::istream& operator>>(std::istream& inInputStream, ChordinoChord& inChord)
{
	string theChordString;
	inInputStream >> theChordString;
	inChord = ChordinoChord(theChordString);
	return inInputStream;
}
