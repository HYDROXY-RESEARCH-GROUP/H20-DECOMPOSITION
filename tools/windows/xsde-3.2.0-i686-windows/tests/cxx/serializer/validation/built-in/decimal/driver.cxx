// file      : tests/cxx/serializer/validation/built-in/decimal/driver.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2006-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

// Test the built-in decimal type validation.
//
#include <stdlib.h> // strtod
#include <cassert>

#include <xsde/cxx/serializer/validating/decimal.hxx>

using namespace xsde::cxx;
using namespace xsde::cxx::serializer;
using namespace xsde::cxx::serializer::validating;

int
main ()
{
  {
    decimal_simpl s;
    context c (0);
    s.pre (strtod ("NAN", 0));
    s._pre_impl (c);
    s._serialize_content ();
    assert (c.schema_error () == schema_error::invalid_decimal_value);
  }

  {
    decimal_simpl s;
    context c (0);
    s.pre (strtod ("INF", 0));
    s._pre_impl (c);
    s._serialize_content ();
    assert (c.schema_error () == schema_error::invalid_decimal_value);
  }

  {
    decimal_simpl s;
    context c (0);
    s.pre (strtod ("-INF", 0));
    s._pre_impl (c);
    s._serialize_content ();
    assert (c.schema_error () == schema_error::invalid_decimal_value);
  }

  return 0;
}
