// file      : tests/cxx/serializer/reset/driver.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2006-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

// Test serializer resetting.
//

#include <assert.h>

#include <string>
#include <sstream>
#include <iostream>

#include "test-sskel.hxx"

using namespace std;
using namespace test;

bool fail = true;

struct error {};

#ifdef XSDE_REUSE_STYLE_MIXIN
struct base_simpl: virtual base_sskel
#else
struct base_simpl: base_sskel
#endif
{
  base_simpl (unsigned long i)
      : i_ (i)
  {
  }

  virtual void
  pre ()
  {
#ifndef XSDE_EXCEPTIONS
    assert (!_error ());
#endif

    if (fail && i_ == 3)
    {
#ifdef XSDE_EXCEPTIONS
      throw error ();
#else
      _app_error (1);
#endif
    }
  }

private:
  unsigned long i_;
};

#ifdef XSDE_REUSE_STYLE_MIXIN
struct inner_simpl: inner_sskel, base_simpl
#else
struct inner_simpl: inner_sskel
#endif
{
  inner_simpl (unsigned long i)
#ifdef XSDE_REUSE_STYLE_MIXIN
      : base_simpl (i), i_ (i)
#else
          : inner_sskel (&base_impl_), base_impl_ (i), i_ (i)
#endif
  {
  }

  virtual void
  _pre ()
  {
    n_ = 0;
  }

  virtual bool
  b_next ()
  {
    if (fail && i_ == 6)
    {
#ifdef XSDE_SERIALIZER_VALIDATION
      return false;
#else
#ifdef XSDE_EXCEPTIONS
      throw error ();
#else
      _app_error (1);
#endif
      return true;
#endif
    }

    return n_++ == 0;
  }

  virtual int
  b ()
  {
    if (fail && i_ == 4)
    {
#ifdef XSDE_EXCEPTIONS
      throw error ();
#else
      _app_error (1);
#endif
    }

    return 1;
  }

  virtual void
  post ()
  {
    if (fail && i_ == 5)
    {
#ifdef XSDE_EXCEPTIONS
      throw error ();
#else
      _app_error (1);
#endif
    }
  }

private:
#ifdef XSDE_REUSE_STYLE_TIEIN
  base_simpl base_impl_;
#endif
  unsigned long i_;
  unsigned long n_;
};

struct type_simpl: type_sskel
{
  type_simpl (unsigned long i)
      : i_ (i)
  {
  }

  virtual void
  pre ()
  {
    if (fail && i_ == 0)
    {
#ifdef XSDE_EXCEPTIONS
      throw error ();
#else
      _app_error (1);
#endif
    }
  }

  virtual void
  a ()
  {
    if (fail && i_ == 1)
    {
#ifdef XSDE_EXCEPTIONS
      throw error ();
#else
      _app_error (1);
#endif
    }
  }

  virtual void
  post ()
  {
    if (fail && i_ == 2)
    {
#ifdef XSDE_EXCEPTIONS
      throw error ();
#else
      _app_error (1);
#endif
    }
  }

private:
  unsigned long i_;
};

int
main ()
{
  try
  {
    for (unsigned long i (0); i < 7; ++i)
    {
      xml_schema::int_simpl int_s;
      inner_simpl inner_s (i);
      type_simpl type_s (i);

      inner_s.serializers (int_s);
      type_s.serializers (inner_s);

      xml_schema::document_simpl doc_s (type_s, "test", "root");

      doc_s.add_prefix ("t", "test");
      doc_s.add_schema ("test", "test.xsd");

      ostringstream ostr;

      cout << i << ": ";

#ifdef XSDE_EXCEPTIONS
      try
      {
        fail = true;

        type_s.pre ();
        doc_s.serialize (ostr);
        type_s.post ();
        assert (false);
      }
      catch (error const&)
      {
      }
      catch (xml_schema::serializer_exception const&)
      {
      }

      fail = false;
      doc_s.reset ();

      type_s.pre ();
      doc_s.serialize (cout);
      type_s.post ();
#else
      do
      {
        fail = true;

        type_s.pre ();

        if (type_s._error ())
          break;

        doc_s.serialize (ostr);

        if (doc_s._error ())
          break;

        type_s.post ();

        if (type_s._error ())
          break;

        assert (false);
      }
      while (false);

      fail = false;
      doc_s.reset ();

      type_s.pre ();
      assert (!type_s._error ());

      doc_s.serialize (cout);
      assert (!doc_s._error ());

      type_s.post ();
      assert (!type_s._error ());
#endif

      cout << endl;
    }
  }
#ifdef XSDE_EXCEPTIONS
  catch (xml_schema::serializer_exception const& e)
  {
    cerr << e << endl;
    return 1;
  }
#endif
  catch (std::ios_base::failure const&)
  {
    cerr << "io failure" << endl;
    return 1;
  }

  return 0;
}
