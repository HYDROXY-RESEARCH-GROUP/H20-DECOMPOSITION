// file      : tests/cxx/parser/validation/built-in/binary/driver.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2006-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

// Test the built-in base64Binary and hexBinary types validation.
//
#include <cassert>
#include <string.h> // memcpy

#include <xsde/cxx/parser/validating/base64-binary.hxx>
#include <xsde/cxx/parser/validating/hex-binary.hxx>

using namespace xsde::cxx;
using namespace xsde::cxx::parser;
using namespace xsde::cxx::parser::validating;

bool
compare (buffer* x, const char* p, size_t n)
{
  buffer b;
  b.size (n);
  memcpy (b.data (), p, n);

  bool r = *x == b;
  delete x;
  return r;
}

int
main ()
{
  // Good.
  //

  // hexBinary
  //
  {
    context c;
    hex_binary_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters (" \t\n ");
    p._characters ("  ");
    p._post ();
    assert (!c.error_type () &&
            compare (p.post_hex_binary (), "", 0));
  }

  {
    context c;
    hex_binary_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters (" \t\n313");
    p._characters ("23334356162636a6b  ");
    p._post ();
    assert (!c.error_type () &&
            compare (p.post_hex_binary (), "12345abcjk", 10));
  }

  // base64Binary
  //
  {
    context c;
    base64_binary_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters (" \t\n ");
    p._characters ("MTIzND  ");
    p._characters ("VhYmNqaw = = ");
    p._post ();
    assert (!c.error_type () &&
            compare (p.post_base64_binary (), "12345abcjk", 10));
  }

  {
    context c;
    base64_binary_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("YQ==");
    p._post ();
    assert (!c.error_type () &&
            compare (p.post_base64_binary (), "a", 1));
  }

  {
    context c;
    base64_binary_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("YWI=");
    p._post ();
    assert (!c.error_type () &&
            compare (p.post_base64_binary (), "ab", 2));
  }

  {
    context c;
    base64_binary_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("YWJj");
    p._post ();
    assert (!c.error_type () &&
            compare (p.post_base64_binary (), "abc", 3));
  }

  // Bad
  //

  // hexBinary
  //
  {
    context c;
    hex_binary_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("313");
    p._post ();
    assert (c.schema_error () == schema_error::invalid_hex_binary_value);
  }

  {
    context c;
    hex_binary_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("313233343X6162636a6b");
    p._post ();
    assert (c.schema_error () == schema_error::invalid_hex_binary_value);
  }

  // base64Binary
  //
  {
    context c;
    base64_binary_pimpl p;
    p.pre ();
    p._pre_impl (c);
    // p._characters ("");
    p._post ();
    assert (c.schema_error () == schema_error::invalid_base64_binary_value);
  }

  {
    context c;
    base64_binary_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("YQ");
    p._post ();
    assert (c.schema_error () == schema_error::invalid_base64_binary_value);
  }

  {
    context c;
    base64_binary_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("==");
    p._post ();
    assert (c.schema_error () == schema_error::invalid_base64_binary_value);
  }

  {
    context c;
    base64_binary_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("MTIzNDVhYmNqaw=A");
    p._post ();
    assert (c.schema_error () == schema_error::invalid_base64_binary_value);
  }

  return 0;
}
