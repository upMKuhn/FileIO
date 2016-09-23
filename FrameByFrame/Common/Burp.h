#pragma once
#include "Common.h"

#ifndef BURP_H_INCLUDED
#define BURP_H_INCLUDED
namespace Common {

	template<typename T>
	struct is_pointer { static const bool value = false; };

	template<typename T>
	struct is_pointer<T*> { static const bool value = true; };

	template <typename T>
	///This class is used best for classes and structs... 
	class Burp
	{

	public:

		Burp()
		{
			object = nullptr;
			deleter = [](T obj) {};
		}

		Burp(T pointer)
		{
			object = pointer;
			this->deleter = [](T obj) { if (is_pointer<T>().value) delete obj; };
		}

		Burp(T pointer, std::function<void(T)> deletef)
		{
			object = pointer;
			this->deleter = [deletef](T obj) { deletef(obj); };
		}

		~Burp()
		{
			cleanup();
		}

		T operator &() {
			cleanup();
			return is_pointer<T> ? object : &object;
		}
		
		T operator *() {
			return object;
		}

		T operator->()
		{
			return object;
		}

		///Exceptional conditions e.g.  initlaize object and set pointer at later stage
		T operator=(T newObj)
		{
			cleanup();
			object = newObj;
			return object;
		}

		operator T() const {
			return object;
		}

	private:

		T object;
		std::function<void(T)> deleter;

		//assuming memory leaks are acceptable during unit tests
#ifndef UNIT_TESTS
		void cleanup() {
			if (object != nullptr) {
				deleter(object);
			}
			object = nullptr;
		}
#else
		void cleanup() {
			object = nullptr;
		}
#endif
	};
}

#endif // !AUTODELETEOBJECT_H_INCLUDED