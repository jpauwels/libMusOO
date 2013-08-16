#ifndef KeyFile_h
#define KeyFile_h

//============================================================================
/**
	Abstract base class representing a file containing a timed sequence of keys.

	@author		Johan Pauwels
	@date		20100322
*/
//============================================================================
#include "MusOO/TimedKey.h"

namespace MusOO
{
class KeyFile
{
public:

	KeyFile(const bool inPitchSpelled);
	/** Destructor. */
	virtual ~KeyFile();

	const TimedKeySequence& readAll();
	const TimedKeySequence readRange(double inStartTime, double inEndTime);
	void writeAll(TimedKeySequence& inTimedKeys);
	bool isEmpty() const;

	virtual void open(const std::string& inFileName) = 0;
	virtual void close() = 0;

protected:

	TimedKeySequence m_TimedKeys;
	bool m_FileHasChanged;
    bool m_PitchSpelled;
};
}
#endif	// #ifndef KeyFile_h
