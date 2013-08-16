#ifndef KeyFileElis_h
#define KeyFileElis_h

//============================================================================
/**
	Class representing a file containing a timed sequence of keys using Elis
	syntax.

	@author		Johan Pauwels
	@date		20100401
*/
//============================================================================
#include <string>
#include "MusOOFile/KeyFile.h"
#include "MusOOFile/LabFile.h"
#include "MusOO/KeyElis.h"

namespace MusOO
{
class KeyFileElis : public KeyFile
{
public:

	typedef TimedLabel<KeyElis> TimedKeyElis;
	typedef std::vector<TimedKeyElis> KeyElisSequence;

	KeyFileElis(const bool inPitchSpelled);
	KeyFileElis(std::string inFileName, const bool inPitchSpelled);
	/** Destructor. */
	virtual ~KeyFileElis();

	virtual void open(const std::string& inFileName);
	virtual void close();

private:

	LabFile<KeyElis> m_File;

};
}
#endif	// #ifndef KeyFileElis_h
