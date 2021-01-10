// file      : tests/cxx/serializer/validation/built-in/string/driver.cxx
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
#include <xsde/cxx/serializer/validating/xml-schema-simpl.hxx>

using namespace xsde::cxx;
using namespace xsde::cxx::serializer;
using namespace xsde::cxx::serializer::validating;

int
main ()
{
  // normalized_string
  //
  {
    normalized_string_simpl s;
    context c (0);
    s.pre ("aaa\nbbb");
    s._pre_impl (c);
    s._serialize_content ();
    assert (c.schema_error () == schema_error::invalid_normalized_string_value);
  }

  {
    normalized_string_simpl s;
    context c (0);
    s.pre ("aaa\tbbb");
    s._pre_impl (c);
    s._serialize_content ();
    assert (c.schema_error () == schema_error::invalid_normalized_string_value);
  }

  {
    normalized_string_simpl s;
    context c (0);
    s.pre ("aaa\rbbb");
    s._pre_impl (c);
    s._serialize_content ();
    assert (c.schema_error () == schema_error::invalid_normalized_string_value);
  }

  // token
  //
  {
    token_simpl s;
    context c (0);
    s.pre ("aaa\nbbb");
    s._pre_impl (c);
    s._serialize_content ();
    assert (c.schema_error () == schema_error::invalid_token_value);
  }

  {
    token_simpl s;
    context c (0);
    s.pre ("aaa\tbbb");
    s._pre_impl (c);
    s._serialize_content ();
    assert (c.schema_error () == schema_error::invalid_token_value);
  }

  {
    token_simpl s;
    context c (0);
    s.pre ("aaa\rbbb");
    s._pre_impl (c);
    s._serialize_content ();
    assert (c.schema_error () == schema_error::invalid_token_value);
  }

  {
    token_simpl s;
    context c (0);
    s.pre ("aaa  bbb");
    s._pre_impl (c);
    s._serialize_content ();
    assert (c.schema_error () == schema_error::invalid_token_value);
  }

  {
    token_simpl s;
    context c (0);
    s.pre (" aaa bbb");
    s._pre_impl (c);
    s._serialize_content ();
    assert (c.schema_error () == schema_error::invalid_token_value);
  }

  {
    token_simpl s;
    context c (0);
    s.pre ("aaa bbb ");
    s._pre_impl (c);
    s._serialize_content ();
    assert (c.schema_error () == schema_error::invalid_token_value);
  }

  // name
  //
  {
    name_simpl s;
    context c (0);
    s.pre ("");
    s._pre_impl (c);
    s._serialize_content ();
    assert (c.schema_error () == schema_error::invalid_name_value);
  }

  {
    name_simpl s;
    context c (0);
    s.pre (".a");
    s._pre_impl (c);
    s._serialize_content ();
    assert (c.schema_error () == schema_error::invalid_name_value);
  }

  {
    name_simpl s;
    context c (0);
    s.pre ("-a");
    s._pre_impl (c);
    s._serialize_content ();
    assert (c.schema_error () == schema_error::invalid_name_value);
  }

  {
    name_simpl s;
    context c (0);
    s.pre ("1a");
    s._pre_impl (c);
    s._serialize_content ();
    assert (c.schema_error () == schema_error::invalid_name_value);
  }

  {
    name_simpl s;
    context c (0);
    s.pre (" a");
    s._pre_impl (c);
    s._serialize_content ();
    assert (c.schema_error () == schema_error::invalid_name_value);
  }

  {
    name_simpl s;
    context c (0);
    s.pre ("a,b");
    s._pre_impl (c);
    s._serialize_content ();
    assert (c.schema_error () == schema_error::invalid_name_value);
  }

  {
    name_simpl s;
    context c (0);
    s.pre ("a b");
    s._pre_impl (c);
    s._serialize_content ();
    assert (c.schema_error () == schema_error::invalid_name_value);
  }

  {
    name_simpl s;
    context c (0);
    s.pre ("a<b");
    s._pre_impl (c);
    s._serialize_content ();
    assert (c.schema_error () == schema_error::invalid_name_value);
  }

  {
    name_simpl s;
    context c (0);
    s.pre ("a ");
    s._pre_impl (c);
    s._serialize_content ();
    assert (c.schema_error () == schema_error::invalid_name_value);
  }

  // nmtoken
  //
  {
    nmtoken_simpl s;
    context c (0);
    s.pre ("");
    s._pre_impl (c);
    s._serialize_content ();
    assert (c.schema_error () == schema_error::invalid_nmtoken_value);
  }

  {
    nmtoken_simpl s;
    context c (0);
    s.pre (" a");
    s._pre_impl (c);
    s._serialize_content ();
    assert (c.schema_error () == schema_error::invalid_nmtoken_value);
  }

  {
    nmtoken_simpl s;
    context c (0);
    s.pre ("a,b");
    s._pre_impl (c);
    s._serialize_content ();
    assert (c.schema_error () == schema_error::invalid_nmtoken_value);
  }

  {
    nmtoken_simpl s;
    context c (0);
    s.pre ("a b");
    s._pre_impl (c);
    s._serialize_content ();
    assert (c.schema_error () == schema_error::invalid_nmtoken_value);
  }

  {
    nmtoken_simpl s;
    context c (0);
    s.pre ("a<b");
    s._pre_impl (c);
    s._serialize_content ();
    assert (c.schema_error () == schema_error::invalid_nmtoken_value);
  }

  {
    nmtoken_simpl s;
    context c (0);
    s.pre ("a ");
    s._pre_impl (c);
    s._serialize_content ();
    assert (c.schema_error () == schema_error::invalid_nmtoken_value);
  }

  // nmtokens
  //
  {
    nmtokens_simpl s;
    context c (0);
    string_sequence seq;
    s.pre (&seq);
    s._pre_impl (c);
    s._serialize_content ();
    assert (c.schema_error () == schema_error::invalid_nmtokens_value);
  }

  {
    nmtokens_simpl s;
    context c (0);
    string_sequence seq;
#ifdef XSDE_STL
    seq.push_back ("a,b");
    seq.push_back ("ab");
#else
    seq.push_back_copy ("a,b");
    seq.push_back_copy ("ab");
#endif
    s.pre (&seq);
    s._pre_impl (c);
    s._serialize_content ();
    assert (c.schema_error () == schema_error::invalid_nmtoken_value);
  }

  // ncname
  //
  {
    ncname_simpl s;
    context c (0);
    s.pre ("");
    s._pre_impl (c);
    s._serialize_content ();
    assert (c.schema_error () == schema_error::invalid_ncname_value);
  }

  {
    ncname_simpl s;
    context c (0);
    s.pre (" a");
    s._pre_impl (c);
    s._serialize_content ();
    assert (c.schema_error () == schema_error::invalid_ncname_value);
  }

  {
    ncname_simpl s;
    context c (0);
    s.pre (".a");
    s._pre_impl (c);
    s._serialize_content ();
    assert (c.schema_error () == schema_error::invalid_ncname_value);
  }

  {
    ncname_simpl s;
    context c (0);
    s.pre ("-a");
    s._pre_impl (c);
    s._serialize_content ();
    assert (c.schema_error () == schema_error::invalid_ncname_value);
  }

  {
    ncname_simpl s;
    context c (0);
    s.pre (":a");
    s._pre_impl (c);
    s._serialize_content ();
    assert (c.schema_error () == schema_error::invalid_ncname_value);
  }

  {
    ncname_simpl s;
    context c (0);
    s.pre ("1a");
    s._pre_impl (c);
    s._serialize_content ();
    assert (c.schema_error () == schema_error::invalid_ncname_value);
  }

  {
    ncname_simpl s;
    context c (0);
    s.pre ("a,b");
    s._pre_impl (c);
    s._serialize_content ();
    assert (c.schema_error () == schema_error::invalid_ncname_value);
  }

  {
    ncname_simpl s;
    context c (0);
    s.pre ("a b");
    s._pre_impl (c);
    s._serialize_content ();
    assert (c.schema_error () == schema_error::invalid_ncname_value);
  }

  {
    ncname_simpl s;
    context c (0);
    s.pre ("a:b");
    s._pre_impl (c);
    s._serialize_content ();
    assert (c.schema_error () == schema_error::invalid_ncname_value);
  }

  {
    ncname_simpl s;
    context c (0);
    s.pre ("a<b");
    s._pre_impl (c);
    s._serialize_content ();
    assert (c.schema_error () == schema_error::invalid_ncname_value);
  }

  {
    ncname_simpl s;
    context c (0);
    s.pre ("a ");
    s._pre_impl (c);
    s._serialize_content ();
    assert (c.schema_error () == schema_error::invalid_ncname_value);
  }

  // id
  //
  {
    id_simpl s;
    context c (0);
    s.pre ("a b");
    s._pre_impl (c);
    s._serialize_content ();
    assert (c.schema_error () == schema_error::invalid_id_value);
  }

  // idref
  //
  {
    idref_simpl s;
    context c (0);
    s.pre ("a b");
    s._pre_impl (c);
    s._serialize_content ();
    assert (c.schema_error () == schema_error::invalid_idref_value);
  }

  // idrefs
  //
  {
    idrefs_simpl s;
    context c (0);
    string_sequence seq;
    s.pre (&seq);
    s._pre_impl (c);
    s._serialize_content ();
    assert (c.schema_error () == schema_error::invalid_idrefs_value);
  }

  {
    idrefs_simpl s;
    context c (0);
    string_sequence seq;
#ifdef XSDE_STL
    seq.push_back ("a,b");
    seq.push_back ("ab");
#else
    seq.push_back_copy ("a,b");
    seq.push_back_copy ("ab");    
#endif
    s.pre (&seq);
    s._pre_impl (c);
    s._serialize_content ();
    assert (c.schema_error () == schema_error::invalid_idref_value);
  }

  // language
  //
  {
    language_simpl s;
    context c (0);
    s.pre ("");
    s._pre_impl (c);
    s._serialize_content ();
    assert (c.schema_error () == schema_error::invalid_language_value);
  }

  {
    language_simpl s;
    context c (0);
    s.pre ("   ");
    s._pre_impl (c);
    s._serialize_content ();
    assert (c.schema_error () == schema_error::invalid_language_value);
  }

  {
    language_simpl s;
    context c (0);
    s.pre ("en-");
    s._pre_impl (c);
    s._serialize_content ();
    assert (c.schema_error () == schema_error::invalid_language_value);
  }

  {
    language_simpl s;
    context c (0);
    s.pre ("a1");
    s._pre_impl (c);
    s._serialize_content ();
    assert (c.schema_error () == schema_error::invalid_language_value);
  }

  {
    language_simpl s;
    context c (0);
    s.pre ("en+us");
    s._pre_impl (c);
    s._serialize_content ();
    assert (c.schema_error () == schema_error::invalid_language_value);
  }

  {
    language_simpl s;
    context c (0);
    s.pre ("en-nine99999");
    s._pre_impl (c);
    s._serialize_content ();
    assert (c.schema_error () == schema_error::invalid_language_value);
  }

  return 0;
}
