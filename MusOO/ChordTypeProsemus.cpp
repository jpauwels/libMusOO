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

using std::pair;
using namespace MusOO;

static const pair<const std::string,const ChordTypeProsemus> typeStringMap[] =
{
	//triads
	pair<const std::string,const ChordTypeProsemus>("",ChordTypeProsemus::major()),
	pair<const std::string,const ChordTypeProsemus>("m",ChordTypeProsemus::minor()),
	pair<const std::string,const ChordTypeProsemus>("dim",ChordTypeProsemus::diminished()),
	pair<const std::string,const ChordTypeProsemus>("aug",ChordTypeProsemus::augmented()),
	pair<const std::string,const ChordTypeProsemus>("sus",ChordTypeProsemus::suspendedFourth()),
	pair<const std::string,const ChordTypeProsemus>("4",ChordTypeProsemus::suspendedFourth()),
	pair<const std::string,const ChordTypeProsemus>("(b5)",ChordTypeProsemus::majorFlatFifth()),
	pair<const std::string,const ChordTypeProsemus>("m(+5)",ChordTypeProsemus::minorSharpFifth()),
	pair<const std::string,const ChordTypeProsemus>("m#5",ChordTypeProsemus::minorSharpFifth()),
	//tetrads
	pair<const std::string,const ChordTypeProsemus>("maj7",ChordTypeProsemus::majorSeventh()),
	pair<const std::string,const ChordTypeProsemus>("m7",ChordTypeProsemus::minorSeventh()),
	pair<const std::string,const ChordTypeProsemus>("7",ChordTypeProsemus::dominantSeventh()),
	pair<const std::string,const ChordTypeProsemus>("m7b5",ChordTypeProsemus::halfDiminished()),
	pair<const std::string,const ChordTypeProsemus>("7+",ChordTypeProsemus::augmentedSeventh()),
	pair<const std::string,const ChordTypeProsemus>("m6",ChordTypeProsemus::minorSixth()),
    //pentads
	pair<const std::string,const ChordTypeProsemus>("7#9",ChordTypeProsemus::dominantSeventh().addInterval(SimpleInterval::augmentedSecond())),
	pair<const std::string,const ChordTypeProsemus>("7#11",ChordTypeProsemus::dominantSeventh().addInterval(SimpleInterval::augmentedFourth())),
	pair<const std::string,const ChordTypeProsemus>("7b5#9",ChordTypeProsemus::majorFlatFifth().
        addInterval(SimpleInterval::minorSeventh()).addInterval(SimpleInterval::augmentedSecond())),
	pair<const std::string,const ChordTypeProsemus>("7susb9",ChordTypeProsemus::suspendedFourth().
                           addInterval(SimpleInterval::minorSeventh()).addInterval(SimpleInterval::minorSecond())),
	pair<const std::string,const ChordTypeProsemus>("maj7#5",ChordTypeProsemus::majorSeventh().
                           replaceInterval(SimpleInterval::perfectFifth(),SimpleInterval::augmentedFifth())),
    //hexads
	pair<const std::string,const ChordTypeProsemus>("7b9#11",ChordTypeProsemus::dominantSeventh().
		addInterval(SimpleInterval::minorSecond()).addInterval(SimpleInterval::augmentedFourth())),
	pair<const std::string,const ChordTypeProsemus>("11",ChordTypeProsemus::dominantEleventh()),
	pair<const std::string,const ChordTypeProsemus>("9#11",ChordTypeProsemus::dominantNinth().addInterval(SimpleInterval::augmentedFourth())),
	pair<const std::string,const ChordTypeProsemus>("maj9#11",ChordTypeProsemus::majorNinth().addInterval(SimpleInterval::augmentedFourth())),
    //heptads
	pair<const std::string,const ChordTypeProsemus>("13#11",ChordTypeProsemus::dominantThirteenth().
		replaceInterval(SimpleInterval::perfectFourth(),SimpleInterval::augmentedFourth())),
	pair<const std::string,const ChordTypeProsemus>("13sus",ChordTypeProsemus::dominantThirteenth().
		replaceInterval(SimpleInterval::majorThird(),SimpleInterval::perfectFourth())),
	pair<const std::string,const ChordTypeProsemus>("maj13",ChordTypeProsemus::majorThirteenth()),
    //not clear
	pair<const std::string,const ChordTypeProsemus>("whole",ChordTypeProsemus::rootOnly()),
	pair<const std::string,const ChordTypeProsemus>("7alt",ChordTypeProsemus::rootOnly()),
	pair<const std::string,const ChordTypeProsemus>("13alt",ChordTypeProsemus::rootOnly())
};
const std::map<const std::string,const ChordTypeProsemus> ChordTypeProsemus::s_TypeStringMap(typeStringMap, typeStringMap+30);

ChordTypeProsemus::ChordTypeProsemus(std::string inName)
{
	const std::map<const std::string,const ChordTypeProsemus>::const_iterator theMapPos = s_TypeStringMap.find(inName);
	if (theMapPos != s_TypeStringMap.end())
	{
		*this = theMapPos->second;
	}
	else
	{
		throw std::invalid_argument("Unknown Prosemus chord type '" + inName + "'");
	}
}

const std::string ChordTypeProsemus::str() const
{
	for (std::map<const std::string,const ChordTypeProsemus>::const_iterator theCurType = s_TypeStringMap.begin();
		theCurType != s_TypeStringMap.end(); theCurType++)
	{
		if (*this == theCurType->second)
		{
			return theCurType->first;
		}
	}
	throw std::logic_error("Invalid Prosemus chord type");
}
