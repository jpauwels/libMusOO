#ifndef ChordChordino_h
#define ChordChordino_h

//============================================================================
	/**
	Class representing a chord with syntax as used by the Chordino Vamp plugin

	@author		Johan Pauwels
	@date		20090119
*/
//============================================================================
#include "MusOO/ChordAbstract.h"
#include "MusOO/ChromaLetter.h"
#include "MusOO/ChordTypeQMUL.h"

namespace MusOO
{
class ChordChordino : public ChordAbstract<ChordChordino, ChromaLetter, ChordTypeQMUL>
{
public:

    using ChordAbstract<ChordChordino, ChromaLetter, ChordTypeQMUL>::ChordAbstract;
    ChordChordino(std::string inChordString);

	const std::string str() const;

};

}
#endif	// #ifndef ChordChordino_h
