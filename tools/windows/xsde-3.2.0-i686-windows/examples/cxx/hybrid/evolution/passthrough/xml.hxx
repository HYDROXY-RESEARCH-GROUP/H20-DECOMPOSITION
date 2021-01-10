// file      : examples/cxx/hybrid/evolution/passthrough/xml.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : not copyrighted - public domain

//
// In-memory representation for raw XML. The primary goal here is to provide
// a simple, if not very efficient, implementation. As a result, it probably
// shouldn't be used in production, especially if performance is important.
// It also does not support mixed content (interleaved elements and text).
//

#ifndef XML_HXX
#define XML_HXX

#include <map>
#include <vector>
#include <string>

namespace xml
{
  // Qualified name.
  //
  class qname
  {
  public:
    qname (const char* name);
    qname (const std::string& name);
    qname (const std::string& ns, const std::string& name);

    const std::string&
    ns () const;

    const std::string&
    name () const;

  private:
    std::string ns_;
    std::string name_;
  };

  bool
  operator== (const qname&, const qname&);

  bool
  operator!= (const qname&, const qname&);

  bool
  operator< (const qname&, const qname&);

  // Attribute.
  //
  typedef std::map<qname, std::string> attributes;

  // Element.
  //
  class element;
  typedef std::vector<element*> elements;

  class element
  {
  public:
    ~element ();
    element (const qname& name, element* parent);
    element (const qname& name, const std::string value, element* parent);

  private:
    element (const element&);
    element& operator= (const element&);

  public:
    const qname&
    name () const;

    const element*
    parent () const;

    element*
    parent ();

    typedef xml::attributes attributes_type;

    const attributes_type&
    attributes () const;

    attributes_type&
    attributes ();

    const std::string&
    value () const;

    void
    value (const std::string&);

    const elements&
    children () const;

    elements&
    children ();

  private:
    qname name_;
    element* parent_;
    attributes_type attributes_;
    std::string value_;
    elements children_;
  };
}

#include "xml.ixx"

#endif // XML_HXX
