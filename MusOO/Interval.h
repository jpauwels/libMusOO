#ifndef Interval_h
#define Interval_h

//============================================================================
/**
	Class representing a musical interval.

	@author		Johan Pauwels
	@date		20100916
*/
//============================================================================
#include <string>
#include <map>
#include <vector>

class Chroma;
class Mode;

class Interval
{
public:

	const static Interval& silence();
	const static Interval& none();
	const static Interval& unknown();
	const static Interval& unison(); //1
	const static Interval& minorSecond(); //b2
	const static Interval& majorSecond(); //2
	const static Interval& minorThird(); //b3
	const static Interval& majorThird(); //3
	const static Interval& perfectFourth(); //4
	const static Interval& augmentedFourth(); //#4
	const static Interval& diminishedFifth(); //b5
	const static Interval& perfectFifth(); //5
	const static Interval& augmentedFifth(); //#5
	const static Interval& minorSixth(); //b6
	const static Interval& majorSixth(); //6
	const static Interval& augmentedSixth(); //#6
	const static Interval& diminishedSeventh(); //bb7
	const static Interval& minorSeventh(); //b7
	const static Interval& majorSeventh(); //7
	const static Interval& octave(); //8
	const static Interval& minorNinth(); //b9
	const static Interval& majorNinth(); //9
	const static Interval& augmentedNinth(); //#9
	const static Interval& diminishedEleventh(); //b11
	const static Interval& perfectEleventh(); //11
	const static Interval& augmentedEleventh(); //#11
	const static Interval& minorThirteenth(); //b13
	const static Interval& majorThirteenth(); //13

	friend class Chroma; 
	//to access m_CircleSteps in Chroma::operator+=(Interval), Chroma::operator+=(Interval) and Chroma::Chroma(Chroma, Interval)

	/** Default constructor. */
	Interval(const Chroma& inRoot, const Chroma& inOther, const bool inUp = true);
	Interval(const std::string& inMajorDegree, const bool inUp = true);
	Interval(const std::string& inDegree, const Mode& inMode);
	Interval(const int inSemiTones);

	// Operators
	bool operator==(const Interval& inInterval) const;
	bool operator!=(const Interval& inInterval) const;
	bool operator<(const Interval& inInterval) const;
	Interval& operator+=(const Interval& inInterval);
	Interval& operator-=(const Interval& inInterval);
	const Interval operator+(const Interval& inInterval) const;
	const Interval operator-(const Interval& inInterval) const;
	//Interval& operator-(); //inverse in-place
	//const Interval operator-() const; //inverse out-of-place

	// Observers
	const ptrdiff_t semiTonesUp() const;
	const ptrdiff_t semiTonesDown() const;
	const ptrdiff_t circleStepsCW() const;
	const ptrdiff_t circleStepsCCW() const;
	const std::string majorDegree() const;
	const ptrdiff_t diatonicNumber() const;

	const std::string asDegree(const Mode& inMode) const;

	/** Destructor. */
	virtual ~Interval();

	const bool hasSpelling() const;
	const Interval& ignoreSpelling();
	const bool isTrueInterval() const;

protected:


private:
	//only for creation of static distances
	Interval(const int inCircleSteps, const bool inHasSpelling, const size_t inOctaves);
	ptrdiff_t m_CircleSteps;
	size_t m_Octaves;
	bool m_HasSpelling;
	static const std::map<size_t,ptrdiff_t> s_MajorDegreeToCircleSteps;
	static const std::map<ptrdiff_t,size_t> s_CircleStepsToMajorDegree;
	static const std::vector<std::string> s_MajorDegrees;
	static const std::vector<std::string> s_MinorDegrees;

};

#endif	// #ifndef Interval_h
