#ifndef RelativeChordAbstract_h
#define RelativeChordAbstract_h

//============================================================================
/**
	Class representing a relative chord.

	@author		Johan Pauwels
	@date		20101222
*/
//============================================================================
#include "MusOO/ChordType.h"
#include "MusOO/Key.h"

namespace MusOO
{
class ChordAbstract;
class Mode;
    
class RelativeChordAbstract
{
public:

    template <typename RelativeChord>
	static const RelativeChord& silence();
    template <typename RelativeChord>
	static const RelativeChord& none();
    template <typename RelativeChord>
	static const RelativeChord& unknown();

	/** Default constructor. */
	RelativeChordAbstract();
	RelativeChordAbstract(const SimpleInterval& inRootInterval, const ChordType& inType);
    template <typename Chord>
	RelativeChordAbstract(const Key& inKey, const Chord& inChord);
	RelativeChordAbstract(const std::string& inDegree, const ChordType& inChordType, const Mode& inMode);

	/** Destructor. */
	virtual ~RelativeChordAbstract() = 0;

	bool operator==(const RelativeChordAbstract& inRelativeChord) const;
	bool operator!=(const RelativeChordAbstract& inRelativeChord) const;
	bool operator<(const RelativeChordAbstract& inRelativeChord) const;
	const SimpleInterval& rootInterval() const;
	const ChordType& type() const;
    
    const bool isTrueRelativeChord() const;
    
    const bool hasSpelling() const;
    RelativeChordAbstract& ignoreSpelling();
    
protected:

	SimpleInterval m_RootInterval;
	ChordType m_Type;

private:


};
    
template <typename RelativeChord>
const RelativeChord& RelativeChordAbstract::silence()
{
    static const RelativeChord silence(SimpleInterval::silence(), ChordType::none());
    return silence;
}

template <typename RelativeChord>
const RelativeChord& RelativeChordAbstract::none()
{
    static const RelativeChord none(SimpleInterval::none(), ChordType::none());
    return none;
}

template <typename RelativeChord>
const RelativeChord& RelativeChordAbstract::unknown()
{
    static const RelativeChord unknown(SimpleInterval::undefined(), ChordType::none());
    return unknown;
}

template <typename Chord>
RelativeChordAbstract::RelativeChordAbstract(const Key& inKey, const Chord& inChord)
: m_RootInterval(inKey.tonic(), inChord.root()), m_Type(inChord.type())
{
    if (inChord == Chord::silence())
    {
        m_RootInterval = SimpleInterval::silence();
    }
    else if (inChord == Chord::none())
    {
        m_RootInterval = SimpleInterval::none();
    }
    else if (inChord == Chord::undefined())
    {
        m_RootInterval = SimpleInterval::undefined();
    }
    if (inKey == Key::silence())
    {
        std::runtime_error("Cannot deduce relative chord when key is silence");
    }
}

}
#endif	// #ifndef RelativeChordAbstract_h
