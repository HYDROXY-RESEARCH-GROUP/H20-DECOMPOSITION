// file      : examples/cxx/hybrid/custom/wildcard/envelope-simpl.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : not copyrighted - public domain

#include "body.hxx"

// Include email-simpl.hxx (which includes envelope-simpl.hxx)
// instead of envelope-simpl.hxx.
//
#include "email-simpl.hxx"

namespace email
{
  void envelope_simpl::
  _pre ()
  {
    // Initialize the body iterator.
    //
    i_ = envelope_base_simpl_state_.envelope_->body ().begin ();
  }

  bool envelope_simpl::
  any_next ()
  {
    envelope::body_const_iterator end (
      envelope_base_simpl_state_.envelope_->body ().end ());

    // See if there is a body that we know how to serialize.
    //
    for (; i_ != end; ++i_)
    {
      body::type t = i_->body_type ();

      if (t == body::type_text || t == body::type_binary)
        break;
    }

    return i_ != end;
  }

  void envelope_simpl::
  any (std::string& ns, std::string& name)
  {
    ns = "http://www.codesynthesis.com/email";

    switch (i_->body_type ())
    {
    case body::type_text:
      {
        name = "text";
        break;
      }
    case body::type_binary:
      {
        name = "binary";
        break;
      }
    default:
      break;
    }
  }

  void envelope_simpl::
  serialize_any ()
  {
    xml_schema::serializer_base* s = 0;
    const body& b = *i_++;

    // If you are not using exceptions then you will need to add
    // error propagation code. For more information on how to do
    // this see the wildcard example for the C++/Parser mapping
    // (examples/parser/ directory).
    //
    switch (b.body_type ())
    {
    case body::type_text:
      {
        text_s_->pre (b.text ());
        s = text_s_;
        break;
      }
    case body::type_binary:
      {
        binary_s_->pre (b.binary ());
        s = binary_s_;
        break;
      }
    default:
      break;
    }

    if (s != 0)
    {
      // If XML Schema validation is enabled then we need to check
      // for error conditions.
      //
      xml_schema::serializer_context& ctx = _context ();

      s->_pre_impl (ctx);

#ifdef XSDE_SERIALIZER_VALIDATION
      if (ctx.error_type ())
        return;
#endif
      s->_serialize_attributes ();

#ifdef XSDE_SERIALIZER_VALIDATION
      if (ctx.error_type ())
        return;
#endif
      s->_serialize_content ();

#ifdef XSDE_SERIALIZER_VALIDATION
      if (ctx.error_type ())
        return;
#endif
      s->_post_impl ();

#ifdef XSDE_SERIALIZER_VALIDATION
      if (ctx.error_type ())
        return;
#endif
      s->post ();
    }
  }

  void envelope_simpl::
  _reset ()
  {
    text_s_->_reset ();
    binary_s_->_reset ();

    // Note that we always need to call _reset() from the base.
    //
    envelope_base_simpl::_reset ();
  }
}
