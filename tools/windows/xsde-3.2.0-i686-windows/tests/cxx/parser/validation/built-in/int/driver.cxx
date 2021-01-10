// file      : tests/cxx/parser/validation/built-in/int/driver.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2006-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

// Test the built-in int and unsigned int types validation.
//
#include <cassert>

#include <xsde/cxx/parser/validating/int.hxx>
#include <xsde/cxx/parser/validating/unsigned-int.hxx>

using namespace xsde::cxx::parser;
using namespace xsde::cxx::parser::validating;

int
main ()
{
  // Good.
  //
  {
    context c;
    int_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("-2147483648");
    p._post ();
    assert (!c.error_type () && p.post_int () == -2147483648);
  }

  {
    context c;
    int_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("0");
    p._post ();
    assert (!c.error_type () && p.post_int () == 0);
  }

  {
    context c;
    int_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("2147483647");
    p._post ();
    assert (!c.error_type () && p.post_int () == 2147483647);
  }

  {
    context c;
    unsigned_int_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("0");
    p._post ();
    assert (!c.error_type () && p.post_unsigned_int () == 0);
  }

  {
    context c;
    unsigned_int_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("4294967295");
    p._post ();
    assert (!c.error_type () && p.post_unsigned_int () == 4294967295);
  }

  // Bad
  //

  {
    context c;
    unsigned_int_pimpl p;
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
    int_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("-2147483649");
    p._post ();
    assert (c.schema_error ());
  }

  {
    context c;
    int_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("2147483648");
    p._post ();
    assert (c.schema_error ());
  }

  {
    context c;
    unsigned_int_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("4294967296");
    p._post ();
    assert (c.schema_error ());
  }

  return 0;
}
