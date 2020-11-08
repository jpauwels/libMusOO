#ifndef ChromaLetter_h
#define ChromaLetter_h

//============================================================================
/**
 Class representing a chroma with letter syntax.
 
 @author	Johan Pauwels
 @date		20120720
 */
//============================================================================
#include "MusOO/ChromaAbstract.h"
#include <map>

namespace MusOO
{
class ChromaLetter : public ChromaAbstract<ChromaLetter>
{
public:
	
	using ChromaAbstract<ChromaLetter>::ChromaAbstract;
    ChromaLetter(const std::string& inName);

	const std::string str() const;
	
protected:

	
private:
    static const std::map<char,ptrdiff_t> s_NameToLinePosition;
    static const std::map<ptrdiff_t,char> s_LinePositionToName;
    
};

}
#endif	// #ifndef ChromaLetter_h
