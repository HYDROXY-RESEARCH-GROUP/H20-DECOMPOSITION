// file      : tests/cxx/parser/validation/all/driver.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2006-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

// Test the all compositor validation.
//

#include <string>
#include <iostream>

#include "test-pskel.hxx"

using namespace std;
using namespace test;

struct all_pimpl: all_pskel
{
  virtual void
  pre ()
  {
    cout << "{" << endl;
  }

#ifdef XSDE_STL
  virtual void
  a (string const& v)
  {
    cout << "  a = " << v << endl;
  }

  virtual void
  b (string const& v)
  {
    cout << "  b = " << v << endl;
  }

  virtual void
  c (string const& v)
  {
    cout << "  c = " << v << endl;
  }
#else
  virtual void
  a (char* v)
  {
    cout << "  a = " << v << endl;
    delete[] v;
  }

  virtual void
  b (char* v)
  {
    cout << "  b = " << v << endl;
    delete[] v;
  }

  virtual void
  c (char* v)
  {
    cout << "  c = " << v << endl;
    delete[] v;
  }
#endif

  virtual void
  post_all ()
  {
    cout << "}" << endl
         << endl;
  }
};

struct type_pimpl: type_pskel
{
};

int
main (int argc, char* argv[])
{
  if (argc != 2)
  {
    cerr << "usage: " << argv[0] << " test.xml" << endl;
    return 1;
  }

  try
  {
    xml_schema::string_pimpl string_p;
    all_pimpl all_p;
    type_pimpl type_p;

    all_p.parsers (string_p, string_p, string_p);
    type_p.parsers (all_p);

    xml_schema::document_pimpl doc_p (type_p, "test", "root");

    try
    {
      type_p.pre ();
      doc_p.parse (argv[1]);
      type_p.post_type ();
    }
    catch (xml_schema::parser_exception const& e)
    {
      cout << "  " << e.line () << ":" << e.column () << " " << e << endl
           << "}" << endl
           << endl;
    }
  }
  catch (xml_schema::parser_exception const& e)
  {
    cerr << e << endl;
    return 1;
  }
  catch (ios_base::failure const&)
  {
    cerr << "io failure" << endl;
    return 1;
  }

  return 0;
}
