#ifndef KeyQMUL_h
#define KeyQMUL_h

//============================================================================
/**
	Class representing a key with syntax inspired by the chord syntax of
    Queen Mary University of London.

	@author		Johan Pauwels
	@date		20100330
*/
//============================================================================
#include "MusOO/KeyAbstract.h"
#include "MusOO/ChromaLetter.h"
#include "MusOO/ModeQMUL.h"

namespace MusOO
{
class KeyQMUL : public KeyAbstract<KeyQMUL, ChromaLetter, ModeQMUL>
{
public:

    using KeyAbstract<KeyQMUL, ChromaLetter, ModeQMUL>::KeyAbstract;
	KeyQMUL(std::string inKeyString);

	const std::string str() const;

};

}
#endif	// #ifndef KeyQMUL_h
