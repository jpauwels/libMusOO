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
class SimpleInterval;

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
	Chroma(const Chroma& inReference, const SimpleInterval& inInterval);

	virtual const std::string str() const;
	/** Destructor. */
	virtual ~Chroma();

	const bool hasSpelling() const;
    Chroma withoutSpelling() const;
    Chroma& ignoreSpelling();

	const bool isTrueChroma() const;

	const bool operator==(const Chroma& inChroma) const;
	const bool operator!=(const Chroma& inChroma) const;
	Chroma& operator+=(const SimpleInterval& inInterval);
	Chroma& operator-=(const SimpleInterval& inInterval);
	bool operator<(const Chroma& inChroma) const;
	//const Chroma operator+(const SimpleInterval& inInterval) const; as friend function
	//const Chroma operator-(const SimpleInterval& inInterval) const;

	friend class SimpleInterval; //to access stringModifierToCircleSteps() and m_LinePosition in SimpleInterval::SimpleInterval()

protected:

	static const ptrdiff_t stringModifierToCircleSteps(const std::string& inStringModifier);

	static const std::map<char,ptrdiff_t> s_NameToCirclePosition;
	static const std::map<ptrdiff_t,char> s_CirclePositionToName;
	
	ptrdiff_t m_LinePosition;
	bool m_HasSpelling;
	
private:
	//only for creation of static chromas
	Chroma(const ptrdiff_t inCirclePosition, const bool inHasSpelling);

};

std::ostream& operator<<(std::ostream& inOutputStream, const Chroma& inChroma);
}
#endif	// #ifndef Chroma_h
