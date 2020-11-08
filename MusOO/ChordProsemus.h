#ifndef ChordProsemus_h
#define ChordProsemus_h

//============================================================================
/**
	Class representing a chord with Prosemus syntax.

	@author		Johan Pauwels
	@date		20101220
*/
//============================================================================
#include "MusOO/ChordAbstract.h"
#include "MusOO/ChromaLetter.h"
#include "MusOO/ChordTypeProsemus.h"

namespace MusOO
{
class ChordProsemus : public ChordAbstract<ChordProsemus, ChromaLetter, ChordTypeProsemus>
{
public:

    using ChordAbstract<ChordProsemus, ChromaLetter, ChordTypeProsemus>::ChordAbstract;
    ChordProsemus(const std::string& inChordString);

	const std::string str() const;

};

}
#endif	// #ifndef ChordProsemus_h
