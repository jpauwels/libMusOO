#ifndef ModeQMUL_h
#define ModeQMUL_h

//============================================================================
/**
	Class representing a key according to the Queen Mary, University of London
	syntax.

	@author		Johan Pauwels
	@date		20100330
*/
//============================================================================
#include "MusOO/ModeAbstract.h"

namespace MusOO
{
class ModeQMUL : public ModeAbstract<ModeQMUL>
{
public:
    
    using ModeAbstract<ModeQMUL>::ModeAbstract;
    ModeQMUL(const std::string& inString);
    
	const std::string str() const;

};

}
#endif	// #ifndef ModeQMUL_h
