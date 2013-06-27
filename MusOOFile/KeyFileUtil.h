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
#include "ElisKeyFile.h"
#include "QMKeyFile.h"
#include "ProsemusKeyFile.h"
#include "KeyFileMuDesc.h"
#include "KeyQuaero.h"

class KeyFileUtil
{
public:

	static KeyFile* newKeyFileFromExtension(boost::filesystem::path inFileName, const bool inPitchSpelled)
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
//				return new ElisKeyFile(inFileName.string());
//			}
//			else
			{
				return new QMKeyFile(inFileName.string(), inPitchSpelled);
			}
		}
		else if (inFileName.extension() == ".txt")
		{
			return new ElisKeyFile(inFileName.string(), inPitchSpelled);
		}
		else if (inFileName.extension() == ".key")
		{
			return new ProsemusKeyFile(inFileName.string(), inPitchSpelled);
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

protected:


private:


};

#endif	// #ifndef KeyFileUtil_h
