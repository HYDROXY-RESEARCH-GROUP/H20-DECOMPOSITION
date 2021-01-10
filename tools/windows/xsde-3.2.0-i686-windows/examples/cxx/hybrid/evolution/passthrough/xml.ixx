// file      : examples/cxx/hybrid/evolution/passthrough/xml.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : not copyrighted - public domain

namespace xml
{
  //
  // qname
  //

  inline qname::
  qname (const char* name)
      : name_ (name)
  {
  }

  inline qname::
  qname (const std::string& name)
      : name_ (name)
  {
  }

  inline qname::
  qname (const std::string& ns, const std::string& name)
      : ns_ (ns), name_ (name)
  {
  }

  inline const std::string& qname::
  ns () const
  {
    return ns_;
  }

  inline const std::string& qname::
  name () const
  {
    return name_;
  }

  inline bool
  operator== (const qname& x, const qname& y)
  {
    return x.name () == y.name () && x.ns () == y.ns ();
  }

  inline bool
  operator!= (const qname& x, const qname& y)
  {
    return !(x == y);
  }

  inline bool
  operator< (const qname& x, const qname& y)
  {
    int r (x.name ().compare (y.name ()));
    return (r < 0) || (r == 0 && x.ns () < y.ns ());
  }

  //
  // element
  //

  inline element::
  element (const qname& name, element* parent)
      : name_ (name), parent_ (parent)
  {
  }

  inline element::
  element (const qname& name, const std::string value, element* parent)
      : name_ (name), parent_ (parent), value_ (value)
  {
  }

  inline const qname& element::
  name () const
  {
    return name_;
  }

  inline const element* element::
  parent () const
  {
    return parent_;
  }

  inline element* element::
  parent ()
  {
    return parent_;
  }

  inline const element::attributes_type& element::
  attributes () const
  {
    return attributes_;
  }

  inline element::attributes_type& element::
  attributes ()
  {
    return attributes_;
  }

  inline const std::string& element::
  value () const
  {
    return value_;
  }

  inline void element::
  value (const std::string& value)
  {
    value_ = value;
  }

  inline const elements& element::
  children () const
  {
    return children_;
  }

  inline elements& element::
  children ()
  {
    return children_;
  }
}
