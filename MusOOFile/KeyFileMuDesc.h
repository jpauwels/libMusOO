#ifndef KeyFileMuDesc_h
#define KeyFileMuDesc_h

//============================================================================
/**
 Class representing a file on disk containing key segments.
 
 @author		Johan Pauwels
 @date			20130416
 */
//============================================================================
#include <string>
#include "KeyFile.h"

template <typename KeyLabel>
class KeyFileMuDesc : public KeyFile
{
public:
	
	KeyFileMuDesc(const bool inPitchSpelled);
	KeyFileMuDesc(std::string inFileName, const bool inPitchSpelled);
	/** Destructor. */
	virtual ~KeyFileMuDesc();
	
	virtual void open(const std::string& inFileName);
	virtual void close();
	
private:
	
	typedef TimedLabel<KeyLabel> TimedMDKey;
	typedef std::vector<TimedKey> TimedMDKeySequence;
	
	std::string m_FileName;
};

// Include template implementation
#include "KeyFileMuDesc.cpp"

#endif	// #ifndef KeyFileMuDesc_h
