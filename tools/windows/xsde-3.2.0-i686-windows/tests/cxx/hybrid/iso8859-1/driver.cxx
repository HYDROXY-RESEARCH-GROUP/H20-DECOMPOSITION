// file      : tests/cxx/hybrid/iso8859-1/driver.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2006-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

// Test support for the ISO-8859-1 encoding.
//

#include <assert.h>

#include <string>
#include <iostream>

#include "test.hxx"
#include "test-pimpl.hxx"
#include "test-simpl.hxx"

#include <xsde/cxx/iso8859-1.hxx>

using namespace std;
using namespace test;

int
main (int argc, char* argv[])
{
  if (argc != 2)
  {
    cerr << "usage: " << argv[0] << " test.xml" << endl;
    return 1;
  }

  // Parse.
  //
  root_paggr root_p;

  xml_schema::document_pimpl doc_p (
    root_p.root_parser (),
    root_p.root_namespace (),
    root_p.root_name ());

#ifdef XSDE_EXCEPTIONS
  try
  {
    root_p.pre ();
    doc_p.parse (argv[1]);
    type* r = root_p.post ();
    assert (false);
    delete r;
  }
  catch (const xml_schema::parser_exception& e)
  {
    // cerr << e.line () << ":" << e.column () << ": " << e.text () << endl;
  }
#else
  root_p.pre ();
  doc_p.parse (argv[1]);
  assert (doc_p._error ());
#endif

  doc_p.reset ();
  xml_schema::iso8859_1::unrep_char ('?');

  root_p.pre ();
  doc_p.parse (argv[1]);
  type* r = root_p.post ();

  assert (r->a ()[0] == string ("abc"));
  assert (r->a ()[1] == string ("\xE6"));
  assert (r->a ()[2] == string ("\xA2\xA3\xA4\xA5"));
  assert (r->a ()[3] == string ("???"));
  assert (r->a ()[4] == string ("longlonglonglonglonglonglonglonglonglonglonglong\xE6longlonglonglong"));

  assert (r->b ()[0] == strenum::abc);
  assert (r->b ()[1] == strenum::a_c);
  assert (r->b ()[1].string () == string ("a\xE2""c"));
  assert (r->b ()[2] == strenum::cxx__bc);

  assert (r->element_name_with_special_char__ () == string ("longlonglong\xA2\xA3\xA4\xA5longlong"));

  // Serialize.
  //
  root_saggr root_s;

  xml_schema::document_simpl doc_s (
    root_s.root_serializer (),
    root_s.root_namespace (),
    root_s.root_name ());

  doc_s.add_prefix ("t", "test");

  root_s.pre (*r);
  doc_s.serialize (cout);
  root_s.post ();

  delete r;

  return 0;
}
