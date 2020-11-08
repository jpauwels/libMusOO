#ifndef RelativeChordQMUL_h
#define RelativeChordQMUL_h

//============================================================================
/**
	Class representing a relative chord with syntax inspired by the chord syntax
    of Queen Mary University of London.

	@author		Johan Pauwels
	@date		20101222
*/
//============================================================================
#include "MusOO/RelativeChordAbstract.h"
#include "MusOO/ChordTypeQMUL.h"
#include "MusOO/ModeQMUL.h"

namespace MusOO
{
class RelativeChordQMUL : public RelativeChordAbstract<RelativeChordQMUL, ChordTypeQMUL>
{
public:
    
    using RelativeChordAbstract<RelativeChordQMUL, ChordTypeQMUL>::RelativeChordAbstract;
	RelativeChordQMUL(const std::string& inString, const ModeQMUL& inMode);

    const std::string str() const;
    const std::string asDegree(const ModeQMUL& inMode) const;
};
}
#endif	// #ifndef RelativeChordQMUL_h
