#ifndef Chroma_h
#define Chroma_h

//============================================================================
/**
	Class representing a chroma.

	@author		Johan Pauwels
	@date		20100322
*/
//============================================================================
#include <string>
#include <map>
#include <limits>
#include <vector>
#include <ostream>

class Interval;

class Chroma
{
public:

	const static Chroma& silence();
	const static Chroma& none();
	const static Chroma& undefined();
	const static Chroma& Fb();
	const static Chroma& Cb();
	const static Chroma& Gb();
	const static Chroma& Db();
	const static Chroma& Ab();
	const static Chroma& Eb();
	const static Chroma& Bb();
	const static Chroma& F();
	const static Chroma& C();
	const static Chroma& G();
	const static Chroma& D();
	const static Chroma& A();
	const static Chroma& E();
	const static Chroma& B();
	const static Chroma& Fs();
	const static Chroma& Cs();
	const static Chroma& Gs();
	const static Chroma& Ds();
	const static Chroma& As();
	const static Chroma& Es();
	const static Chroma& Bs();

	static const std::vector<Chroma>& circleOfFifths(const Chroma& inStartChroma = Chroma::A());

	/** Default constructor. */
	Chroma();
	Chroma(const std::string& inName, const bool inHasSpelling = true);
	Chroma(const Chroma& inReference, const Interval& inInterval);

	virtual const std::string str() const;
	/** Destructor. */
	virtual ~Chroma();

	const bool hasSpelling() const;
	Chroma ignoreSpelling() const;

	const bool isTrueChroma() const;

	const bool operator==(const Chroma& inChroma) const;
	const bool operator!=(const Chroma& inChroma) const;
	Chroma& operator+=(const Interval& inInterval);
	Chroma& operator-=(const Interval& inInterval);
	bool operator<(const Chroma& inChroma) const;
	//const Chroma operator+(const Interval& inInterval) const; as friend function
	//const Chroma operator-(const Interval& inInterval) const;

	friend class Interval; //to access stringModifierToCircleSteps() and m_CirclePosition in Interval::Interval(...)

protected:

	static const int stringModifierToCircleSteps(const std::string& inStringModifier);

	static const std::map<char,int> s_NameToCirclePosition;
	static const std::map<int,char> s_CirclePositionToName;
	
	ptrdiff_t m_CirclePosition;
	bool m_HasSpelling;
	
private:
	//only for creation of static chromas
	Chroma(const int inCirclePosition, const bool inHasSpelling);

};

std::ostream& operator<<(std::ostream& inOutputStream, const Chroma& inChroma);

#endif	// #ifndef Chroma_h
