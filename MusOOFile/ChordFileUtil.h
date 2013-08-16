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
#include "MusOOFile/ChordFileQM.h"
#include "MusOOFile/ChordFileProsemus.h"
#include "MusOOFile/ChordFileSonicAnnotatorCSV.h"
#include "MusOOFile/ChordFileMuDesc.h"
#include "MusOO/ChordQuaero.h"


namespace MusOO { namespace ChordFileUtil
{
	ChordFile* const newChordFileFromExtension(const boost::filesystem::path& inFileName, const bool inPitchSpelled, const std::string& inFileTypeSelect = "auto")
	{
        using boost::algorithm::ends_with;
		if (inFileTypeSelect == "QMUL" || (inFileTypeSelect == "auto" && (inFileName.extension() == ".lab" || inFileName.extension() == ".txt")))
		{
			return new ChordFileQM(inFileName.string(), inPitchSpelled);
		}
		else if (inFileTypeSelect == "Prosemus" || (inFileTypeSelect == "auto" && inFileName.extension() == ".chords"))
		{
			return new ChordFileProsemus(inFileName.string(), inPitchSpelled);
		}
		else if (inFileTypeSelect == "SonicAnnotator" || (inFileTypeSelect == "auto" && inFileName.extension() == ".csv"))
		{
			return new ChordFileSonicAnnotatorCSV<ChordQM>(inFileName.string(), inPitchSpelled);
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
    
    const TimedChordSequence readChordSequenceFromFile(const boost::filesystem::path& inFilePath, const bool inPitchSpelled, const std::string& inFileTypeSelect = "auto")
    {
        ChordFile* const theChordFile = newChordFileFromExtension(inFilePath, inPitchSpelled, inFileTypeSelect);
        if (theChordFile->isEmpty())
        {
            throw std::runtime_error("The file " + inFilePath.string() + " does not contain any chords");
        }
        const TimedChordSequence retChords = theChordFile->readAll();
        delete theChordFile;
        return retChords;
    }
} }

#endif	// #ifndef ChordFileUtil_h
