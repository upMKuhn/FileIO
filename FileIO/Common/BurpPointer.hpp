#pragma once
#include "Common.h"

namespace FileIO::Common {

	template<typename T>
	struct is_pointer { static const bool value = false; };

	template<typename T>
	struct is_pointer<T*> { static const bool value = true; };

	template <typename T>
	
	/// This class is a smarter pointer. It deletes the content once this class gets destoryed.
	/// hence the name burp!
	class BurpPointer
	{

	public:

		BurpPointer()
		{
			object = nullptr;
			deleter = [](T obj) {};
		}

		BurpPointer(T pointer)
		{
			object = pointer;
			this->deleter = [](T obj) { if (is_pointer<T>().value) delete obj; };
		}

		BurpPointer(T pointer, std::function<void(T)> deletef)
		{
			object = pointer;
			this->deleter = [deletef](T obj) { deletef(obj); };
		}

		~BurpPointer()
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

