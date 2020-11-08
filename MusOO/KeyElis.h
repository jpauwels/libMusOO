#ifndef KeyElis_h
#define KeyElis_h

//============================================================================
/**
	Class representing a key according to the Elis syntax.

	@author		Johan Pauwels
	@date		20100330
*/
//============================================================================
#include "MusOO/KeyAbstract.h"
#include "MusOO/ChromaLetter.h"
#include "MusOO/ModeElis.h"

namespace MusOO
{
class KeyElis : public KeyAbstract<KeyElis, ChromaLetter, ModeElis>
{
public:

    using KeyAbstract<KeyElis, ChromaLetter, ModeElis>::KeyAbstract;
	KeyElis(const std::string& inKeyString);

	const std::string str() const;

};

}
#endif	// #ifndef KeyElis_h
