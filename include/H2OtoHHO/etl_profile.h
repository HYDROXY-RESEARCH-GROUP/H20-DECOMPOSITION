/*
  etl_profile.h

  Macros
    Many of the features or options in the ETL can be selected by defining the appropriate
     macros.Some macros are defined by the ETL.
  
  // ____________________________________________________________________________________________________
  User defined

    These must be defined in the user created etl_profile.h.
*/

// ensure this library description is only included once
#ifndef ETL_PROFILE_H
#define ETL_PROFILE_H

/* Global ETL Features Macro Definitions  */
// ____________________________________________________________________________________________________

/*
  ETL_ASSERT has no effect.
*/
// #define ETL_NO_CHECKS
// ____________________________________________________________________________________________________

/*
  ETL_ASSERT throws the specified exception.
*/
// #define ETL_THROW_EXCEPTIONS
// ____________________________________________________________________________________________________

/*
  ETL_ASSERT calls the error handler then throws an exception.
*/
// #define ETL_THROW_EXCEPTIONS +ETL_LOG_ERRORS
// ____________________________________________________________________________________________________

/*
  ETL_ASSERT calls the error handler then asserts.
*/
// #define ETL_LOG_ERRORS

// ____________________________________________________________________________________________________
/*
  ETL_ASSERT calls the error handler.
*/
// #define ETL_LOG_ERRORS +NDEBUG
// ____________________________________________________________________________________________________
/*
  Pushes and pops to containers are checked for bounds.
*/
// #define ETL_CHECK_PUSH_POP
// ____________________________________________________________________________________________________
/*
  If this is defined then error messages and ouput in their long form.
*/
// #define ETL_VERBOSE_ERRORS
// ____________________________________________________________________________________________________
/*
  If this is defined, then it will become the type used for elements in the bitset class.
  Default is uint_least8_t
*/
//  #define ETL_BITSET_ELEMENT_TYPE
// ____________________________________________________________________________________________________
/*
  If this is defined, then it will become the type used for FSM state id numbers.
  Default is uint_least8_t
*/
//  #define ETL_FSM_STATE_ID_TYPE
// ____________________________________________________________________________________________________
/*
  If this is defined, then it will become the type used for message id numbers.
  Default is uint_least8_t
*/
//  #define ETL_MESSAGE_ID_TYPE
// ____________________________________________________________________________________________________
/*
  If this is defined, then it will become the type used for the type for the timer guard variable.
  This must be a type that cannot be interrupted during a read/modify/write cycle.
  Default is etl::atomic_uint32_t
*/
//  #define ETL_TIMER_GUARD_TYPE
// ____________________________________________________________________________________________________
/*
  Define this if you wish to memcpy ETL strings and repair them via an istring pointer or reference.
  Warning: This will make the container a virtual class.
*/
// #define ETL_ISTRING_REPAIR_ENABLE
// ____________________________________________________________________________________________________
/*
  Define this if you wish to memcpy ETL vectors and repair them via an ivector pointer or reference.
  Warning: This will make the container a virtual class.
*/
// #define ETL_IVECTOR_REPAIR_ENABLE
// ____________________________________________________________________________________________________
/*
  Define this if you wish to memcpy ETL deques and repair them via an ideque pointer or reference.
  Warning : This will make the container a virtual class.
*/
// #define ETL_IDEQUE_REPAIR_ENABLE
// ____________________________________________________________________________________________________
/*
  This must be defined in the user library profile when using STLPort as the standard library implementation.
*/
//  #define ETL_STLPORT
// ____________________________________________________________________________________________________
/*
  If defined, the ETL will not use definitions from the STL.Instead it will use its own reverse engineered versions.
*/
//#define ETL_NO_STL
// ____________________________________________________________________________________________________

