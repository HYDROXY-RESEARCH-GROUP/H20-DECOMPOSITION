// file      : tests/cxx/serializer/validation/built-in/int/driver.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2006-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

// Test the built-in integer & friends types validation.
//

#include <cassert>

#include <xsde/cxx/serializer/validating/negative-integer.hxx>
#include <xsde/cxx/serializer/validating/non-positive-integer.hxx>
#include <xsde/cxx/serializer/validating/positive-integer.hxx>

using namespace xsde::cxx::serializer;
using namespace xsde::cxx::serializer::validating;
using namespace std;

int
main ()
{
  // negative_integer
  //
  {
    negative_integer_simpl s;
    context c (0);
    s.pre (0);
    s._pre_impl (c);
    s._serialize_content ();
    assert (c.schema_error ());
  }

  {
    negative_integer_simpl s;
    context c (0);
    s.pre (1);
    s._pre_impl (c);
    s._serialize_content ();
    assert (c.schema_error ());
  }

  // non_positive_integer
  //
  {
    non_positive_integer_simpl s;
    context c (0);
    s.pre (1);
    s._pre_impl (c);
    s._serialize_content ();
    assert (c.schema_error ());
  }

  // positive_integer
  //
  {
    positive_integer_simpl s;
    context c (0);
    s.pre (0);
    s._pre_impl (c);
    s._serialize_content ();
    assert (c.schema_error ());
  }

  return 0;
}
