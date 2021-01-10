// file      : tests/cxx/parser/validation/built-in/long/driver.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2006-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

// Test built-in long and unsigned long types validation (32 bit fall-back).
//
#include <cassert>

#include <xsde/cxx/parser/validating/long.hxx>
#include <xsde/cxx/parser/validating/unsigned-long.hxx>

using namespace xsde::cxx::parser;
using namespace xsde::cxx::parser::validating;

int
main ()
{
  // Good.
  //
  {
    context c;
    long_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("-2147483648");
    p._post ();
    assert (!c.error_type () && p.post_long () == -2147483648);
  }

  {
    context c;
    long_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("0");
    p._post ();
    assert (!c.error_type () && p.post_long () == 0);
  }

  {
    context c;
    long_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("2147483647");
    p._post ();
    assert (!c.error_type () && p.post_long () == 2147483647);
  }

  {
    context c;
    unsigned_long_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("0");
    p._post ();
    assert (!c.error_type () && p.post_unsigned_long () == 0);
  }

  {
    context c;
    unsigned_long_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("4294967295");
    p._post ();
    assert (!c.error_type () && p.post_unsigned_long () == 4294967295);
  }

  // Bad
  //

  {
    context c;
    unsigned_long_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("-123");
    p._post ();
    assert (c.schema_error ());
  }


  // Ranges
  //
  {
    context c;
    long_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("-2147483649");
    p._post ();
    assert (c.schema_error ());
  }

  {
    context c;
    long_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("2147483648");
    p._post ();
    assert (c.schema_error ());
  }

  return 0;
}
