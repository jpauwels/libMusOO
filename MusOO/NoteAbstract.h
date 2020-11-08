#ifndef Note_h
#define Note_h

//============================================================================
/**
	Class representing a note.

	@author		Johan Pauwels
	@date		20090120
*/
//============================================================================
#include "MusOO/ChromaAbstract.h"

namespace MusOO
{
template <typename Note, typename Chroma>
class NoteAbstract
{
public:
    
    template <typename OtherNote, typename OtherChroma> friend class NoteAbstract; // to access m_Chroma and m_Octave from other Note types
    
    using ChromaT = Chroma;
    
	const static Note& silence();
    
    /** Default constructor. */
    NoteAbstract();
    /** Generalised copy constructor. */
    template <typename OtherNote, typename OtherChroma>
    NoteAbstract(const NoteAbstract<OtherNote, OtherChroma>& inNote);
    template <typename OtherChroma>
    NoteAbstract(const ChromaAbstract<OtherChroma>& inChroma, const ptrdiff_t inOctave);
// 	NoteAbstract(double inFrequency);
// 	NoteAbstract(std::string inNoteName);

	/** Destructor. */
	virtual ~NoteAbstract();

	const bool operator==(const Note& inNote) const;

    Chroma& chroma();
    const Chroma& chroma() const;
    ptrdiff_t& octave();
    const ptrdiff_t& octave() const;
    
// 	const double frequency(double inDiapason = 440.) const;
// 	const std::string name() const;

// 	int intervalInCircleSteps(Note inNote);

	/** 
		Moves this note a given number of semitones up if the number is positive or down if it is negative.

		@param	inSemiTones		the number of semitones to move
		@return					a reference to this note
	*/
//	Note& moveSemiTones(int inSemiTones);
    
    const bool hasSpelling() const;
    Note withoutSpelling() const;
    Note& ignoreSpelling();
    
    virtual const std::string str() const = 0;
    
protected:

	Chroma m_Chroma;
	ptrdiff_t m_Octave;
	
};


template <typename Note, typename Chroma>
std::ostream& operator<<(std::ostream& inOutputStream, const NoteAbstract<Note, Chroma>& inNote)
{
    inOutputStream << inNote.str();
    return inOutputStream;
}

template <typename Note, typename Chroma>
std::istream& operator>>(std::istream& inInputStream, NoteAbstract<Note, Chroma>& inNote)
{
    std::string theNoteString;
    inInputStream >> theNoteString;
    inNote = Note(theNoteString);
    return inInputStream;
}


template <typename Note, typename Chroma>
const Note& NoteAbstract<Note, Chroma>::silence()
{
    static const Note silence(ChromaAbstract<Chroma>::silence(), 0);
    return silence;
}

template <typename Note, typename Chroma>
NoteAbstract<Note, Chroma>::NoteAbstract()
: m_Chroma(ChromaAbstract<Chroma>::undefined()), m_Octave(0)
{
}

template <typename Note, typename Chroma>
template <typename OtherNote, typename OtherChroma>
NoteAbstract<Note, Chroma>::NoteAbstract(const NoteAbstract<OtherNote, OtherChroma>& inNote)
: m_Chroma(inNote.m_Chroma), m_Octave(inNote.m_Octave)
{
}

template <typename Note, typename Chroma>
template <typename OtherChroma>
NoteAbstract<Note, Chroma>::NoteAbstract(const ChromaAbstract<OtherChroma>& inChroma, const ptrdiff_t inOctave)
: m_Chroma(static_cast<const OtherChroma&>(inChroma)), m_Octave(inOctave)
{
}

//template <typename Note, typename Chroma>
// NoteAbstract<Note, Chroma>::NoteAbstract(double inFrequency)
// {
//
// }

//template <typename Note, typename Chroma>
// NoteAbstract<Note, Chroma>::NoteAbstract(std::string inNoteName)
// {
//
// }

template <typename Note, typename Chroma>
NoteAbstract<Note, Chroma>::~NoteAbstract()
{
}

template <typename Note, typename Chroma>
const bool NoteAbstract<Note, Chroma>::operator==(const Note& inNote) const
{
    return m_Chroma == inNote.m_Chroma && m_Octave == inNote.m_Octave;
}

template <typename Note, typename Chroma>
Chroma& NoteAbstract<Note, Chroma>::chroma()
{
    return m_Chroma;
}

template <typename Note, typename Chroma>
const Chroma& NoteAbstract<Note, Chroma>::chroma() const
{
    return m_Chroma;
}

template <typename Note, typename Chroma>
ptrdiff_t& NoteAbstract<Note, Chroma>::octave()
{
    return m_Octave;
}

template <typename Note, typename Chroma>
const ptrdiff_t& NoteAbstract<Note, Chroma>::octave() const
{
    return m_Octave;
}

//template <typename Note, typename Chroma>
// const double NoteAbstract<Note, Chroma>::frequency(double inDiapason /*= 440.*/) const
// {
//     return inDiapason;
// }

//template <typename Note, typename Chroma>
// const std::string NoteAbstract<Note, Chroma>::name() const
// {
//     return "";
// }

template <typename Note, typename Chroma>
const bool NoteAbstract<Note, Chroma>::hasSpelling() const
{
    return m_Chroma.hasSpelling();
}

template <typename Note, typename Chroma>
Note NoteAbstract<Note, Chroma>::withoutSpelling() const
{
    return Note(static_cast<const Note&>(*this)).ignoreSpelling();
}

template <typename Note, typename Chroma>
Note& NoteAbstract<Note, Chroma>::ignoreSpelling()
{
    m_Chroma.ignoreSpelling();
    return static_cast<Note&>(*this);
}

}
#endif	// #ifndef Note_h
