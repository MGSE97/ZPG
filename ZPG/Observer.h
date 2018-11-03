#pragma once

/*template<typename T>
class Observer
{
private:
	Observable<T>* _value;
public:
	Observer()
	{
		_value = nullptr;
	}
	~Observer()
	{
	}

	virtual void Update(Observable<T>* value)
	{
		_value = value;
	}

	virtual T* Value()
	{
		return _value->Get();
	}
};*/
template <class T>
class Observer
{
public:
	Observer() {}
	virtual ~Observer() {}
	virtual void Update(T *value) = 0;
};