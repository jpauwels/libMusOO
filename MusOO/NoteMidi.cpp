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

using std::istringstream;
using std::ostringstream;
using std::string;
using namespace MusOO;

NoteMidi::NoteMidi()
{
}

NoteMidi::NoteMidi(const std::string& inNoteMidiNumber)
{
	istringstream theNoteMidiStream(inNoteMidiNumber);
	ptrdiff_t theNoteMidiNumber;
	theNoteMidiStream >> theNoteMidiNumber;
	setNoteNumber(theNoteMidiNumber);
}

NoteMidi::NoteMidi(const ptrdiff_t inNoteMidiNumber)
{
	setNoteNumber(inNoteMidiNumber);
}

NoteMidi::NoteMidi(const Note& inNote)
: Note(inNote)
{
}

NoteMidi::~NoteMidi()
{
	// Nothing to do...
}

const ptrdiff_t NoteMidi::value() const
{
	return 12*(this->m_Octave+1) + SimpleInterval(Chroma::C(), this->m_Chroma).semiTonesUp();
}

NoteMidi& NoteMidi::operator=(const ptrdiff_t inNoteMidiNumber)
{
	setNoteNumber(inNoteMidiNumber);
	return *this;
}

void NoteMidi::setNoteNumber(const ptrdiff_t inNoteMidiNumber)
{
	this->m_Octave = inNoteMidiNumber / 12 - 1;
	this->m_Chroma = Chroma(Chroma::C(), SimpleInterval(inNoteMidiNumber % 12));
}

const std::string NoteMidi::str() const
{
	ostringstream theNoteNumberStream;
	theNoteNumberStream << value();
	return theNoteNumberStream.str();
}

std::ostream& MusOO::operator<<(std::ostream& inOutputStream, const NoteMidi& inNote)
{
	inOutputStream << inNote.str();
	return inOutputStream;
}

std::istream& MusOO::operator>>(std::istream& inInputStream, NoteMidi& inNote)
{
	string theNoteString;
	inInputStream >> theNoteString;
	inNote = NoteMidi(theNoteString);
	return inInputStream;
}

