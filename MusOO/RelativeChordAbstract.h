#ifndef RelativeChordAbstract_h
#define RelativeChordAbstract_h

//============================================================================
/**
	Class representing a relative chord.

	@author		Johan Pauwels
	@date		20101222
*/
//============================================================================
#include "MusOO/ChordTypeAbstract.h"

namespace MusOO
{
template <typename Key, typename Chroma, typename Mode> class KeyAbstract;
template <typename Chord, typename Chroma, typename ChordType> class ChordAbstract;

template <typename RelativeChord, typename ChordType>
class RelativeChordAbstract
{
public:
    
    template <typename OtherRelativeChord, typename OtherChordType> friend class RelativeChordAbstract; // to access m_RootInterval and m_Type from other RelativeChord types
    
    using ChordTypeT = ChordType;
    
	static const RelativeChord& silence();
	static const RelativeChord& none();
	static const RelativeChord& unknown();

	/** Default constructor. */
	RelativeChordAbstract();
    /** Generalised copy constructor. */
    template <typename OtherRelativeChord, typename OtherChordType>
    RelativeChordAbstract(const RelativeChordAbstract<OtherRelativeChord, OtherChordType>& inRelativeChord);
	RelativeChordAbstract(const SimpleInterval& inRootInterval, const ChordType& inType);
    template <typename Key, typename Tonic, typename Mode, typename Chord, typename Root, typename OtherChordType>
    RelativeChordAbstract(const KeyAbstract<Key, Tonic, Mode>& inKey, const ChordAbstract<Chord, Root, OtherChordType>& inChord);
    template <typename Mode>
	RelativeChordAbstract(const std::string& inDegree, const ChordType& inChordType, const Mode& inMode);
    
    /** Destructor. */
    virtual ~RelativeChordAbstract();

	const bool operator==(const RelativeChord& inRelativeChord) const;
	const bool operator!=(const RelativeChord& inRelativeChord) const;
	const bool operator<(const RelativeChord& inRelativeChord) const;
	const SimpleInterval& rootInterval() const;
	const ChordType& type() const;
    
    const bool isTrueRelativeChord() const;
    
    const bool hasSpelling() const;
    RelativeChord withoutSpelling() const;
    RelativeChord& ignoreSpelling();
    
    virtual const std::string str() const = 0;
    
protected:

