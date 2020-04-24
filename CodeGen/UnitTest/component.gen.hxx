//generated time:1587752031
//generated end


#pragma once
#include <refl.rule.hxx>

using namespace Sakura::refl;

template<>
struct ClassInfo<Test::TestComponent>
{
	inline static const constexpr const char* GetClassName() 
	{
		return "Test::TestComponent";
	}
	inline static const constexpr Meta::MetaPiece meta[2] = 
	{
		{"descriptions", "This is a test component"},
		{"refl", "null"}
	};

	inline static const constexpr Meta::MetaPiece attrib_meta[1] = 
	{
		{"meta", "SaeruHikari"}
	};

	inline static const constexpr Meta::MetaPiece name_meta[1] = 
	{
		{"meta", "Fxxk ISO C++23"}
	};

	inline static const constexpr Meta::MetaPiece staticAttrib_meta[1] = 
	{
		{"meta", "This is a static attribute"}
	};

	inline static const constexpr Meta::MetaPiece Method_meta[1] = 
	{
		{"meta", "Can't wait to use compile-time-reflection"}
	};

	inline static const constexpr auto all_fields()
	{
		SFIELD_INFO(attrib, Test::TestComponent, attrib_meta);
		SFIELD_INFO(name, Test::TestComponent, name_meta);
		return hana::make_tuple(attrib_info(), name_info());
	}
	inline static const constexpr auto all_static_fields()
	{
		SSTATICFIELD_INFO(staticAttrib, Test::TestComponent, staticAttrib_meta);
		return hana::make_tuple(staticAttrib_info());
	}
	inline static const constexpr auto all_methods()
	{
		SMETHOD_INFO(Method, Test::TestComponent, Method_meta);
		return hana::make_tuple(Method_info());
	}
};

template<>
struct ClassInfo<Test::TestComponentWrap>
{
	inline static const constexpr const char* GetClassName() 
	{
		return "Test::TestComponentWrap";
	}
	inline static const constexpr Meta::MetaPiece meta[1] = 
	{
		{"refl", "null"}
	};

	inline static const constexpr Meta::MetaPiece comp_meta[1] = 
	{
		{"description", "Test wrapping of reflection component"}
	};

	inline static const constexpr auto all_fields()
	{
		SFIELD_INFO(comp, Test::TestComponentWrap, comp_meta);
		SFIELD_INFO(wtf, Test::TestComponentWrap, nullptr);
		return hana::make_tuple(comp_info(), wtf_info());
	}
	inline static const constexpr auto all_static_fields()
	{
		SSTATICFIELD_INFO(statComp, Test::TestComponentWrap, nullptr);
		return hana::make_tuple(statComp_info());
	}
};

template<>
struct EnumInfo<Test::TestEnum>
{
	inline static const constexpr const char* GetEnumName() 
	{
		return "Test::TestEnum";
	}
	inline static const constexpr Meta::MetaPiece meta[1] = 
	{
		{"refl", "null"}
	};

	inline static const constexpr Meta::MetaPiece E_ONE_meta[1] = 
	{
		{"enum", "This is enum one"}
	};

	inline static const constexpr Meta::MetaPiece E_TWO_meta[1] = 
	{
		{"enum", "This is enum two"}
	};

	inline static const constexpr Meta::MetaPiece E_THREE_meta[1] = 
	{
		{"enum", "This is enum three"}
	};

	inline static const constexpr auto all_static_fields()
	{
		SENUM_FIELD_INFO(E_ONE, Test::TestEnum, E_ONE_meta);
		SENUM_FIELD_INFO(E_TWO, Test::TestEnum, E_TWO_meta);
		SENUM_FIELD_INFO(E_THREE, Test::TestEnum, E_THREE_meta);
		return hana::make_tuple(E_ONE_info(), E_TWO_info(), E_THREE_info());
	}
};

