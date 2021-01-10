// file      : tests/cxx/parser/validation/built-in/long-long/driver.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2006-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

// Test the built-in long and unsigned long types validation.
//
#include <cassert>

#include <xsde/cxx/parser/validating/long-long.hxx>
#include <xsde/cxx/parser/validating/unsigned-long-long.hxx>

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
    p._characters ("-9223372036854775808");
    p._post ();
    assert (!c.error_type () &&
            p.post_long () == (-9223372036854775807LL - 1));
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
    p._characters ("9223372036854775807");
    p._post ();
    assert (!c.error_type () && p.post_long () == 9223372036854775807LL);
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
    p._characters ("18446744073709551615");
    p._post ();
    assert (!c.error_type () &&
            p.post_unsigned_long () == 18446744073709551615ULL);
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
    p._characters ("-9223372036854775809");
    p._post ();
    assert (c.schema_error ());
  }

  {
    context c;
    long_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("9223372036854775808");
    p._post ();
    assert (c.schema_error ());
  }

  {
    context c;
    unsigned_long_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("18446744073709551616");
    p._post ();
    assert (c.schema_error ());
  }

  return 0;
}