	SimpleInterval m_RootInterval;
	ChordType m_Type;

};


template <typename RelativeChord, typename ChordType>
std::ostream& operator<<(std::ostream& inOutputStream, const RelativeChordAbstract<RelativeChord, ChordType>& inRelativeChord)
{
    inOutputStream << inRelativeChord.str();
    return inOutputStream;
}

template <typename RelativeChord, typename ChordType>
std::istream& operator>>(std::istream& inInputStream, RelativeChordAbstract<RelativeChord, ChordType>& inRelativeChord)
{
    std::string theRelativeChordString;
    inInputStream >> theRelativeChordString;
    inRelativeChord = RelativeChord(theRelativeChordString);
    return inInputStream;
}


template <typename RelativeChord, typename ChordType>
const RelativeChord& RelativeChordAbstract<RelativeChord, ChordType>::silence()
{
    static const RelativeChord silence(SimpleInterval::silence(), ChordType::none());
    return silence;
}

template <typename RelativeChord, typename ChordType>
const RelativeChord& RelativeChordAbstract<RelativeChord, ChordType>::none()
{
    static const RelativeChord none(SimpleInterval::none(), ChordType::none());
    return none;
}

template <typename RelativeChord, typename ChordType>
const RelativeChord& RelativeChordAbstract<RelativeChord, ChordType>::unknown()
{
    static const RelativeChord unknown(SimpleInterval::undefined(), ChordType::none());
    return unknown;
}

template <typename RelativeChord, typename ChordType>
template <typename Key, typename Tonic, typename Mode, typename Chord, typename Root, typename OtherChordType>
RelativeChordAbstract<RelativeChord, ChordType>::RelativeChordAbstract(const KeyAbstract<Key, Tonic, Mode>& inKey, const ChordAbstract<Chord, Root, OtherChordType>& inChord)
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

template <typename RelativeChord, typename ChordType>
template <typename Mode>
RelativeChordAbstract<RelativeChord, ChordType>::RelativeChordAbstract( const std::string& inDegree, const ChordType& inChordType, const Mode& inMode)
: m_RootInterval(inDegree, inMode), m_Type(inChordType)
{
}

template <typename RelativeChord, typename ChordType>
RelativeChordAbstract<RelativeChord, ChordType>::RelativeChordAbstract()
: m_RootInterval(SimpleInterval::undefined()), m_Type(ChordType::none())
{
}

template <typename RelativeChord, typename ChordType>
template <typename OtherRelativeChord, typename OtherChordType>
RelativeChordAbstract<RelativeChord, ChordType>::RelativeChordAbstract(const RelativeChordAbstract<OtherRelativeChord, OtherChordType>& inRelativeChord)
: m_RootInterval(inRelativeChord.m_RootInterval), m_Type(inRelativeChord.m_Type)
{
}

template <typename RelativeChord, typename ChordType>
RelativeChordAbstract<RelativeChord, ChordType>::RelativeChordAbstract(const SimpleInterval& inRootInterval, const ChordType& inType)
: m_RootInterval(inRootInterval), m_Type(inType)
{
}

template <typename RelativeChord, typename ChordType>
RelativeChordAbstract<RelativeChord, ChordType>::~RelativeChordAbstract()
{
}

template <typename RelativeChord, typename ChordType>
const bool RelativeChordAbstract<RelativeChord, ChordType>::operator==(const RelativeChord& inRelativeChord) const
{
    return m_RootInterval == inRelativeChord.m_RootInterval && m_Type == inRelativeChord.m_Type;
}

template <typename RelativeChord, typename ChordType>
const bool RelativeChordAbstract<RelativeChord, ChordType>::operator!=(const RelativeChord& inRelativeChord) const
{
    return m_RootInterval != inRelativeChord.m_RootInterval || m_Type != inRelativeChord.m_Type;
}

template <typename RelativeChord, typename ChordType>
const bool RelativeChordAbstract<RelativeChord, ChordType>::operator<(const RelativeChord& inRelativeChord) const
{
    if (m_RootInterval != inRelativeChord.m_RootInterval)
    {
        return m_RootInterval < inRelativeChord.m_RootInterval;
    }
    else
    {
        return m_Type < inRelativeChord.m_Type;
    }
}

template <typename RelativeChord, typename ChordType>
const SimpleInterval& RelativeChordAbstract<RelativeChord, ChordType>::rootInterval() const
{
    return m_RootInterval;
}

template <typename RelativeChord, typename ChordType>
const ChordType& RelativeChordAbstract<RelativeChord, ChordType>::type() const
{
    return m_Type;
}

template <typename RelativeChord, typename ChordType>
const bool RelativeChordAbstract<RelativeChord, ChordType>::isTrueRelativeChord() const
{
    return m_Type != ChordType::none();
}

template <typename RelativeChord, typename ChordType>
const bool RelativeChordAbstract<RelativeChord, ChordType>::hasSpelling() const
{
    return m_RootInterval.hasSpelling() && m_Type.hasSpelling();
}

template <typename RelativeChord, typename ChordType>
RelativeChord RelativeChordAbstract<RelativeChord, ChordType>::withoutSpelling() const
{
    return RelativeChord(static_cast<const RelativeChord&>(*this)).ignoreSpelling();
}
template <typename RelativeChord, typename ChordType>
RelativeChord& RelativeChordAbstract<RelativeChord, ChordType>::ignoreSpelling()
{
    if (isTrueRelativeChord())
    {
        m_RootInterval.ignoreSpelling();
        m_Type.ignoreSpelling();
    }
    return static_cast<RelativeChord&>(*this);
}

}
#endif	// #ifndef RelativeChordAbstract_h
