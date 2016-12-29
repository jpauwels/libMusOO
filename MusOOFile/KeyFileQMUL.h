#ifndef KeyFileQMUL_h
#define KeyFileQMUL_h

//============================================================================
/**
	Class representing a file on disk containing key segments according to
	syntax used at QMUL.

	@author		Johan Pauwels
	@date		20100401
*/
//============================================================================
#include <string>
#include "MusOOFile/KeyFile.h"
#include "MusOO/KeyQMUL.h"
#include "MusOOFile/LabFile.h"

namespace MusOO
{
class KeyFileQMUL : public KeyFile
{
public:

	typedef TimedLabel<KeyQMUL> TimedKeyQMUL;
	typedef std::vector<TimedKeyQMUL> KeyQMULSequence;

	KeyFileQMUL(const bool inPitchSpelled);
	KeyFileQMUL(std::string inFileName, const bool inPitchSpelled);
	/** Destructor. */
	virtual ~KeyFileQMUL();

	virtual void open(const std::string& inFileName);
	virtual void close();

private:
	
//	KeyQMULSequence m_TimedKeys;
	LabFile<KeyQMUL> m_File;
};
}
#endif	// #ifndef KeyFileQMUL_h
