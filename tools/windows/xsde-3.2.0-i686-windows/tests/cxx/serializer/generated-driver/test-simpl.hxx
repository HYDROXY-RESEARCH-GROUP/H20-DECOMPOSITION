// file      : tests/cxx/serializer/generated-driver/test-simpl.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2006-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef TEST_SIMPL_HXX
#define TEST_SIMPL_HXX

#include "test-sskel.hxx"

namespace test
{
  class type_simpl: public virtual type_sskel
  {
  public:
    virtual void
    pre ();

    virtual int
    value ();

    virtual void
    post ();
  };
}

#endif // TEST_SIMPL_HXX
