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
#include "MusOO/Mode.h"

namespace MusOO
{
class ModeQMUL : public Mode
{
public:
	ModeQMUL();
	ModeQMUL(const Mode& inMode);
	ModeQMUL(const std::string& inString);

	const std::string str() const;

};

std::ostream& operator<<(std::ostream& inOutputStream, const ModeQMUL& inMode);
}
#endif	// #ifndef ModeQMUL_h
