// file      : examples/cxx/hybrid/evolution/passthrough/unknown-type-simpl.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : not copyrighted - public domain

// Include transform-simpl.hxx (which includes unknown-type-simpl.hxx)
// instead of unknown-type-simpl.hxx.
//
#include "transform-simpl.hxx"

namespace transform
{
  void unknown_type_simpl::
  _serialize_attributes ()
  {
    // Allow the base to serialize its attributes.
    //
    unknown_type_base_simpl::_serialize_attributes ();

    // Serialize attributes from the unknown content.
    //
    const xml::element& e =
      unknown_type_base_simpl_state_.unknown_type_->content ();

    serialize (e.attributes ());
  }

  void unknown_type_simpl::
  _serialize_content ()
  {
    // Allow the base to serialize its elements.
    //
    unknown_type_base_simpl::_serialize_content ();

    // Serialize elements from the unknown content.
    //
    const xml::element& e =
      unknown_type_base_simpl_state_.unknown_type_->content ();

    serialize (e.children ());
  }

  void unknown_type_simpl::
  serialize (const xml::attributes& as)
  {
    for (xml::attributes::const_iterator i (as.begin ()); i != as.end (); ++i)
    {
      const xml::qname& n = i->first;
      const std::string& v = i->second;

      if (n.ns ().empty ())
        _attribute (n.name ().c_str (), v.c_str ());
      else
        _attribute (n.ns ().c_str (), n.name ().c_str (), v.c_str ());
    }
  }

  void unknown_type_simpl::
  serialize (const xml::elements& es)
  {
    for (xml::elements::const_iterator i (es.begin ()); i != es.end (); ++i)
    {
      const xml::element& e = **i;
      const xml::qname& n = e.name ();

      if (n.ns ().empty ())
        _start_element (n.name ().c_str ());
      else
        _start_element (n.ns ().c_str (), n.name ().c_str ());

      serialize (e.attributes ());

      if (!e.children ().empty ())
        serialize (e.children ());
      else if (!e.value ().empty ())
        _characters (e.value ().c_str ());

      _end_element ();
    }
  }
}
