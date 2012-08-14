#ifndef KeyFile_h
#define KeyFile_h

//============================================================================
/**
	Abstract base class representing a file containing a timed sequence of keys.

	@author		Johan Pauwels
	@date		20100322
*/
//============================================================================
#include "TimedKey.h"

class KeyFile
{
public:

	KeyFile();
	/** Destructor. */
	virtual ~KeyFile();

	const KeySequence& readAll();
	const KeySequence readRange(double inStartTime, double inEndTime);
	void writeAll(KeySequence& inTimedKeys);
	bool isEmpty() const;

	virtual void open(const std::string& inFileName) = 0;
	virtual void close() = 0;

protected:

	KeySequence m_TimedKeys;
	bool m_FileHasChanged;
};

#endif	// #ifndef KeyFile_h
