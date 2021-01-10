// file      : tests/cxx/serializer/validation/built-in/qname/driver.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2006-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

// Test the built-in QName type validation.
//
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
  {
    qname_simpl s;
    context c (0);
#ifdef XSDE_STL
    s.pre (qname ("a b"));
#else
    qname qn;
    qn.name_copy ("a b");
    s.pre (&qn);
#endif
    s._pre_impl (c);
    s._serialize_content ();
    assert (c.schema_error () == schema_error::invalid_qname_value);
  }

  {
    qname_simpl s;
    context c (0);
#ifdef XSDE_STL
    s.pre (qname ("ab", "a b"));
#else
    qname qn;
    qn.name_copy ("a b");
    qn.prefix_copy ("ab");
    s.pre (&qn);
#endif
    s._pre_impl (c);
    s._serialize_content ();
    assert (c.schema_error () == schema_error::invalid_qname_value);
  }

  {
    qname_simpl s;
    context c (0);
#ifdef XSDE_STL
    s.pre (qname ("a b", "ab"));
#else
    qname qn;
    qn.name_copy ("ab");
    qn.prefix_copy ("a b");
    s.pre (&qn);
#endif
    s._pre_impl (c);
    s._serialize_content ();
    assert (c.schema_error () == schema_error::invalid_qname_value);
  }

  return 0;
}
