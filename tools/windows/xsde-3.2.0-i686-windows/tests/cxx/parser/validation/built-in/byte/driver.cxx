// file      : tests/cxx/parser/validation/built-in/byte/driver.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2006-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

// Test the built-in byte and unsigned byte types validation.
//
#include <cassert>

#include <xsde/cxx/parser/validating/byte.hxx>
#include <xsde/cxx/parser/validating/unsigned-byte.hxx>

using namespace xsde::cxx::parser;
using namespace xsde::cxx::parser::validating;

int
main ()
{
  // Good.
  //
  {
    context c;
    byte_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("123");
    p._post ();
    assert (!c.error_type () && p.post_byte () == 123);
  }

  {
    context c;
    byte_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("\t +123 \n ");
    p._post ();
    assert (!c.error_type () && p.post_byte () == 123);
  }

  {
    context c;
    byte_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("-123");
    p._post ();
    assert (!c.error_type () && p.post_byte () == -123);
  }

  {
    context c;
    byte_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("+123");
    p._post ();
    assert (!c.error_type () && p.post_byte () == 123);
  }

  {
    context c;
    byte_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("0000000000000000123");
    p._post ();
    assert (!c.error_type () && p.post_byte () == 123);
  }

  {
    context c;
    byte_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("+0000000000000000123");
    p._post ();
    assert (!c.error_type () && p.post_byte () == 123);
  }

  {
    context c;
    byte_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("-0000000000000000123");
    p._post ();
    assert (!c.error_type () && p.post_byte () == -123);
  }

  {
    context c;
    byte_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("\t \n");
    p._characters (" -");
    p._characters ("00000");
    p._characters ("001");
    p._characters ("23   \n\t");
    p._post ();
    assert (!c.error_type () && p.post_byte () == -123);
  }

  {
    context c;
    byte_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("-128");
    p._post ();
    assert (!c.error_type () && p.post_byte () == -128);
  }

  {
    context c;
    byte_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("127");
    p._post ();
    assert (!c.error_type () && p.post_byte () == 127);
  }

  {
    context c;
    unsigned_byte_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("+123");
    p._post ();
    assert (!c.error_type () && p.post_unsigned_byte () == 123);
  }

  {
    context c;
    unsigned_byte_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("0");
    p._post ();
    assert (!c.error_type () && p.post_unsigned_byte () == 0);
  }

  {
    context c;
    unsigned_byte_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("255");
    p._post ();
    assert (!c.error_type () && p.post_unsigned_byte () == 255);
  }

  // Bad
  //
  {
    context c;
    byte_pimpl p;
    p.pre ();
    p._pre_impl (c);
    // p._characters ("");
    p._post ();
    assert (c.schema_error ());
  }

  {
    context c;
    byte_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("");
    p._post ();
    assert (c.schema_error ());
  }

  {
    context c;
    byte_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters (" \n \t ");
    p._post ();
    assert (c.schema_error ());
  }

  {
    context c;
    byte_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("+");
    p._post ();
    assert (c.schema_error ());
  }

  {
    context c;
    byte_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("-");
    p._post ();
    assert (c.schema_error ());
  }

  {
    context c;
    byte_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("++01");
    p._post ();
    assert (c.schema_error ());
  }

  {
    context c;
    byte_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("--01");
    p._post ();
    assert (c.schema_error ());
  }

  {
    context c;
    byte_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("-01");
    p._characters ("    ");
    p._characters ("23    ");
    p._post ();
    assert (c.schema_error ());
  }

  {
    context c;
    unsigned_byte_pimpl p;
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
    byte_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("-129");
    p._post ();
    assert (c.schema_error ());
  }

  {
    context c;
    byte_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("128");
    p._post ();
    assert (c.schema_error ());
  }

  {
    context c;
    unsigned_byte_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("256");
    p._post ();
    assert (c.schema_error ());
  }

  return 0;
}
