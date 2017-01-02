#ifndef ChromaLetter_h
#define ChromaLetter_h

//============================================================================
/**
 Class representing a chroma with letter syntax.
 
 @author	Johan Pauwels
 @date		20120720
 */
//============================================================================
#include <string>
#include <map>
#include "MusOO/Chroma.h"

namespace MusOO
{
class ChromaLetter : public Chroma
{
public:
	
	/** Default constructor. */
    ChromaLetter();
    ChromaLetter(const std::string& inName, const bool inHasSpelling = true);
	ChromaLetter(const Chroma& inReference, const SimpleInterval& inInterval);
	/** Copy constructor. */
	ChromaLetter(const Chroma& inChroma);
	
	/** Destructor. */
	virtual ~ChromaLetter();
	
	const std::string str() const;
	
protected:

	
private:
    static const std::map<char,ptrdiff_t> s_NameToLinePosition;
    static const std::map<ptrdiff_t,char> s_LinePositionToName;
    
};
    
std::ostream& operator<<(std::ostream& inOutputStream, const ChromaLetter& inChroma);
std::istream& operator>>(std::istream& inInputStream, ChromaLetter& inChroma);
}
#endif	// #ifndef ChromaLetter_h
