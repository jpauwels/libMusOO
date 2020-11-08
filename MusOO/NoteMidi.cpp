//============================================================================
/**
	Implementation file for NoteMidi.h
	
	@author		Johan Pauwels
	@date		20101206
*/
//============================================================================

// Includes
#include <sstream>
#include "MusOO/NoteMidi.h"
#include "MusOO/SimpleInterval.h"

using namespace MusOO;

NoteMidi::NoteMidi(const std::string& inNoteMidiNumber)
{
	std::istringstream theNoteMidiStream(inNoteMidiNumber);
	ptrdiff_t theNoteMidiNumber;
	theNoteMidiStream >> theNoteMidiNumber;
	setNoteNumber(theNoteMidiNumber);
}

NoteMidi::NoteMidi(const ptrdiff_t inNoteMidiNumber)
{
	setNoteNumber(inNoteMidiNumber);
}

const ptrdiff_t NoteMidi::value() const
{
	return 12*(this->m_Octave+1) + SimpleInterval(ChromaLetter::C(), this->m_Chroma).semiTonesUp();
}

//NoteMidi& NoteMidi::operator=(const ptrdiff_t inNoteMidiNumber)
//{
//	setNoteNumber(inNoteMidiNumber);
//	return *this;
//}

void NoteMidi::setNoteNumber(const ptrdiff_t inNoteMidiNumber)
{
	this->m_Octave = inNoteMidiNumber / 12 - 1;
	this->m_Chroma = ChromaLetter(ChromaLetter::C(), SimpleInterval(inNoteMidiNumber % 12));
}

const std::string NoteMidi::str() const
{
	std::ostringstream theNoteNumberStream;
	theNoteNumberStream << value();
	return theNoteNumberStream.str();
}
