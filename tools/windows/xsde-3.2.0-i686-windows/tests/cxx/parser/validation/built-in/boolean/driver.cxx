// file      : tests/cxx/parser/validation/built-in/boolean/driver.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2006-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

// Test the built-in boolean type validation.
//
#include <cassert>

#include <xsde/cxx/parser/validating/boolean.hxx>

using namespace xsde::cxx::parser;
using namespace xsde::cxx::parser::validating;

int
main ()
{
  // Good.
  //
  {
    context c;
    boolean_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("true");
    p._post ();
    assert (!c.error_type () && p.post_boolean ());
  }

  {
    context c;
    boolean_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("1");
    p._post ();
    assert (!c.error_type () && p.post_boolean ());
  }

  {
    context c;
    boolean_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("false");
    p._post ();
    assert (!c.error_type () && !p.post_boolean ());
  }

  {
    context c;
    boolean_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("0");
    p._post ();
    assert (!c.error_type () && !p.post_boolean ());
  }


  {
    context c;
    boolean_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("  true  ");
    p._post ();
    assert (!c.error_type () && p.post_boolean ());
  }

  {
    context c;
    boolean_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters (" ");
    p._characters (" \n  ");
    p._characters ("   fa");
    p._characters ("l");
    p._characters ("se   ");
    p._characters (" \n  ");
    p._characters (" ");
    p._post ();
    assert (!c.error_type () && !p.post_boolean ());
  }

  // Bad
  //
  {
    context c;
    boolean_pimpl p;
    p.pre ();
    p._pre_impl (c);
    //p._characters ("");
    p._post ();
    assert (c.schema_error ());
  }

  {
    context c;
    boolean_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("");
    p._post ();
    assert (c.schema_error ());
  }

  {
    context c;
    boolean_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("  ");
    p._post ();
    assert (c.schema_error ());
  }

  {
    context c;
    boolean_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("                        ");
    p._post ();
    assert (c.schema_error ());
  }

  {
    context c;
    boolean_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("fal");
    p._characters ("s   ");
    p._characters ("e");
    p._post ();
    assert (c.schema_error ());
  }

  {
    context c;
    boolean_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("01");
    p._post ();
    assert (c.schema_error ());
  }

  return 0;
}
