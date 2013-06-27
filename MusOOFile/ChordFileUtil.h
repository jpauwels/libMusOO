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
#include <boost/algorithm/string/predicate.hpp>
#include <string>
#include "QMChordFile.h"
#include "ProsemusChordFile.h"
#include "SonicAnnotatorCSVChordFile.h"
#include "ChordFileMuDesc.h"
#include "ChordQuaero.h"

using boost::algorithm::ends_with;

class ChordFileUtil
{
public:

	static ChordFile* newChordFileFromExtension(boost::filesystem::path inFileName, const bool inPitchSpelled, std::string inFileTypeSelect = "auto")
	{
		if (inFileTypeSelect == "QMUL" || (inFileTypeSelect == "auto" && (inFileName.extension() == ".lab" || inFileName.extension() == ".txt")))
		{
			return new QMChordFile(inFileName.string(), inPitchSpelled);
		}
		else if (inFileTypeSelect == "Prosemus" || (inFileTypeSelect == "auto" && inFileName.extension() == ".chords"))
		{
			return new ProsemusChordFile(inFileName.string(), inPitchSpelled);
		}
		else if (inFileTypeSelect == "SonicAnnotator" || (inFileTypeSelect == "auto" && inFileName.extension() == ".csv"))
		{
			return new SonicAnnotatorCSVChordFile<QMChord>(inFileName.string(), inPitchSpelled);
		}
		else if (inFileTypeSelect == "QuaeroEval" || (inFileTypeSelect == "auto" && ends_with(inFileName.stem().string(), ".f") && inFileName.extension() == ".xml"))
		{
			return new ChordFileMuDesc<ChordinoChord>(inFileName.string(), inPitchSpelled);
		}
		else if (inFileTypeSelect == "Quaero" || (inFileTypeSelect == "auto" && inFileName.extension() == ".xml"))
		{
			return new ChordFileMuDesc<ChordQuaero>(inFileName.string(), inPitchSpelled);
		}
		else if (inFileTypeSelect == "auto")
		{
			throw std::invalid_argument("Cannot automatically derive file type from extension " + inFileName.extension().string());
		}
		else
		{
			throw std::invalid_argument("Unknown type selector " + inFileTypeSelect);
		}
	}

protected:


private:


};

#endif	// #ifndef ChordFileUtil_h
