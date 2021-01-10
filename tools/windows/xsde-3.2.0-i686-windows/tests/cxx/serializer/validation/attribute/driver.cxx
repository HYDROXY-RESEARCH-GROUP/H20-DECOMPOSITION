// file      : tests/cxx/serializer/validation/attribute/driver.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2006-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

// Test attribute and anyAttribute validation.
//

#include <sstream>
#include <iostream>

#include "test-sskel.hxx"

using namespace std;
using namespace test;

struct test_1_simpl: virtual test_1_sskel
{
  test_1_simpl (int state)
      :
#ifdef XSDE_REUSE_STYLE_TIEIN
      test_1_sskel (0),
#endif
      state_ (state)
  {
  }

  virtual int
  x ()
  {
    if (state_ == 0)
      state_ ++;

    return 123;
  }

  // ##any
  //
  virtual bool
  any_attribute_next ()
  {
    return state_ == 1;
  }

  virtual void
#ifdef XSDE_STL
  any_attribute (std::string& ns, std::string& name)
  {
#else
  any_attribute (const char*& ns, const char*& name, bool& free)
  {
    free = false;
#endif
    state_++;
    ns = "foo";
    name = "";
  }

  // ##other
  //
  virtual bool
  any_attribute1_next ()
  {
    return state_ > 1 && state_ < 4;
  }

  virtual void
#ifdef XSDE_STL
  any_attribute1 (std::string& ns, std::string& name)
  {
#else
  any_attribute1 (const char*& ns, const char*& name, bool& free)
  {
    free = false;
#endif
    switch (state_++)
    {
    case 2:
      {
        // target
        //
        ns = "test";
        name = "x";
        break;
      }
    case 3:
      {
        // local
        //
        ns = "";
        name = "x";
        break;
      }
    }
  }

  // ##local
  //
  virtual bool
  any_attribute2_next ()
  {
    return state_ == 4;
  }

  virtual void
#ifdef XSDE_STL
  any_attribute2 (std::string& ns, std::string& name)
  {
#else
  any_attribute2 (const char*& ns, const char*& name, bool& free)
  {
    free = false;
#endif
    state_++;
    ns = "foo";
    name = "x";
  }

  // ##targetNamespace
  //
  virtual bool
  any_attribute3_next ()
  {
    return state_ > 4 && state_ < 7;
  }

  virtual void
#ifdef XSDE_STL
  any_attribute3 (std::string& ns, std::string& name)
  {
#else
  any_attribute3 (const char*& ns, const char*& name, bool& free)
  {
    free = false;
#endif
    switch (state_++)
    {
    case 5:
      {
        // target
        //
        ns = "foo";
        name = "x";
        break;
      }
    case 6:
      {
        // local
        //
        ns = "";
        name = "x";
        break;
      }
    }
  }

  // foo
  //
  virtual bool
  any_attribute4_next ()
  {
    return state_ > 6 && state_ < 9;
  }

  virtual void
#ifdef XSDE_STL
  any_attribute4 (std::string& ns, std::string& name)
  {
#else
  any_attribute4 (const char*& ns, const char*& name, bool& free)
  {
    free = false;
#endif
    switch (state_++)
    {
    case 7:
      {
        // bar
        //
        ns = "bar";
        name = "x";
        break;
      }
    case 8:
      {
        // local
        //
        ns = "";
        name = "x";
        break;
      }
    }
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
  for (int i = 0; i < 9; ++i)
  {
#ifdef XSDE_EXCEPTIONS
    try
    {
#endif
      xml_schema::int_simpl int_s;
      test_1_simpl test_1_s (i);
      root_simpl root_s;

      if (i != 0)
        test_1_s.serializers (int_s);

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