/*
  If defined, the ETL will force string, wstring, u16string, u32string and string_view to have explicit construction from a character pointer.
*/
//  #define ETL_FORCE_EXPLICIT_STRING_CONVERSION_FROM_CHAR
// ____________________________________________________________________________________________________
/*
  If defined, then a string truncation will result in an etl::string_truncation error being emitted.
*/
//  #define ETL_STRING_TRUNCATION_IS_ERROR
// ____________________________________________________________________________________________________
/*
  Defining any one of these will make the corresponding ETL_POLYMORPHIC_DEQUE container polymorphic, 
  turning the protected non-virtual destructor to public virtual.
*/
//  #define ETL_POLYMORPHIC_BITSET
//  #define ETL_POLYMORPHIC_FLAT_MAP
//  #define ETL_POLYMORPHIC_FLAT_MULTIMAP
//  #define ETL_POLYMORPHIC_FLAT_SET
//  #define ETL_POLYMORPHIC_FLAT_MULTISET
//  #define ETL_POLYMORPHIC_FORWARD_LIST
//  #define ETL_POLYMORPHIC_LIST
//  #define ETL_POLYMORPHIC_MAP
//  #define ETL_POLYMORPHIC_MULTIMAP
//  #define ETL_POLYMORPHIC_SET
//  #define ETL_POLYMORPHIC_MULTISET
//  #define ETL_POLYMORPHIC_QUEUE
//  #define ETL_POLYMORPHIC_STACK
//  #define ETL_POLYMORPHIC_REFERENCE_FLAT_MAP
//  #define ETL_POLYMORPHIC_REFERENCE_FLAT_MULTIMAP
//  #define ETL_POLYMORPHIC_REFERENCE_FLAT_SET
//  #define ETL_POLYMORPHIC_REFERENCE_FLAT_MULTISET
//  #define ETL_POLYMORPHIC_UNORDERED_MAP
//  #define ETL_POLYMORPHIC_UNORDERED_MULTIMAP
//  #define ETL_POLYMORPHIC_UNORDERED_SET
//  #define ETL_POLYMORPHIC_UNORDERED_MULTISET
//  #define ETL_POLYMORPHIC_STRINGS
//  #define ETL_POLYMORPHIC_POOL
//  #define ETL_POLYMORPHIC_VECTOR
// ____________________________________________________________________________________________________
/*
  If defined then all containers are polymorphic.
*/
//  #define ETL_POLYMORPHIC_CONTAINERS
// ____________________________________________________________________________________________________
/*
  If defined then etl::imessage is virtual.
  ETL_MESSAGES_ARE_VIRTUAL is deprecated and may be removed.
*/
//  #define ETL_POLYMORPHIC_MESSAGES
// ____________________________________________________________________________________________________

//These may be user defined in etl_profile.h, or automatically determined in platform.h
//  #define ETL_CPP11_SUPPORTED                        //This is defined as 1 if the compiler supports C++11. Otherwise 0.
//  #define ETL_CPP14_SUPPORTED                        //This is defined as 1 if the compiler supports C++14. Otherwise 0.
//  #define ETL_CPP17_SUPPORTED                        //This is defined as 1 if the compiler supports C++17. Otherwise 0.
//  #define ETL_NO_NULLPTR_SUPPORT                     //This is defined as 1 if compiler does not support nullptr. Otherwise 0.
//  #define ETL_NO_LARGE_CHAR_SUPPORT                  //This is defined as 1 if the compiler does not support char16_t or char32_t types. Otherwise 0.
//  #define ETL_CPP11_TYPE_TRAITS_IS_TRIVIAL_SUPPORTED //This is defined as 1 if compiler supports  the std::is_trivially_xxx set of traits. Otherwise 0.

/*
ETL_COMPILER_IAR                                //One of these will be defined.
ETL_COMPILER_GREEN_HILLS
ETL_COMPILER_INTEL
ETL_COMPILER_MICROSOFT
ETL_COMPILER_GCC
ETL_COMPILER_CLANG
ETL_COMPILER_ARM
ETL_COMPILER_TEXAS_INSTRUMENTS
ETL_COMPILER_GENERIC
*/

//  #define ETL_COMPILER_VERSION       //These will be defined as the compiler version numbers,ETL_COMPILER_FULL_VERSION if available.
//  #define ETL_DEVELOPMENT_OS_WINDOWS //One of these will be defined.ETL_DEVELOPMENT_OS_LINUXETL_DEVELOPMENT_OS_UNIXETL_DEVELOPMENT_OS_APPLEETL_DEVELOPMENT_OS_BSDETL_DEVELOPMENT_OS_GENERIC
//  #define ETL_NO_CPP_NAN_SUPPORT     //If defined, indicates that the compiler does not support nan(),nanf() or nanl(). Automatically defined if using CodeWorks for ARM

#endif