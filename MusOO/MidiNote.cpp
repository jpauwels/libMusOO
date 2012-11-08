//============================================================================
/**
	Implementation file for MidiNote.h
	
	@author		Johan Pauwels
	@date		20101206
*/
//============================================================================

// Includes
#include <sstream>
#include "MidiNote.h"
#include "Interval.h"

using std::istringstream;
using std::ostringstream;
using std::string;

MidiNote::MidiNote()
{
}

MidiNote::MidiNote(std::string inMidiNoteNumber)
{
	istringstream theMidiNoteStream(inMidiNoteNumber);
	size_t theMidiNoteNumber;
	theMidiNoteStream >> theMidiNoteNumber;
	setNoteNumber(theMidiNoteNumber);
}

MidiNote::MidiNote(size_t inMidiNoteNumber)
{
	setNoteNumber(inMidiNoteNumber);
}

MidiNote::MidiNote(const Note& inNote)
: Note(inNote)
{
}

MidiNote::~MidiNote()
{
	// Nothing to do...
}

const size_t MidiNote::number() const
{
	return 12*(this->m_Octave+1) + Interval(Chroma::C(), this->m_Chroma).semiTonesUp();
}

MidiNote& MidiNote::operator=(const size_t inMidiNoteNumber)
{
	setNoteNumber(inMidiNoteNumber);
	return *this;
}

void MidiNote::setNoteNumber(const size_t inMidiNoteNumber)
{
	this->m_Octave = inMidiNoteNumber / 12 - 1;
	this->m_Chroma = Chroma(Chroma::C(), Interval(inMidiNoteNumber % 12));
}

const std::string MidiNote::str() const
{
	ostringstream theNoteNumberStream;
	theNoteNumberStream << number();
	return theNoteNumberStream.str();
}

std::ostream& operator<<(std::ostream& inOutputStream, const MidiNote& inNote)
{
	inOutputStream << inNote.str();
	return inOutputStream;
}

std::istream& operator>>(std::istream& inInputStream, MidiNote& inNote)
{
	string theNoteString;
	inInputStream >> theNoteString;
	inNote = MidiNote(theNoteString);
	return inInputStream;
}

