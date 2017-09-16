#pragma once

#include "Object.hpp"

namespace wdm {

	typedef enum _VariantType {
		V_NULL = 0,
		V_BOOL,
		V_INTEGER,
		V_DOUBLE,
        V_STRING,
        V_OBJECT,
        V_ARRAY
	} VariantType;

	class Variant : public Object
    {

	public:
		Variant();
		Variant(const int val);
		Variant(const double val);
		Variant(const char* val);
		Variant(const std::string val);
        Variant(Object*& val);
        Variant(std::vector<Object*>& val);
        ~Variant() {
            std::cout << "Clear variant" << std::endl;
        };

    public:
        static Variant nil;

	public:
		Variant* operator=(const int val);
        Variant* operator=(const double val);
        Variant* operator=(const char* val);
        Variant* operator=(const std::string val);
        Variant* operator=(Object* const val);
        Variant* operator=(const std::vector<Object*> val);

		operator int() { return intVal; };
		operator double() { return doubleVal; };
        operator std::string() { return strVal; };
        operator Object*() { return ptrVal; };
        operator std::vector<Object*>() { return arrayVal; };

    public:
		VariantType type;

    private:
		int intVal;
		double doubleVal;
		std::string strVal;
        Object* ptrVal;
        std::vector<Object*> arrayVal;

	};

}