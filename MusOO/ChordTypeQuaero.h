#ifndef ChordTypeQuaero_h
#define ChordTypeQuaero_h

//============================================================================
/**
 Class representing a chord type with Quaero syntax.
 
 @author	Johan Pauwels
 @date		20120719
 */
//============================================================================
#include "MusOO/ChordTypeAbstract.h"
#include <string>

namespace MusOO
{
class ChromaSolfege;
    
class ChordTypeQuaero : public ChordTypeAbstract<ChordTypeQuaero>
{
public:
    
    friend class ModeQuaero; // to access getConstrainedString() in ModeQuaero::str
	
	using ChordTypeAbstract<ChordTypeQuaero>::ChordTypeAbstract;
	ChordTypeQuaero(std::string inName);

    const std::string str() const;
	const std::string str(const ChromaSolfege& inRootChroma) const;
	
private:
	
	static const std::map<std::string,ChordTypeQuaero> s_TypeStringMap;
	static const std::string getConstrainedString(const ChromaSolfege& inChroma);
	
};

}
#endif	// #ifndef ChordTypeQuaero_h
