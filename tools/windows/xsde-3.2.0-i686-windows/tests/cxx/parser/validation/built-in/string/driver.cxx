// file      : tests/cxx/parser/validation/built-in/string/driver.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2006-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

// Test the built-in string & friends types validation.
//
#include <string>
#include <cassert>

#include <xsde/config.h>

// Let the runtime header sort out which version (stl/no-stl) to
// include.
//
#include <xsde/cxx/parser/validating/xml-schema-pimpl.hxx>

using namespace xsde::cxx;
using namespace xsde::cxx::parser;
using namespace xsde::cxx::parser::validating;

bool
compare (const string_sequence* x, const string_sequence& y)
{
  bool r = *x == y;
  delete x;
  return r;
}

int
main ()
{
  // We are going to leak a bit of memory in the no-STL case.
  //
  using std::string;

  // Good.
  //

  // string
  //
  {
    context c;
    string_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters (" \n\t");
    p._characters (" aaa ");
    p._characters ("bbb");
    p._characters (" ");
    p._post ();
    assert (!c.error_type () &&
            p.post_string () == string (" \n\t aaa bbb "));
  }

  // normalized_string
  //
  {
    context c;
    normalized_string_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters (" \n\t");
    p._characters (" aaa \n\t ");
    p._characters (" bbb");
    p._characters ("  ");
    p._post ();
    assert (!c.error_type () &&
            p.post_normalized_string () == string ("    aaa     bbb  "));
  }

  // token
  //
  {
    context c;
    token_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters (" \n\t");
    p._characters (" aaa \n\t ");
    p._characters (" bbb \n\t");
    p._characters ("  ");
    p._post ();
    assert (!c.error_type () &&
            p.post_token () == string ("aaa bbb"));
  }

  // name
  //
  {
    context c;
    name_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters (" \n\t");
    p._characters (" a:b-c_d123 ");
    p._characters ("  ");
    p._post ();
    assert (!c.error_type () &&
            p.post_name () == string ("a:b-c_d123"));
  }

  {
    context c;
    name_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters (" \n\t");
    p._characters (" _12 ");
    p._characters ("  ");
    p._post ();
    assert (!c.error_type () &&
            p.post_name () == string ("_12"));
  }

  {
    context c;
    name_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters (" \n\t");
    p._characters (" :12 ");
    p._characters ("  ");
    p._post ();
    assert (!c.error_type () &&
            p.post_name () == string (":12"));
  }

  // nmtoken
  //
  {
    context c;
    nmtoken_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters (" \n\t");
    p._characters (" 123a:b-c_d123 ");
    p._characters (" \n\t");
    p._characters ("  ");
    p._post ();
    assert (!c.error_type () &&
            p.post_nmtoken () == string ("123a:b-c_d123"));
  }

  // nmtokens
  //
  {
    context c;
    string_sequence s;
#ifdef XSDE_STL    
    s.push_back ("123");
    s.push_back ("abc");
#else
    s.push_back_copy ("123");
    s.push_back_copy ("abc");
#endif    

    nmtokens_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters (" \n\t");
    p._characters (" 123 ");
    p._characters (" \n\t abc ");
    p._characters ("  ");
    p._post ();
    assert (!c.error_type () && compare (p.post_nmtokens (), s));
  }

  // ncname
  //
  {
    context c;
    ncname_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters (" \n\t");
    p._characters (" a.b-c_d123 ");
    p._characters ("  ");
    p._post ();
    assert (!c.error_type () &&
            p.post_ncname () == string ("a.b-c_d123"));
  }

  // id
  //
  {
    context c;
    id_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters (" \n\t");
    p._characters (" a.b-c_d123 ");
    p._characters ("  ");
    p._post ();
    assert (!c.error_type () &&
            p.post_id () == string ("a.b-c_d123"));
  }

  // idref
  //
  {
    context c;
    idref_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters (" \n\t");
    p._characters (" a.b-c_d123 ");
    p._characters ("  ");
    p._post ();
    assert (!c.error_type () &&
            p.post_idref () == string ("a.b-c_d123"));
  }

  // idrefs
  //
  {
    context c;
    string_sequence s;
#ifdef XSDE_STL    
    s.push_back ("a123");
    s.push_back ("abc");
#else
    s.push_back_copy ("a123");
    s.push_back_copy ("abc");
#endif    

    idrefs_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters (" \n\t");
    p._characters (" a123 ");
    p._characters (" \n\t abc ");
    p._characters ("  ");
    p._post ();
    assert (!c.error_type () && compare (p.post_idrefs (), s));
  }

  // language
  //
  {
    context c;
    language_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters (" x ");
    p._post ();
    assert (!c.error_type () && p.post_language () == string ("x"));
  }

  {
    context c;
    language_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters (" en ");
    p._post ();
    assert (!c.error_type () && p.post_language () == string ("en"));
  }

  {
    context c;
    language_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters (" en");
    p._characters ("-us ");
    p._post ();
    assert (!c.error_type () && p.post_language () == string ("en-us"));
  }

  {
    context c;
    language_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("one-two-three-four44-seven77-eight888");
    p._post ();
    assert (!c.error_type () &&
            p.post_language () ==
            string ("one-two-three-four44-seven77-eight888"));
  }

  // Bad
  //

  // name
  //
  {
    context c;
    name_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("");
    p._post ();
    assert (c.schema_error ());
  }

  {
    context c;
    name_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters (".a");
    p._post ();
    assert (c.schema_error ());
  }

  {
    context c;
    name_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("-a");
    p._post ();
    assert (c.schema_error ());
  }

  {
    context c;
    name_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("1a");
    p._post ();
    assert (c.schema_error ());
  }

  {
    context c;
    name_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("a,b");
    p._post ();
    assert (c.schema_error ());
  }

  {
    context c;
    name_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("a b");
    p._post ();
    assert (c.schema_error ());
  }

  {
    context c;
    name_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("a<b");
    p._post ();
    assert (c.schema_error ());
  }

  // nmtoken
  //
  {
    context c;
    nmtoken_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("");
    p._post ();
    assert (c.schema_error ());
  }

  {
    context c;
    nmtoken_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("a,b");
    p._post ();
    assert (c.schema_error ());
  }

  {
    context c;
    nmtoken_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("a b");
    p._post ();
    assert (c.schema_error ());
  }

  {
    context c;
    nmtoken_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("a<b");
    p._post ();
    assert (c.schema_error ());
  }

  // nmtokens
  //
  {
    context c;
    nmtokens_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters (" ");
    p._characters (" \t\n  ");
    p._post_impl ();
    assert (c.schema_error () == schema_error::invalid_nmtokens_value);
  }

  {
    context c;
    nmtokens_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("ab a,b");
    p._post_impl ();
    assert (c.schema_error () == schema_error::invalid_nmtoken_value);
  }

  // ncname
  //
  {
    context c;
    ncname_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("");
    p._post ();
    assert (c.schema_error ());
  }

  {
    context c;
    ncname_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters (".a");
    p._post ();
    assert (c.schema_error ());
  }

  {
    context c;
    ncname_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("-a");
    p._post ();
    assert (c.schema_error ());
  }

  {
    context c;
    ncname_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters (":a");
    p._post ();
    assert (c.schema_error ());
  }

  {
    context c;
    ncname_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("1a");
    p._post ();
    assert (c.schema_error ());
  }

  {
    context c;
    ncname_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("a:b");
    p._post ();
    assert (c.schema_error ());
  }

  {
    context c;
    ncname_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("a,b");
    p._post ();
    assert (c.schema_error ());
  }

  {
    context c;
    ncname_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("a b");
    p._post ();
    assert (c.schema_error ());
  }

  {
    context c;
    ncname_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("a<b");
    p._post ();
    assert (c.schema_error ());
  }

  // id
  //
  {
    context c;
    id_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("a b");
    p._post ();
    assert (c.schema_error () == schema_error::invalid_id_value);
  }

  // idref
  //
  {
    context c;
    idref_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("a b");
    p._post ();
    assert (c.schema_error () == schema_error::invalid_idref_value);
  }

  // idrefs
  //
  {
    context c;
    idrefs_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("  ");
    p._characters (" \t\n ");
    p._post_impl ();
    assert (c.schema_error () == schema_error::invalid_idrefs_value);
  }

  {
    context c;
    idrefs_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("ab a<b");
    p._post_impl ();
    assert (c.schema_error () == schema_error::invalid_idref_value);
  }

  // language
  //
  {
    context c;
    language_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters (" ");
    p._post ();
    assert (c.schema_error () == schema_error::invalid_language_value);
  }

  {
    context c;
    language_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("en-");
    p._post ();
    assert (c.schema_error () == schema_error::invalid_language_value);
  }

  {
    context c;
    language_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("a1");
    p._post ();
    assert (c.schema_error () == schema_error::invalid_language_value);
  }

  {
    context c;
    language_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("en+us");
    p._post ();
    assert (c.schema_error () == schema_error::invalid_language_value);
  }

  {
    context c;
    language_pimpl p;
    p.pre ();
    p._pre_impl (c);
    p._characters ("en-nine99999");
    p._post ();
    assert (c.schema_error () == schema_error::invalid_language_value);
  }

  return 0;
}
