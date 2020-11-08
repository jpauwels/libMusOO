#ifndef KeyQuaero_h
#define KeyQuaero_h

//============================================================================
/**
 Class representing a key according to the Quaero syntax.
 
 @author	Johan Pauwels
 @date		20130417
 */
//============================================================================
#include "MusOO/KeyAbstract.h"
#include "MusOO/ChromaSolfege.h"
#include "MusOO/ModeQuaero.h"

namespace MusOO
{
class KeyQuaero : public KeyAbstract<KeyQuaero, ChromaSolfege, ModeQuaero>
{
public:

    using KeyAbstract<KeyQuaero, ChromaSolfege, ModeQuaero>::KeyAbstract;
	KeyQuaero(const std::string& inKeyString);

	const std::string str() const;

};

}
#endif	// #ifndef KeyQuaero_h
