// file      : tests/cxx/parser/list/driver.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2006-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

// Test xsd:list parsing.
//

#include <string>
#include <iostream>

#include "test-pskel.hxx"

using namespace std;
using namespace test;

struct string_list_pimpl: string_list_pskel
{
  virtual void
  pre ()
  {
    cout << "{" << endl;
  }

#ifdef XSDE_STL
  virtual void
  item (string const& v)
  {
    cout << "  '" << v << "'" << endl;
  }
#else
  virtual void
  item (char* v)
  {
    cout << "  '" << v << "'" << endl;
    delete[] v;
  }
#endif

  virtual void
  post_string_list ()
  {
    cout << "}" << endl
         << endl;
  }
};

struct string_list_lang_pimpl: string_list_lang_pskel
{
  string_list_lang_pimpl ()
      : string_list_lang_pskel (&base_impl_)
  {
  }

  virtual void
  pre ()
  {
    cout << "{" << endl;
  }

#ifdef XSDE_STL
  virtual void
  lang (string const& v)
  {
    cout << "  lang: '" << v << "'" << endl;
  }
#else
  virtual void
  lang (char* v)
  {
    cout << "  lang: '" << v << "'" << endl;
    delete[] v;
  }
#endif

  virtual void
  post_string_list_lang ()
  {
    cout << "}" << endl
         << endl;
  }

private:
  string_list_pimpl base_impl_;
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
    string_list_pimpl string_list_p;
    string_list_lang_pimpl string_list_lang_p;
    type_pimpl type_p;

    string_list_p.parsers (string_p);
    string_list_lang_p.parsers (string_p, string_p);
    type_p.parsers (string_list_p, string_list_lang_p);

    xml_schema::document_pimpl doc_p (type_p, "test", "root");

    type_p.pre ();
    doc_p.parse (argv[1]);
    type_p.post_type ();
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
