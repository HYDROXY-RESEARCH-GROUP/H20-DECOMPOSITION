// file      : examples/cxx/hybrid/evolution/passthrough/unknown-type.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : not copyrighted - public domain

#ifndef UNKNOWN_TYPE_HXX
#define UNKNOWN_TYPE_HXX

#include "xml.hxx"

namespace transform
{
  // Customized unknown_type. We add members that store the raw XML
  // representation of an unknown transformation as well as the parsed
  // element name and namespace from the substitution group.
  //
  class unknown_type: public unknown_type_base
  {
  public:
    unknown_type ();

    const xml::qname&
    element_name () const
    {
      return name_;
    }

    void
    element_name (const xml::qname& n)
    {
      name_ = n;
    }

    const xml::element&
    content () const
    {
      return content_;
    }

    xml::element&
    content ()
    {
      return content_;
    }

  private:
    xml::qname name_;
    xml::element content_;
  };
}

#endif // UNKNOWN_TYPE_HXX
