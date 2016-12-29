//============================================================================
/**
	Implementation file for ChordTypeProsemus.h

	@author		Johan Pauwels
	@date		20101220
*/
//============================================================================

// Includes
#include <map>
#include <stdexcept>
#include "MusOO/ChordTypeProsemus.h"

using std::map;
using std::pair;
using std::string;
using namespace MusOO;

static const pair<string,ChordType> typeStringMap[] =
{
	//triads
	pair<string,ChordType>("",ChordType::major()),
	pair<string,ChordType>("m",ChordType::minor()),
	pair<string,ChordType>("dim",ChordType::diminished()),
	pair<string,ChordType>("aug",ChordType::augmented()),
	pair<string,ChordType>("sus",ChordType::suspendedFourth()),
	pair<string,ChordType>("4",ChordType::suspendedFourth()),
	pair<string,ChordType>("(b5)",ChordType::majorFlatFifth()),
	pair<string,ChordType>("m(+5)",ChordType::minorSharpFifth()),
	pair<string,ChordType>("m#5",ChordType::minorSharpFifth()),
	//tetrads
	pair<string,ChordType>("maj7",ChordType::majorSeventh()),
	pair<string,ChordType>("m7",ChordType::minorSeventh()),
	pair<string,ChordType>("7",ChordType::dominantSeventh()),
	pair<string,ChordType>("m7b5",ChordType::halfDiminished()),
	pair<string,ChordType>("7+",ChordType::augmentedSeventh()),
	pair<string,ChordType>("m6",ChordType::minorSixth()),
    //pentads
	pair<string,ChordType>("7#9",ChordType::dominantSeventh().addInterval(Interval::augmentedNinth())),
	pair<string,ChordType>("7#11",ChordType::dominantSeventh().addInterval(Interval::augmentedEleventh())),
	pair<string,ChordType>("7b5#9",ChordType::majorFlatFifth().
        addInterval(Interval::minorSeventh()).addInterval(Interval::augmentedNinth())),
	pair<string,ChordType>("7susb9",ChordType::suspendedFourth().
                           addInterval(Interval::minorSeventh()).addInterval(Interval::minorNinth())),
	pair<string,ChordType>("maj7#5",ChordType::majorSeventh().
                           replaceInterval(Interval::perfectFifth(),Interval::augmentedFifth())),
    //hexads
	pair<string,ChordType>("7b9#11",ChordType::dominantSeventh().
		addInterval(Interval::minorNinth()).addInterval(Interval::augmentedEleventh())),
	pair<string,ChordType>("11",ChordType::dominantEleventh()),
	pair<string,ChordType>("9#11",ChordType::dominantNinth().addInterval(Interval::augmentedEleventh())),
	pair<string,ChordType>("maj9#11",ChordType::majorNinth().addInterval(Interval::augmentedEleventh())),
    //heptads
	pair<string,ChordType>("13#11",ChordType::dominantThirteenth().
		replaceInterval(Interval::perfectEleventh(),Interval::augmentedEleventh())),
	pair<string,ChordType>("13sus",ChordType::dominantThirteenth().
		replaceInterval(Interval::majorThird(),Interval::perfectFourth())),
	pair<string,ChordType>("maj13",ChordType::majorThirteenth()),
    //not clear
	pair<string,ChordType>("whole",ChordType::rootOnly()),
	pair<string,ChordType>("7alt",ChordType::rootOnly()),
	pair<string,ChordType>("13alt",ChordType::rootOnly())
};
const map<string,ChordType> ChordTypeProsemus::s_TypeStringMap(typeStringMap, typeStringMap+30);

ChordTypeProsemus::ChordTypeProsemus()
{
}

ChordTypeProsemus::ChordTypeProsemus(std::string inName)
{
	const map<string,ChordType>::const_iterator theMapPos = s_TypeStringMap.find(inName);
	if (theMapPos != s_TypeStringMap.end())
	{
		*this = theMapPos->second;
	}
	else
	{
		throw std::invalid_argument("Unknown Prosemus chord type '" + inName + "'");
	}
}

ChordTypeProsemus::ChordTypeProsemus(const ChordType& inChordType)
: ChordType(inChordType)
{
}

ChordTypeProsemus::~ChordTypeProsemus()
{
}

const std::string ChordTypeProsemus::str() const
{
	for (map<string,ChordType>::const_iterator theCurType = s_TypeStringMap.begin();
		theCurType != s_TypeStringMap.end(); theCurType++)
	{
		if (*this == theCurType->second)
		{
			return theCurType->first;
		}
	}
	throw std::logic_error("Invalid Prosemus chord type");
}
