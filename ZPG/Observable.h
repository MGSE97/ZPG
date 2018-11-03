#pragma once
#include "Collection.h"
#include "Observer.h"
#include <vector>

template <class T>
class Observable
{
public:
	Observable()
	{
		_observers = new Generic::Collection<Observer<T>*>();
	}
	virtual ~Observable()
	{
		_observers->clear();
		delete _observers;
	}
	void Bind(Observer<T> &observer)
	{
		_observers->Add(&observer);
	}
	void UnBind(Observer<T> &observer)
	{
		_observers->remove(observer);
	}
	void Notify()
	{
		for (auto it = _observers->begin(); it != _observers->end(); ++it)
			(*it)->Update(static_cast<T*>(this));
	}
private:
	Generic::Collection<Observer<T>*>* _observers;
};

/*template<typename T>
class Observable
{
private:
	T* _value;
	Generic::Collection<Observer<T>*>* _observers;
public:
	Observable(T* value = nullptr)
	{
		_value = value;
		_observers = new Generic::Collection<Observer<T>>();
	}
	~Observable()
	{
		delete _value;
	}
	Observable<T>* Set(T* value)
	{
		_value = value;
		Notify();
		return this;
	}
	T* Get()
	{
		return _value;
	}
	Observable<T> Notify()
	{
		for (auto observer : *_observers)
			observer->Update(this);
		return this;
	}
	Observable<T> Bind(Observer<T>* observer)
	{
		_observers->Add(observer);
		return this;
	}

	Observable<T> UnBind(Observer<T>* observer)
	{
		_observers->remove(observer);
		return this;
	}
};*/
