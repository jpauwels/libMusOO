#ifndef ModeElis_h
#define ModeElis_h

//============================================================================
/**
	Class representing a mode according to the Elis syntax.

	@author		Johan Pauwels
	@date		20100330
*/
//============================================================================
#include "MusOO/Mode.h"

namespace MusOO
{
class ModeElis : public Mode
{
public:

	ModeElis();
	ModeElis(const Mode& inMode);
	ModeElis(const std::string& inString);

	const std::string str() const;

};

std::ostream& operator<<(std::ostream& inOutputStream, const ModeElis& inMode);
}
#endif	// #ifndef ModeElis_h
