#ifndef ModeQuaero_h
#define ModeQuaero_h

//============================================================================
/**
     Class representing a mode according to the Quaero syntax.
     
     @author	Johan Pauwels
     @date		20130417
 */
//============================================================================
#include "MusOO/Mode.h"
#include "MusOO/Chroma.h"

namespace MusOO
{
class ModeQuaero : public Mode
{
public:
	ModeQuaero();
	ModeQuaero(const Mode& inMode);
	ModeQuaero(const std::string& inString);
    
	const std::string str(const Chroma& inTonicChroma = Chroma::undefined()) const;
    
private:
    static const std::map<std::string,Mode> s_ModeStringMap;
};

std::ostream& operator<<(std::ostream& inOutputStream, const ModeQuaero& inMode);
}
#endif	// #ifndef ModeQuaero_h
