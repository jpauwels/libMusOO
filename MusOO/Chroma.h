#ifndef Chroma_h
#define Chroma_h

//============================================================================
/**
	Class representing a chroma.

	@author		Johan Pauwels
	@date		20100322
*/
//============================================================================
#include <cstddef>
#include <string>
#include <map>
#include <limits>
#include <vector>
#include <ostream>

namespace MusOO
{
class Interval;

class Chroma
{
public:

	static const Chroma& silence();
	static const Chroma& none();
	static const Chroma& undefined();
	static Chroma Fb();
	static Chroma Cb();
	static Chroma Gb();
	static Chroma Db();
	static Chroma Ab();
	static Chroma Eb();
	static Chroma Bb();
	static Chroma F();
	static Chroma C();
	static Chroma G();
	static Chroma D();
	static Chroma A();
	static Chroma E();
	static Chroma B();
	static Chroma Fs();
	static Chroma Cs();
	static Chroma Gs();
	static Chroma Ds();
	static Chroma As();
	static Chroma Es();
	static Chroma Bs();

	static const std::vector<Chroma>& circleOfFifths(const Chroma& inStartChroma = Chroma::A(), const bool inHasSpelling = false);

	/** Default constructor. */
	Chroma();
	Chroma(const std::string& inName, const bool inHasSpelling = true);
	Chroma(const Chroma& inReference, const Interval& inInterval);

	virtual const std::string str() const;
	/** Destructor. */
	virtual ~Chroma();

	const bool hasSpelling() const;
    Chroma withoutSpelling() const;
    Chroma& ignoreSpelling();

	const bool isTrueChroma() const;

	const bool operator==(const Chroma& inChroma) const;
	const bool operator!=(const Chroma& inChroma) const;
	Chroma& operator+=(const Interval& inInterval);
	Chroma& operator-=(const Interval& inInterval);
	bool operator<(const Chroma& inChroma) const;
	//const Chroma operator+(const Interval& inInterval) const; as friend function
	//const Chroma operator-(const Interval& inInterval) const;

	friend class Interval; //to access stringModifierToCircleSteps() and m_LinePosition in Interval::Interval(...)

protected:

	static const int stringModifierToCircleSteps(const std::string& inStringModifier);

	static const std::map<char,int> s_NameToCirclePosition;
	static const std::map<int,char> s_CirclePositionToName;
	
	ptrdiff_t m_LinePosition;
	bool m_HasSpelling;
	
private:
	//only for creation of static chromas
	Chroma(const int inCirclePosition, const bool inHasSpelling);

};

std::ostream& operator<<(std::ostream& inOutputStream, const Chroma& inChroma);
}
#endif	// #ifndef Chroma_h
