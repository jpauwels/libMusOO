#ifndef ChordChordino_h
#define ChordChordino_h

//============================================================================
	/**
	Class representing a chord with syntax as used by the Chordino Vamp plugin

	@author		Johan Pauwels
	@date		20090119
*/
//============================================================================
#include <string>
#include <map>
#include "MusOO/ChordAbstract.h"

namespace MusOO
{
class ChordChordino : public ChordAbstract
{
public:

	/** Default constructor. */
	ChordChordino();
    ChordChordino(std::string inChordString);
    using ChordAbstract::ChordAbstract;
	// copy constructor
	ChordChordino(const ChordAbstract& inChord);

	/** Destructor. */
	virtual ~ChordChordino();

	const std::string str() const;

protected:
    virtual const std::unique_ptr<ChordAbstract> create(const Chroma& inRoot, const ChordType& inChordType);


private:


};

std::ostream& operator<<(std::ostream& inOutputStream, const ChordChordino& inChord);
std::istream& operator>>(std::istream& inInputStream, ChordChordino& inChord);
}
#endif	// #ifndef ChordChordino_h
