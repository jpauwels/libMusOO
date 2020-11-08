#ifndef Key_h
#define Key_h

//============================================================================
/**
	Class representing a key.

	@author		Johan Pauwels
	@date		20100322
	@todo		implement stream operators for key class
*/
//============================================================================
#include "MusOO/ChromaAbstract.h"
#include "MusOO/ChordAbstract.h"
#include "MusOO/RelativeChordAbstract.h"
#include <set>


namespace MusOO
{

template <typename Key, typename Chroma, typename Mode>
class KeyAbstract
{
public:
    
    template <typename OtherKey, typename OtherChroma, typename OtherMode> friend class KeyAbstract; // to access m_Tonic and m_Mode from other Key types

    using ChromaT = Chroma;
    using ModeT = Mode;
    
	static const Key& silence();
    static const Key& none();
    static const Key& undefined();

	/** Default constructor. */
	KeyAbstract();
    /** Generalised copy constructor. */
    template <typename OtherKey, typename OtherChroma, typename OtherMode>
    KeyAbstract(const KeyAbstract<OtherKey, OtherChroma, OtherMode>& inKey);
	KeyAbstract(const Chroma& inTonic, const Mode& inMode);

    /** Destructor. */
    virtual ~KeyAbstract();

	bool operator==(const Key& inKey) const;
	bool operator!=(const Key& inKey) const;

	Chroma& tonic();
	const Chroma& tonic() const;
	Mode& mode();
	const Mode& mode() const;
	
	const std::set<Chroma> chromas() const;
	const size_t cardinality() const;

	const size_t chromaticCOFDistance(const Key& inKey) const;
	
	/** Returns the chord that arises from interpreting a given relative chord in this key */
    template <typename Chord, typename RelativeChord, typename RootChroma, typename ChordType>
	const ChordAbstract<Chord, RootChroma, ChordType> chord(const RelativeChordAbstract<RelativeChord, ChordType>& inRelChord) const;
	/* Returns the relative chord that arises from interpreting a given chord in this key */
    template <typename RelativeChord, typename Chord, typename RootChroma, typename ChordType>
	const RelativeChordAbstract<RelativeChord, ChordType> relativeChord(const ChordAbstract<Chord, RootChroma, ChordType>& inChord) const;
    
    const bool isTrueKey() const;
    
    const bool hasSpelling() const;
    Key withoutSpelling() const;
    Key& ignoreSpelling();
    
    void addChroma(const Chroma& inChroma);
	void deleteChroma(const Chroma& inChroma);
    
    virtual const std::string str() const = 0;
    
protected:

