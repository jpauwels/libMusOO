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
#include "MusOO/RelativeChord.h"

namespace MusOO
{
class RelativeChordQMUL : public RelativeChord
{
public:
	RelativeChordQMUL();
	RelativeChordQMUL(const std::string& inString, const Mode& inMode);
	RelativeChordQMUL(const RelativeChord& inRelativeChord);

	//assignment operator
// 		RelativeChordQMUL& operator=(const RelativeChord& inRelativeChord);
    
    //const std::string str() const;
    const std::string asDegree(const Mode& inMode) const;
};
}
#endif	// #ifndef RelativeChordQMUL_h
