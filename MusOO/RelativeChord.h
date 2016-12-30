#ifndef RelativeChord_h
#define RelativeChord_h

//============================================================================
/**
	Class representing a relative chord.

	@author		Johan Pauwels
	@date		20101222
*/
//============================================================================
#include "MusOO/ChordType.h"

namespace MusOO
{
class Key;
class Chord;
class Mode;
    
class RelativeChord
{
public:

	static const RelativeChord& silence();
	static const RelativeChord& none();
	static const RelativeChord& unknown();

	/** Default constructor. */
	RelativeChord();
	RelativeChord(const SimpleInterval& inRootInterval, const ChordType& inType);
	RelativeChord(const Key& inKey, const Chord& inChord);
	RelativeChord(const std::string& inDegree, const ChordType& inChordType, const Mode& inMode);

	/** Destructor. */
	virtual ~RelativeChord();

	bool operator==(const RelativeChord& inRelativeChord) const;
	bool operator!=(const RelativeChord& inRelativeChord) const;
	bool operator<(const RelativeChord& inRelativeChord) const;
	const SimpleInterval& rootInterval() const;
	const ChordType& type() const;
    
    const bool isTrueRelativeChord() const;
    
    const bool hasSpelling() const;
    RelativeChord& ignoreSpelling();
    
protected:

	SimpleInterval m_RootInterval;
	ChordType m_Type;

private:


};
}
#endif	// #ifndef RelativeChord_h
