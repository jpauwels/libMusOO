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
#include "MusOO/Interval.h"

using std::istringstream;
using std::ostringstream;
using std::string;
using namespace MusOO;

NoteMidi::NoteMidi()
{
}

NoteMidi::NoteMidi(std::string inNoteMidiNumber)
{
	istringstream theNoteMidiStream(inNoteMidiNumber);
	size_t theNoteMidiNumber;
	theNoteMidiStream >> theNoteMidiNumber;
	setNoteNumber(theNoteMidiNumber);
}

NoteMidi::NoteMidi(size_t inNoteMidiNumber)
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

const size_t NoteMidi::number() const
{
	return 12*(this->m_Octave+1) + Interval(Chroma::C(), this->m_Chroma).semiTonesUp();
}

NoteMidi& NoteMidi::operator=(const size_t inNoteMidiNumber)
{
	setNoteNumber(inNoteMidiNumber);
	return *this;
}

void NoteMidi::setNoteNumber(const size_t inNoteMidiNumber)
{
	this->m_Octave = inNoteMidiNumber / 12 - 1;
	this->m_Chroma = Chroma(Chroma::C(), Interval(inNoteMidiNumber % 12));
}

const std::string NoteMidi::str() const
{
	ostringstream theNoteNumberStream;
	theNoteNumberStream << number();
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

