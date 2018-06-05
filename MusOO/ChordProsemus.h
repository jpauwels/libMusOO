#ifndef ChordProsemus_h
#define ChordProsemus_h

//============================================================================
/**
	Class representing a chord with Prosemus syntax.

	@author		Johan Pauwels
	@date		20101220
*/
//============================================================================
#include <string>
#include "MusOO/ChordAbstract.h"

namespace MusOO
{
class ChordProsemus : public ChordAbstract
{
public:

	/** Default constructor. */
	ChordProsemus();
    ChordProsemus(const std::string& inChordString);
    using ChordAbstract::ChordAbstract;
	// copy constructor
	ChordProsemus(const ChordAbstract& inChord);

	/** Destructor. */
	virtual ~ChordProsemus();

	const std::string str() const;

protected:
    virtual const std::unique_ptr<ChordAbstract> create(const Chroma& inRoot, const ChordType& inChordType);


private:


};
}
#endif	// #ifndef ChordProsemus_h
