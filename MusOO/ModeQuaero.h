#ifndef ModeQuaero_h
#define ModeQuaero_h

//============================================================================
/**
     Class representing a mode according to the Quaero syntax.
     
     @author	Johan Pauwels
     @date		20130417
 */
//============================================================================
#include "MusOO/ModeAbstract.h"
#include <string>

namespace MusOO
{
class ChromaSolfege;

class ModeQuaero : public ModeAbstract<ModeQuaero>
{
public:
    
    using ModeAbstract<ModeQuaero>::ModeAbstract;
    ModeQuaero(const std::string& inString);
    
    const std::string str() const;
	const std::string str(const ChromaSolfege& inTonicChroma) const;
    
private:
    static const std::map<std::string,ModeQuaero> s_ModeStringMap;
};

}
#endif	// #ifndef ModeQuaero_h
