// file      : tests/cxx/hybrid/clone/driver.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2006-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

// Test _clone() functionality.
//

#include <assert.h>
#include <iostream>

#include "test.hxx"
#include "test-pimpl.hxx"
#include "test-simpl.hxx"

using namespace std;
using namespace test;

void
data_destructor (void* p, size_t)
{
  delete static_cast<int*> (p);
}

void*
data_clone (void* p, size_t)
{
  return new int (*static_cast<int*> (p));
}

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

  root_p.pre ();
  doc_p.parse (argv[1]);
  type* r = root_p.post ();

  r->complex ().custom_data ().destructor (&data_destructor);
  r->complex ().custom_data ().clone (&data_clone);
  r->complex ().custom_data ().push_back (new int (123));

  type* c = r->_clone ();
  delete r;

  assert (c->complex ().custom_data ().size () == 1);
  assert (*static_cast<int*> (c->complex ().custom_data ()[0]) == 123);

  // Serialize.
  //
  root_saggr root_s;

  xml_schema::document_simpl doc_s (
    root_s.root_serializer (),
    root_s.root_namespace (),
    root_s.root_name ());

  doc_s.add_prefix ("t", "test");

  root_s.pre (*c);
  doc_s.serialize (cout, xml_schema::document_simpl::pretty_print);
  root_s.post ();

  delete c;

  return 0;
}