	Chroma m_Tonic;
	Mode m_Mode;

private:


};



template <typename Key, typename Chroma, typename Mode>
std::ostream& operator<<(std::ostream& inOutputStream, const KeyAbstract<Key, Chroma, Mode>& inKey)
{
    inOutputStream << inKey.str();
    return inOutputStream;
}

template <typename Key, typename Chroma, typename Mode>
std::istream& operator>>(std::istream& inInputStream, KeyAbstract<Key, Chroma, Mode>& inKey)
{
    std::string theKeyString;
    inInputStream >> theKeyString;
    inKey = Key(theKeyString);
    return inInputStream;
}


template <typename Key, typename Chroma, typename Mode>
const Key& KeyAbstract<Key, Chroma, Mode>::silence()
{
    static const Key silence(Chroma::silence(), Mode::none());
    return silence;
}

template <typename Key, typename Chroma, typename Mode>
const Key& KeyAbstract<Key, Chroma, Mode>::none()
{
    static const Key none(Chroma::none(), Mode::none());
    return none;
}

template <typename Key, typename Chroma, typename Mode>
const Key& KeyAbstract<Key, Chroma, Mode>::undefined()
{
    static const Key undefined(Chroma::undefined(), Mode::none());
    return undefined;
}

template <typename Key, typename Chroma, typename Mode>
KeyAbstract<Key, Chroma, Mode>::KeyAbstract()
: m_Tonic(Chroma::undefined()), m_Mode(Mode::none())
{
}

template <typename Key, typename Chroma, typename Mode>
template <typename OtherKey, typename OtherChroma, typename OtherMode>
KeyAbstract<Key, Chroma, Mode>::KeyAbstract(const KeyAbstract<OtherKey, OtherChroma, OtherMode>& inKey)
: m_Tonic(inKey.tonic()), m_Mode(inKey.mode())
{
}

template <typename Key, typename Chroma, typename Mode>
KeyAbstract<Key, Chroma, Mode>::KeyAbstract(const Chroma& inTonic, const Mode& inMode)
: m_Tonic(inTonic), m_Mode(inMode)
{
}

template <typename Key, typename Chroma, typename Mode>
KeyAbstract<Key, Chroma, Mode>::~KeyAbstract()
{
}

template <typename Key, typename Chroma, typename Mode>
Chroma& KeyAbstract<Key, Chroma, Mode>::tonic()
{
    return m_Tonic;
}

template <typename Key, typename Chroma, typename Mode>
const Chroma& KeyAbstract<Key, Chroma, Mode>::tonic() const
{
    return m_Tonic;
}

template <typename Key, typename Chroma, typename Mode>
Mode& KeyAbstract<Key, Chroma, Mode>::mode()
{
    return m_Mode;
}

template <typename Key, typename Chroma, typename Mode>
const Mode& KeyAbstract<Key, Chroma, Mode>::mode() const
{
    return m_Mode;
}

template <typename Key, typename Chroma, typename Mode>
bool KeyAbstract<Key, Chroma, Mode>::operator==(const Key& inKey) const
{
    return m_Mode == inKey.m_Mode && m_Tonic == inKey.m_Tonic;
}

template <typename Key, typename Chroma, typename Mode>
bool KeyAbstract<Key, Chroma, Mode>::operator!=(const Key& inKey) const
{
    return m_Mode != inKey.m_Mode || m_Tonic != inKey.m_Tonic;
}

template <typename Key, typename Chroma, typename Mode>
const std::set<Chroma> KeyAbstract<Key, Chroma, Mode>::chromas() const
{
    std::set<Chroma> theChromaSet;
    for (std::set<SimpleInterval>::const_iterator it = m_Mode.m_set.begin(); it != m_Mode.m_set.end(); ++it)
    {
        theChromaSet.insert(Chroma(m_Tonic, *it));
    }
    return theChromaSet;
}

template <typename Key, typename Chroma, typename Mode>
const size_t KeyAbstract<Key, Chroma, Mode>::cardinality() const
{
    return m_Mode.cardinality();
}

template <typename Key, typename Chroma, typename Mode>
const size_t KeyAbstract<Key, Chroma, Mode>::chromaticCOFDistance(const Key& inKey) const
{
    return mode().chromaticCOFDistance(SimpleInterval(tonic(), inKey.tonic()), inKey.mode());
}

template <typename Key, typename Chroma, typename Mode>
template <typename Chord, typename RelativeChord, typename RootChroma, typename ChordType>
const ChordAbstract<Chord, RootChroma, ChordType> KeyAbstract<Key, Chroma, Mode>::chord(const RelativeChordAbstract<RelativeChord, ChordType>& inRelChord) const
{
    //return Chord(tonic()+inRelChord.rootInterval(), inRelChord.type());
    return Chord(Chroma(tonic(), inRelChord.rootInterval()), inRelChord.type());
}

template <typename Key, typename Chroma, typename Mode>
template <typename RelativeChord, typename Chord, typename RootChroma, typename ChordType>
const RelativeChordAbstract<RelativeChord, ChordType> KeyAbstract<Key, Chroma, Mode>::relativeChord(const ChordAbstract<Chord, RootChroma, ChordType>& inChord) const
{
    return RelativeChord(SimpleInterval(tonic(), inChord.root()), inChord.type());
}

template <typename Key, typename Chroma, typename Mode>
const bool KeyAbstract<Key, Chroma, Mode>::isTrueKey() const
{
    return m_Mode != Mode::none();
}

template <typename Key, typename Chroma, typename Mode>
const bool KeyAbstract<Key, Chroma, Mode>::hasSpelling() const
{
    return m_Tonic.hasSpelling() && m_Mode.hasSpelling();
}

template <typename Key, typename Chroma, typename Mode>
Key KeyAbstract<Key, Chroma, Mode>::withoutSpelling() const
{
    return Key(static_cast<const Key&>(*this)).ignoreSpelling();
}

template <typename Key, typename Chroma, typename Mode>
Key& KeyAbstract<Key, Chroma, Mode>::ignoreSpelling()
{
    if (isTrueKey())
    {
        m_Tonic.ignoreSpelling();
        m_Mode.ignoreSpelling();
    }
    return static_cast<Key&>(*this);
}

template <typename Key, typename Chroma, typename Mode>
void KeyAbstract<Key, Chroma, Mode>::addChroma(const Chroma& inChroma)
{
    mode().addInterval(SimpleInterval(tonic(), inChroma));
}

template <typename Key, typename Chroma, typename Mode>
void KeyAbstract<Key, Chroma, Mode>::deleteChroma(const Chroma& inChroma)
{
    mode().deleteInterval(SimpleInterval(tonic(), inChroma));
}

}
#endif	// #ifndef Key_h
