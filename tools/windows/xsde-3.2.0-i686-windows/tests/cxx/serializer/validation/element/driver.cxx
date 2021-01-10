// file      : tests/cxx/serializer/validation/element/driver.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2006-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

// Test element validation.
//

#include <sstream>
#include <iostream>

#include "test-sskel.hxx"

using namespace std;
using namespace test;

struct test_1_simpl: virtual test_1_sskel
{
  test_1_simpl (int state)
      : state_ (state)
  {
  }

  virtual bool
  a_next ()
  {
    if (state_ == 0)
    {
      state_++;
      return true;
    }

    return false;
  }

  virtual int
  a ()
  {
    return 123;
  }

  virtual bool
  b_next ()
  {
    return false;
  }

  virtual int
  b ()
  {
    return 234;
  }

private:
  int state_;
};

struct root_simpl: root_sskel
{
};

int
main ()
{
  for (int i = 0; i < 2; ++i)
  {
#ifdef XSDE_EXCEPTIONS
    try
    {
#endif
      test_1_simpl test_1_s (i);
      root_simpl root_s;

      root_s.serializers (test_1_s);

      xml_schema::document_simpl doc_s (root_s, "test", "root");

      root_s.pre ();

      ostringstream os;
      doc_s.serialize (os);

#ifndef XSDE_EXCEPTIONS
      if (xml_schema::serializer_error e = doc_s._error ())
      {
        if (e.type () == xml_schema::serializer_error::schema)
        {
          cout << "schema: " << e.schema_text () << endl;
          continue;
        }
      }
#endif

      root_s.post ();
#ifdef XSDE_EXCEPTIONS
    }
    catch (xml_schema::serializer_schema const& e)
    {
      cout << "schema: " << e.text () << endl;
      continue;
    }
#endif

    cout << "no error" << endl;
  }

  return 0;
}
