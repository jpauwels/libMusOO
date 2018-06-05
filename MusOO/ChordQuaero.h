#ifndef ChordQuaero_h
#define ChordQuaero_h

//============================================================================
/**
 Class representing a chord with Quaero syntax.
 
 @author	Johan Pauwels
 @date		20120719
 */
//============================================================================
#include <string>
#include "MusOO/ChordAbstract.h"

namespace MusOO
{
class ChordQuaero : public ChordAbstract
{
public:
    
    friend class KeyQuaero; // to access trimRight() in KeyQuaero::KeyQuaero
	
	/** Default constructor. */
	ChordQuaero();
    ChordQuaero(const std::string& inChordString);
    using ChordAbstract::ChordAbstract;
	// copy constructor
	ChordQuaero(const ChordAbstract& inChord);
	
	/** Destructor. */
	virtual ~ChordQuaero();
	
	const std::string str() const;
	
protected:
    virtual const std::unique_ptr<ChordAbstract> create(const Chroma& inRoot, const ChordType& inChordType);
	
	
private:
	static const std::string trimRight(const std::string& inString);
	
};

std::ostream& operator<<(std::ostream& inOutputStream, const ChordQuaero& inChord);
std::istream& operator>>(std::istream& inInputStream, ChordQuaero& inChord);
}
#endif	// #ifndef ChordQuaero_h
