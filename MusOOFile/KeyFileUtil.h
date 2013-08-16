#ifndef KeyFileUtil_h
#define KeyFileUtil_h

//============================================================================
/**
	Class representing .

	@author		Johan Pauwels
	@date		20100401
*/
//============================================================================
#include <stdexcept>
#include <boost/filesystem.hpp>
#include "MusOOFile/KeyFileElis.h"
#include "MusOOFile/KeyFileQM.h"
#include "MusOOFile/KeyFileProsemus.h"
#include "MusOOFile/KeyFileMuDesc.h"
#include "MusOO/KeyQuaero.h"

namespace MusOO { namespace KeyFileUtil
{
	KeyFile* const newKeyFileFromExtension(const boost::filesystem::path& inFileName, const bool inPitchSpelled)
	{
		if (inFileName.extension() == ".lab")
		{
//			if ((inFileName.stem().string().size() >= 5 &&
//				!inFileName.stem().string().compare(inFileName.stem().string().size()-5,5,"-keys")) ||
//				(inFileName.stem().string().size() >=  8 &&
//				!inFileName.stem().string().compare(inFileName.stem().string().size()-8,8,"-globkey")) ||
//				(inFileName.stem().string().size() >=  10 &&
//				!inFileName.stem().string().compare(inFileName.stem().string().size()-10,10,"-globalkey")))
//			{
//				return new KeyFileElis(inFileName.string());
//			}
//			else
			{
				return new KeyFileQM(inFileName.string(), inPitchSpelled);
			}
		}
		else if (inFileName.extension() == ".txt")
		{
			return new KeyFileElis(inFileName.string(), inPitchSpelled);
		}
		else if (inFileName.extension() == ".key")
		{
			return new KeyFileProsemus(inFileName.string(), inPitchSpelled);
		}
		else if (inFileName.extension() == ".xml")
		{
			return new KeyFileMuDesc<KeyQuaero>(inFileName.string(), inPitchSpelled);
		}
		else
		{
			throw std::invalid_argument("Unknown extension " + inFileName.extension().string());
		}
	}

    const TimedKeySequence readKeySequenceFromFile(const boost::filesystem::path& inFilePath, const bool inPitchSpelled)
    {
        KeyFile* const theKeyFile = KeyFileUtil::newKeyFileFromExtension(inFilePath, inPitchSpelled);
        if (theKeyFile->isEmpty())
        {
            delete theKeyFile;
            throw std::runtime_error("The file " + inFilePath.string() + " does not contain any keys");
        }
        const TimedKeySequence retKeySequence = theKeyFile->readAll();
        delete theKeyFile;
        return retKeySequence;
    }

} }

#endif	// #ifndef KeyFileUtil_h
