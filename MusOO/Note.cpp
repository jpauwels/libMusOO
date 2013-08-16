//============================================================================
/**
    Implementation file for Note.h
    
    @author		Johan Pauwels
    @date		20090120
*/
//============================================================================

// Includes
#include "MusOO/Note.h"
#include "MusOO/Interval.h"

using namespace MusOO;

const Note& Note::silence()
{
	static const Note silence(Chroma::silence(), 0);
	return silence;
}

Note::Note()
: m_Chroma(Chroma::undefined()), m_Octave(0)
{

}

Note::Note(Chroma inChroma, ptrdiff_t inOctave)
: m_Chroma(inChroma), m_Octave(inOctave)
{

}

// Note::Note(double inFrequency)
// {
// 
// }
// 
// Note::Note(std::string inNoteName)
// {
// 
// }

Note::~Note()
{
}

const bool Note::operator==(const Note& inNote) const
{
	return m_Chroma == inNote.m_Chroma && m_Octave == inNote.m_Octave;
}

const std::string Note::str() const
{
	if (*this == Note::silence())
	{
		return "silence";
	}
	return "";
}

// const double Note::frequency(double inDiapason /*= 440.*/) const
// {
// 	return inDiapason;
// }
// 
// const std::string Note::name() const
// {
// 	return "";
// }
