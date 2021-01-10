// file      : tests/cxx/parser/validation/built-in/float/driver.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2006-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

// Test the built-in float, double, and decimal types validation.
//
#include <math.h>
#include <cassert>

#include <xsde/cxx/parser/validating/float.hxx>
#include <xsde/cxx/parser/validating/double.hxx>
#include <xsde/cxx/parser/validating/decimal.hxx>

using namespace xsde::cxx::parser;
using namespace xsde::cxx::parser::validating;

int
main ()
{
  // Good.
  //

  // float
  //
  {
    context c;
    float_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters (" 0000123.456 ");
    p._post ();
    assert (!c.error_type () && p.post_float () == 123.456F);
  }

  {
    context c;
    float_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("-12.345E2");
    p._post ();
    assert (!c.error_type () && p.post_float () == -12.345E2F);
  }

  {
    context c;
    float_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("0");
    p._post ();
    assert (!c.error_type () && p.post_float () == 0.0F);
  }

  {
    context c;
    float_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("-0");
    p._post ();
    assert (!c.error_type () && p.post_float () == -0.0F);
  }

  {
    context c;
    float_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("INF");
    p._post ();
    assert (!c.error_type () && isinf (p.post_float ()));
  }

  {
    context c;
    float_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("-INF");
    p._post ();
    assert (!c.error_type () && isinf (p.post_float ()));
  }

  {
    context c;
    float_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("NaN");
    p._post ();
    assert (!c.error_type () && isnan (p.post_float ()));
  }

  // double
  //
  {
    context c;
    double_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters (" 0000123.456789 ");
    p._post ();
    assert (!c.error_type () && p.post_double () == 123.456789);
  }

  {
    context c;
    double_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("-12.3456789E2");
    p._post ();
    assert (!c.error_type () && p.post_double () == -12.3456789E2);
  }

  {
    context c;
    double_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("0");
    p._post ();
    assert (!c.error_type () && p.post_double () == 0.0);
  }

  {
    context c;
    double_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("-0");
    p._post ();
    assert (!c.error_type () && p.post_double () == -0.0);
  }

  {
    context c;
    double_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("INF");
    p._post ();
    assert (!c.error_type () && isinf (p.post_double ()));
  }

  {
    context c;
    double_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("-INF");
    p._post ();
    assert (!c.error_type () && isinf (p.post_double ()));
  }

  {
    context c;
    double_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("NaN");
    p._post ();
    assert (!c.error_type () && isnan (p.post_double ()));
  }

  // decimal
  //
  {
    context c;
    decimal_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters (" 0000123.456789 ");
    p._post ();
    assert (!c.error_type () && p.post_decimal () == 123.456789);
  }

  {
    context c;
    decimal_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("-123.45678912345");
    p._post ();
    assert (!c.error_type () && p.post_decimal () == -123.45678912345);
  }

  {
    context c;
    decimal_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("0");
    p._post ();
    assert (!c.error_type () && p.post_decimal () == 0.0);
  }

  {
    context c;
    decimal_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("-0");
    p._post ();
    assert (!c.error_type () && p.post_decimal () == -0.0);
  }


  // Bad
  //

  // float
  //
  {
    context c;
    float_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("+INF");
    p._post ();
    assert (c.schema_error ());
  }

  {
    context c;
    float_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("1.45 E2");
    p._post ();
    assert (c.schema_error ());
  }

  // double
  //
  {
    context c;
    double_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("+INF");
    p._post ();
    assert (c.schema_error ());
  }

  {
    context c;
    double_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("1.45 E2");
    p._post ();
    assert (c.schema_error ());
  }

  // decimal
  //
  {
    context c;
    decimal_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("INF");
    p._post ();
    assert (c.schema_error ());
  }

  {
    context c;
    decimal_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("+INF");
    p._post ();
    assert (c.schema_error ());
  }

  {
    context c;
    decimal_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("-INF");
    p._post ();
    assert (c.schema_error ());
  }

  {
    context c;
    decimal_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("NaN");
    p._post ();
    assert (c.schema_error ());
  }

  {
    context c;
    decimal_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("1.45 2");
    p._post ();
    assert (c.schema_error ());
  }

  return 0;
}
