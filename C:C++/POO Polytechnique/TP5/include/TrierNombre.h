#ifndef TRIERNOMBRE_H
#define TRIERNOMBRE_H

template <class T>
class TrierNombre
{
public:
	TrierNombre(const T& attribut) : attribut_(attribut) {}
	bool operator()(const T& param) const {
		return (param < attribut_);
	}

private:
	T attribut_;
};

#endif