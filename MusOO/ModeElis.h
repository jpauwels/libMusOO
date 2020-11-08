#ifndef ModeElis_h
#define ModeElis_h

//============================================================================
/**
	Class representing a mode according to the Elis syntax.

	@author		Johan Pauwels
	@date		20100330
*/
//============================================================================
#include "MusOO/ModeAbstract.h"

namespace MusOO
{
class ModeElis : public ModeAbstract<ModeElis>
{
public:
    
    using ModeAbstract<ModeElis>::ModeAbstract;
    ModeElis(const std::string& inString);

	const std::string str() const;

};

}
#endif	// #ifndef ModeElis_h
