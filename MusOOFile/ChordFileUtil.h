#ifndef ChordFileUtil_h
#define ChordFileUtil_h

//============================================================================
/**
	Class representing .

	@author		Johan Pauwels
	@date		20100401
*/
//============================================================================
#include <stdexcept>
#include <boost/filesystem.hpp>
#include "QMChordFile.h"
#include "ProsemusChordFile.h"
#include "SonicAnnotatorCSVChordFile.h"

class ChordFileUtil
{
public:

	static ChordFile* newChordFileFromExtension(boost::filesystem::path inFileName)
	{
		if (inFileName.extension() == ".lab" || inFileName.extension() == ".txt")
		{
			return new QMChordFile(inFileName.string());
		}
		else if (inFileName.extension() == ".chords")
		{
			return new ProsemusChordFile(inFileName.string());
		}
		else if (inFileName.extension() == ".csv")
		{
			return new SonicAnnotatorCSVChordFile<QMChord>(inFileName.string());
		}
		else
		{
			throw std::invalid_argument("Unknown extension " + inFileName.extension().string());
		}
	}

protected:


private:


};

#endif	// #ifndef ChordFileUtil_h
