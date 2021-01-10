// file      : tests/cxx/parser/recursive/driver.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2006-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

// Test recursive parser invocation.
//

#include <iostream>
#include <string>

#include "test-pskel.hxx"

using namespace std;

struct sub_pimpl: sub_type_pskel
{
  virtual void
  pre ()
  {
    cout << "sub::pre" << endl;
  }

  virtual void
  sub ()
  {
    cout << "sub::sub" << endl;
  }

  virtual void
  sub2 ()
  {
    cout << "sub::sub2" << endl;
  }

#ifdef XSDE_STL
  virtual void
  name (string const& n)
  {
    cout << "sub::name: " << n << endl;
  }
#else
  virtual void
  name (char* n)
  {
    cout << "sub::name: " << n << endl;
    delete[] n;
  }
#endif

  virtual void
  post_sub_type ()
  {
    cout << "sub::post" << endl;
  }
};

struct indir_pimpl: indir_type_pskel
{
  virtual void
  pre ()
  {
    cout << "indir::pre" << endl;
  }

  virtual void
  sub ()
  {
    cout << "indir::sub" << endl;
  }

#ifdef XSDE_STL
  virtual void
  name (string const& n)
  {
    cout << "indir::name: " << n << endl;
  }
#else
  virtual void
  name (char* n)
  {
    cout << "indir::name: " << n << endl;
    delete[] n;
  }
#endif

  virtual void
  post_indir_type ()
  {
    cout << "indir::post" << endl;
  }
};

struct a_pimpl: a_pskel
{
  virtual void
  pre ()
  {
    cout << "a::pre" << endl;
  }

  virtual void
  a ()
  {
    cout << "a::a" << endl;
  }

  virtual void
  b ()
  {
    cout << "a::b" << endl;
  }

#ifdef XSDE_STL
  virtual void
  name (string const& n)
  {
    cout << "a::name: " << n << endl;
  }
#else
  virtual void
  name (char* n)
  {
    cout << "a::name: " << n << endl;
    delete[] n;
  }
#endif

  virtual void
  post_a ()
  {
    cout << "a::post" << endl;
  }
};

struct b_pimpl: b_pskel
{
  virtual void
  pre ()
  {
    cout << "b::pre" << endl;
  }

#ifdef XSDE_STL
  virtual void
  name (string const& n)
  {
    cout << "b::name: " << n << endl;
  }
#else
  virtual void
  name (char* n)
  {
    cout << "b::name: " << n << endl;
    delete[] n;
  }
#endif

  virtual void
  post_b ()
  {
    cout << "b::post" << endl;
  }
};

struct test_pimpl: test_type_pskel
{
  virtual void
  pre ()
  {
    cout << "test::pre" << endl;
  }

  virtual void
  sub ()
  {
    cout << "test::sub" << endl;
  }

  virtual void
  a ()
  {
    cout << "test::a" << endl;
  }

#ifdef XSDE_STL
  virtual void
  name (string const& n)
  {
    cout << "test::name: " << n << endl;
  }
#else
  virtual void
  name (char* n)
  {
    cout << "test::name: " << n << endl;
    delete[] n;
  }
#endif

  virtual void
  post_test_type ()
  {
    cout << "test::post" << endl;
  }
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

    sub_pimpl sub_p;
    indir_pimpl indir_p;

    a_pimpl a_p;
    b_pimpl b_p;

    test_pimpl test_p;

    sub_p.parsers (string_p, sub_p, indir_p, sub_p);
    indir_p.parsers (string_p, sub_p);

    a_p.parsers (string_p, a_p, b_p);
    b_p.parsers (string_p);

    test_p.parsers (string_p, sub_p, a_p);

    xml_schema::document_pimpl doc_p (test_p, "test");

    test_p.pre ();
    doc_p.parse (argv[1]);
    test_p.post_test_type ();

    // Test parser resetting.
    //
    doc_p.reset ();
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
