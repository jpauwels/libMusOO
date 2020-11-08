#ifndef ChordQMUL_h
#define ChordQMUL_h

//============================================================================
	/**
	Class representing a chord with syntax defined by Harte et al.

	@author		Johan Pauwels
	@date		20090119
*/
//============================================================================
#include "MusOO/ChordAbstract.h"
#include "MusOO/ChromaLetter.h"
#include "MusOO/ChordTypeQMUL.h"

namespace MusOO
{
class ChordQMUL : public ChordAbstract<ChordQMUL, ChromaLetter, ChordTypeQMUL>
{
public:

    using ChordAbstract<ChordQMUL, ChromaLetter, ChordTypeQMUL>::ChordAbstract;
    ChordQMUL(const std::string& inChordString);

	const std::string str() const;

};

}
#endif	// #ifndef ChordQMUL_h
