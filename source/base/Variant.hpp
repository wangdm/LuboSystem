#pragma once

#include <string>
#include <map>

namespace wdm {

	typedef enum _VariantType {
		V_NULL = 0,
		V_BOOL,
		V_INTEGER,
		V_DOUBLE,
		V_STRING,
		V_OBJECT
	} VariantType;

	class Variant {

	public:
		Variant();
		Variant(const int val);
		Variant(const double val);
		Variant(const char* val);
		Variant(const std::string val);
		Variant(void*& val);
		~Variant() {};

	public:
		Variant* operator=(const int val);
		Variant* operator=(const double val);
		Variant* operator=(const std::string val);

		operator int() { return intVal; };
		operator double() { return doubleVal; };
		operator std::string() { return strVal; };

	private:
		VariantType type;

		int intVal;
		double doubleVal;
		std::string strVal;
		void* ptrVal;

	};

}