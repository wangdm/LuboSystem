#include "Variant.hpp"


namespace wdm {


	//////////////////////////////////////////////////////////////////////////
	//
	//////////////////////////////////////////////////////////////////////////

	Variant::Variant()
	{
		type = V_NULL;
		intVal = 0;
		doubleVal = 0.0;
		strVal = "";
	}

	Variant::Variant(const int val) :Variant()
	{
		type = V_INTEGER;
		intVal = val; 
	};


	Variant::Variant(const double val) :Variant()
	{
		type = V_DOUBLE;
		doubleVal = val;
	};


	Variant::Variant(const char* val) :Variant()
	{
		type = V_STRING;
		strVal = val;
	};


	Variant::Variant(const std::string val) :Variant()
	{
		type = V_STRING;
		strVal = val;
	};


	Variant::Variant(void*& val) :Variant()
	{
		type = V_OBJECT;
		ptrVal = val;
	};


	Variant* Variant::operator=(const int val)
	{
		this->type = V_INTEGER;
		this->intVal = val;
		return this;
	}


	Variant* Variant::operator=(const double val)
	{
		this->type = V_DOUBLE;
		this->doubleVal = val;
		return this;
	}


	Variant* Variant::operator=(const std::string val)
	{
		this->type = V_STRING;
		this->strVal = val;
		return this;
	}

}