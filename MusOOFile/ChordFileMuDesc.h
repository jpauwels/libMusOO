#ifndef ChordFileMuDesc_h
#define ChordFileMuDesc_h

//============================================================================
/**
 Class representing a file on disk containing chord segments.
 
 @author		Johan Pauwels
 @date			20120614
 */
//============================================================================
#include <string>
#include "ChordFile.h"

template <typename ChordLabel>
class ChordFileMuDesc : public ChordFile
{
public:
	
	ChordFileMuDesc(const bool inPitchSpelled);
	ChordFileMuDesc(std::string inFileName, const bool inPitchSpelled);
	/** Destructor. */
	virtual ~ChordFileMuDesc();
	
	virtual void open(const std::string& inFileName);
	virtual void close();
	
private:
	
	typedef TimedLabel<ChordLabel> TimedMDChord;
	typedef std::vector<TimedChord> TimedMDChordSequence;
	
	std::string m_FileName;
};

// Include template implementation
#include "ChordFileMuDesc.cpp"

#endif	// #ifndef ChordFileMuDesc_h
