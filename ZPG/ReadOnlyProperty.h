#pragma once
template <typename T>
class ReadOnlyProperty {
public:
	virtual ~ReadOnlyProperty() {}
	virtual operator T const & () const { return value; }
protected:
	T value;
};
