// file      : examples/cxx/hybrid/evolution/passthrough/unknown-type-pimpl.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : not copyrighted - public domain

#include <memory> // std::auto_ptr

// Include transform-pimpl.hxx (which includes unknown-type-pimpl.hxx)
// instead of unknown-type-pimpl.hxx.
//
#include "transform-pimpl.hxx"

namespace transform
{
  void unknown_type_pimpl::
  _pre ()
  {
    unknown_type_base_pimpl::_pre ();

    // Set the element name and namespace.
    //
    unknown_type* obj = unknown_type_base_pimpl_state_.unknown_type_;

    obj->element_name (
      xml::qname (_context ().element_namespace (),
                  _context ().element_name ()));

    // Initialize the current element.
    //
    cur_ = &obj->content ();
  }

  void unknown_type_pimpl::
  _start_any_element (const xml_schema::ro_string& ns,
                      const xml_schema::ro_string& name,
                      const char*)
  {
    // Create a new child element and add it to cur_.
    //
    std::auto_ptr<xml::element> e (
      new xml::element (xml::qname (ns, name), cur_));

    cur_->children ().push_back (e.get ());
    cur_ = e.get ();
    e.release ();
  }

  void unknown_type_pimpl::
  _end_any_element (const xml_schema::ro_string&,
                    const xml_schema::ro_string&)
  {
    // Make the parent of cur_ the new cur_.
    //
    cur_ = cur_->parent ();
  }

  void unknown_type_pimpl::
  _any_attribute (const xml_schema::ro_string& ns,
                  const xml_schema::ro_string& name,
                  const xml_schema::ro_string& value)
  {
    // Add a new attribute to cur_.
    //
    cur_->attributes ()[xml::qname (ns, name)] = value;
  }

  void unknown_type_pimpl::
  _any_characters (const xml_schema::ro_string& s)
  {
    // Set the character value of cur_.
    //
    cur_->value (s);
  }

  //
  // Low-level content callbacks.
  //

  void unknown_type_pimpl::
  _start_element (const xml_schema::ro_string& ns,
                  const xml_schema::ro_string& name,
                  const char* type)
  {
    // If this is one of the elements from transformation_type, then
    // delegate it to our base. Otherwise, forward it to the wildcard
    // callback.
    //
    if (name == "description" &&
        ns == "http://www.codesynthesis.com/transform")
    {
      unknown_type_base_pimpl::_start_element (ns, name, type);
    }
    else
    {
      _context ().start_wildcard_content ();
      _start_any_element (ns, name, type);
    }
  }


  void unknown_type_pimpl::
  _end_element (const xml_schema::ro_string& ns,
                const xml_schema::ro_string& name)
  {
    // If this is one of the elements from transformation_type, then
    // delegate it to our base. Otherwise, forward it to the wildcard
    // callback.
    //
    if (name == "description" &&
        ns == "http://www.codesynthesis.com/transform")
    {
      unknown_type_base_pimpl::_end_element (ns, name);
    }
    else
      _end_any_element (ns, name);
  }

  void unknown_type_pimpl::
  _attribute (const xml_schema::ro_string& ns,
              const xml_schema::ro_string& name,
              const xml_schema::ro_string& value)
  {
    // If this is one of the elements from transformation_type, then
    // delegate it to our base. Otherwise, forward it to the wildcard
    // callback.
    //
    if (name == "name" && ns.empty ())
    {
      unknown_type_base_pimpl::_attribute (ns, name, value);
    }
    else
      _any_attribute (ns, name, value);
  }

  void unknown_type_pimpl::
  _characters (const xml_schema::ro_string& s)
  {
    // transformation_type has no character content so forward this
    // straight to the wildcard callback.
    //
    _any_characters (s);
  }
}
