// file      : tests/cxx/serializer/test-template/driver.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2006-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

// Insert test description here.
//

#include <iostream>

#include "test-sskel.hxx"

using namespace std;
using namespace test;

struct root_simpl: root_sskel
{
  virtual void
  pre ()
  {
  }

  virtual int
  a ()
  {
    return 1234;
  }

  virtual void
  post_type ()
  {
  }
};

int
main ()
{
  xml_schema::int_simpl int_s;
  root_simpl root_s;

  root_s.serializers (int_s);

  xml_schema::document_simpl doc_s (root_s, "test", "root");

  root_s.pre ();
  doc_s.serialize (cout);
  root_s.post ();

  return 0;
}
