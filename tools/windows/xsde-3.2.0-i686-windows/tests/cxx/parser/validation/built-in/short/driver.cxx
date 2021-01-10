// file      : tests/cxx/parser/validation/built-in/short/driver.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2006-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

// Test the built-in short and unsigned short types validation.
//
#include <cassert>

#include <xsde/cxx/parser/validating/short.hxx>
#include <xsde/cxx/parser/validating/unsigned-short.hxx>

using namespace xsde::cxx::parser;
using namespace xsde::cxx::parser::validating;

int
main ()
{
  // Good.
  //
  {
    context c;
    short_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("-32768");
    p._post ();
    assert (!c.error_type () && p.post_short () == -32768);
  }

  {
    context c;
    short_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("0");
    p._post ();
    assert (!c.error_type () && p.post_short () == 0);
  }

  {
    context c;
    short_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("32767");
    p._post ();
    assert (!c.error_type () && p.post_short () == 32767);
  }

  {
    context c;
    unsigned_short_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("0");
    p._post ();
    assert (!c.error_type () && p.post_unsigned_short () == 0);
  }

  {
    context c;
    unsigned_short_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("65535");
    p._post ();
    assert (!c.error_type () && p.post_unsigned_short () == 65535);
  }

  // Bad
  //

  {
    context c;
    unsigned_short_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("-1234");
    p._post ();
    assert (c.schema_error ());
  }


  // Ranges
  //
  {
    context c;
    short_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("-32769");
    p._post ();
    assert (c.schema_error ());
  }

  {
    context c;
    short_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("32768");
    p._post ();
    assert (c.schema_error ());
  }

  {
    context c;
    unsigned_short_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("65536");
    p._post ();
    assert (c.schema_error ());
  }

  return 0;
}
