// file      : tests/cxx/parser/validation/built-in/int/driver.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2006-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

// Test the built-in integer & friends types validation.
//
#include <limits.h>

#include <string>
#include <sstream>
#include <cassert>

#include <xsde/cxx/parser/validating/integer.hxx>
#include <xsde/cxx/parser/validating/negative-integer.hxx>
#include <xsde/cxx/parser/validating/non-positive-integer.hxx>
#include <xsde/cxx/parser/validating/positive-integer.hxx>
#include <xsde/cxx/parser/validating/non-negative-integer.hxx>

using namespace std;
using namespace xsde::cxx::parser;
using namespace xsde::cxx::parser::validating;

int
main ()
{
  // Good.
  //

  std::string min;
  std::string max;
  std::string umax;

  {
    ostringstream ostr;
    ostr << LONG_MIN;
    min = ostr.str ();
  }

  {
    ostringstream ostr;
    ostr << LONG_MAX;
    max = ostr.str ();
  }

  {
    ostringstream ostr;
    ostr << ULONG_MAX;
    umax = ostr.str ();
  }

  // integer
  //
  {
    context c;
    integer_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters (min.c_str ());
    p._post ();
    assert (!c.error_type () && p.post_integer () == LONG_MIN);
  }

  {
    context c;
    integer_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("0");
    p._post ();
    assert (!c.error_type () && p.post_integer () == 0);
  }

  {
    context c;
    integer_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters (max.c_str ());
    p._post ();
    assert (!c.error_type () && p.post_integer () == LONG_MAX);
  }

  // negative_integer
  //
  {
    context c;
    negative_integer_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters (min.c_str ());
    p._post ();
    assert (!c.error_type () && p.post_negative_integer () == LONG_MIN);
  }

  {
    context c;
    negative_integer_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("-1");
    p._post ();
    assert (!c.error_type () && p.post_negative_integer () == -1);
  }

  // non_positive_integer
  //
  {
    context c;
    non_positive_integer_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters (min.c_str ());
    p._post ();
    assert (!c.error_type () && p.post_non_positive_integer () == LONG_MIN);
  }

  {
    context c;
    non_positive_integer_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("+0");
    p._post ();
    assert (!c.error_type () && p.post_non_positive_integer () == 0);
  }

  // positive_integer
  //
  {
    context c;
    positive_integer_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("1");
    p._post ();
    assert (!c.error_type () && p.post_positive_integer () == 1);
  }

  {
    context c;
    positive_integer_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters (umax.c_str ());
    p._post ();
    assert (!c.error_type () && p.post_positive_integer () == ULONG_MAX);
  }

  // non_negative_integer
  //
  {
    context c;
    non_negative_integer_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("-0");
    p._post ();
    assert (!c.error_type () && p.post_non_negative_integer () == 0);
  }

  {
    context c;
    non_negative_integer_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters (umax.c_str ());
    p._post ();
    assert (!c.error_type () && p.post_non_negative_integer () == ULONG_MAX);
  }


  // Bad
  //

  std::string past_min (min);
  std::string past_max (max);
  std::string past_umax (umax);

  assert (*past_min.rbegin () != '9');
  assert (*past_max.rbegin () != '9');
  assert (*past_umax.rbegin () != '9');

  (*past_min.rbegin ())++;
  (*past_max.rbegin ())++;
  (*past_umax.rbegin ())++;

  // integer
  //
  {
    context c;
    integer_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters (past_min.c_str ());
    p._post ();
    assert (c.schema_error ());
  }

  {
    context c;
    integer_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters (past_max.c_str ());
    p._post ();
    assert (c.schema_error ());
  }

  // negative_integer
  //
  {
    context c;
    negative_integer_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters (past_min.c_str ());
    p._post ();
    assert (c.schema_error ());
  }

  {
    context c;
    negative_integer_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("-0");
    p._post ();
    assert (c.schema_error ());
  }

  {
    context c;
    negative_integer_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("1");
    p._post ();
    assert (c.schema_error ());
  }

  // non_positive_integer
  //
  {
    context c;
    non_positive_integer_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters (past_min.c_str ());
    p._post ();
    assert (c.schema_error ());
  }

  {
    context c;
    non_positive_integer_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("1");
    p._post ();
    assert (c.schema_error ());
  }

  // positive_integer
  //
  {
    context c;
    positive_integer_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("-1");
    p._post ();
    assert (c.schema_error ());
  }

  {
    context c;
    positive_integer_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("+0");
    p._post ();
    assert (c.schema_error ());
  }

  {
    context c;
    positive_integer_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters (past_umax.c_str ());
    p._post ();
    assert (c.schema_error ());
  }

  // non_negative_integer
  //
  {
    context c;
    non_negative_integer_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("-1");
    p._post ();
    assert (c.schema_error ());
  }

  {
    context c;
    non_negative_integer_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters (past_umax.c_str ());
    p._post ();
    assert (c.schema_error ());
  }

  return 0;
}
