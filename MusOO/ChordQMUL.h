#ifndef ChordQMUL_h
#define ChordQMUL_h

//============================================================================
	/**
	Class representing a chord with syntax defined by Harte et al.

	@author		Johan Pauwels
	@date		20090119
*/
//============================================================================
#include <string>
#include <map>
#include "MusOO/ChordAbstract.h"

namespace MusOO
{
class ChordQMUL : public ChordAbstract
{
public:

	/** Default constructor. */
	ChordQMUL();
    ChordQMUL(const std::string& inChordString);
    using ChordAbstract::ChordAbstract;
	// copy constructor
	ChordQMUL(const ChordAbstract& inChord);

	/** Destructor. */
	virtual ~ChordQMUL();

	const std::string str() const;

protected:
    virtual const std::unique_ptr<ChordAbstract> create(const Chroma& inRoot, const ChordType& inChordType);


private:


};

std::ostream& operator<<(std::ostream& inOutputStream, const ChordQMUL& inChord);
std::istream& operator>>(std::istream& inInputStream, ChordQMUL& inChord);
}
#endif	// #ifndef ChordQMUL_h
