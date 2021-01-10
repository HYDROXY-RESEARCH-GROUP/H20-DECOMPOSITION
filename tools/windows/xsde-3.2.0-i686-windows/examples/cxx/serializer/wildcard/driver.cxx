// file      : examples/cxx/serializer/wildcard/driver.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : not copyrighted - public domain

#include <iostream>

#include "email-sskel.hxx"

#ifndef XSDE_REUSE_STYLE_TIEIN
#  error this example requires the tiein serializer reuse support
#endif

using namespace std;

namespace email
{
  struct binary_simpl: binary_sskel
  {
    // Indicate to base64_binary_simpl that we want it to release
    // the buffer passed via pre().
    //
    binary_simpl ()
        : binary_sskel (&base_impl_), base_impl_ (true)
    {
    }

    virtual void
    pre (const binary* bin)
    {
      using namespace xml_schema;

      bin_ = bin;
      buffer* buf = new buffer (bin->data (), bin->size ());
      base_impl_.pre (buf);
    }

    virtual std::string
    name ()
    {
      return bin_->name ();
    }

    virtual std::string
    mime ()
    {
      return bin_->mime ();
    }

  private:
    xml_schema::base64_binary_simpl base_impl_;
    const binary* bin_;
  };

  struct envelope_simpl: envelope_sskel
  {
    envelope_simpl (xml_schema::string_simpl& text_s,
                    binary_sskel& bin_s,
                    xml_schema::unsigned_int_simpl& uint_s)
        : text_s_ (text_s), bin_s_ (bin_s), uint_s_ (uint_s)
    {
    }

    virtual void
    pre (const envelope& env)
    {
      env_ = &env;
      tid_set_ = false;
      i_ = env_->begin_body ();
    }

    // Attributes.
    //
    virtual bool
    any_attribute_next ()
    {
      return !tid_set_;
    }

    virtual void
    any_attribute (std::string& ns, std::string& name)
    {
      ns = "http://www.codesynthesis.com/email";
      name = "thread-id";
    }

    virtual void
    serialize_any_attribute ()
    {
      // This function is where we perform the actual wildcard
      // serialization.
      //
      xml_schema::serializer_context& ctx = _context ();

#if defined(XSDE_EXCEPTIONS) && !defined(XSDE_SERIALIZER_VALIDATION)

      uint_s_.pre (env_->thread_id ());
      uint_s_._pre_impl (ctx);
      uint_s_._serialize_content ();
      uint_s_._post_impl ();
      uint_s_.post ();
#else
      // If we are not using exceptions or XML Schema validation
      // is enabled then we need to check for the error condition
      // and, if the (user) error was set in pre() or post(),
      // also copy the error code to the context. The _error_type()
      // function returns non-0 value if there an error pending.
      // The _copy_error() functions copies the error state to
      // the context.

      uint_s_.pre (env_->thread_id ());

#ifndef XSDE_EXCEPTIONS
      if (uint_s_._error_type ())
        uint_s_._copy_error (ctx);

      if (ctx.error_type ())
        return;
#endif
      uint_s_._pre_impl (ctx);

      if (ctx.error_type ())
        return;

      uint_s_._serialize_content ();

      if (ctx.error_type ())
        return;

      uint_s_._post_impl ();

      if (ctx.error_type ())
        return;

      uint_s_.post ();

#ifndef XSDE_EXCEPTIONS
      if (uint_s_._error_type ())
        uint_s_._copy_error (ctx);

      if (_error_type ())
        return;
#endif
#endif

      tid_set_ = true;
    }

    // Elements.
    //
    virtual std::string
    to ()
    {
      return env_->to ();
    }

    virtual std::string
    from ()
    {
      return env_->from ();
    }

    virtual std::string
    subject ()
    {
      return env_->subject ();
    }

    virtual bool
    any_next ()
    {
      // See if there is a body that we know how to serialize.
      //
      for (; i_ != env_->end_body (); ++i_)
      {
        body_type t = (*i_)->type ();

        if (t == email::text_body || t == email::binary_body)
          break;
      }

      return i_ != env_->end_body ();
    }

    virtual void
    any (std::string& ns, std::string& name)
    {
      ns = "http://www.codesynthesis.com/email";

      switch ((*i_)->type ())
      {
      case email::text_body:
        {
          name = "text";
          break;
        }
      case email::binary_body:
        {
          name = "binary";
          break;
        }
      }
    }

    virtual void
    serialize_any ()
    {
      const body* b = *i_++;
      xml_schema::serializer_context& ctx = _context ();

      switch (b->type ())
      {
      case email::text_body:
        {
          // For more information on what's going here, see the
          // serialize_any_attribute() function above.
          //
#if defined(XSDE_EXCEPTIONS) && !defined(XSDE_SERIALIZER_VALIDATION)

          text_s_.pre (static_cast<const text*> (b)->content ());
          text_s_._pre_impl (ctx);
          text_s_._serialize_content ();
          text_s_._post_impl ();
          text_s_.post ();
#else

          text_s_.pre (static_cast<const text*> (b)->content ());

#ifndef XSDE_EXCEPTIONS
          if (text_s_._error_type ())
            text_s_._copy_error (ctx);

          if (ctx.error_type ())
            return;
#endif
          text_s_._pre_impl (ctx);

          if (ctx.error_type ())
            return;

          text_s_._serialize_content ();

          if (ctx.error_type ())
            return;

          text_s_._post_impl ();

          if (ctx.error_type ())
            return;

          text_s_.post ();

#ifndef XSDE_EXCEPTIONS
          if (text_s_._error_type ())
            text_s_._copy_error (ctx);

          if (ctx.error_type ())
            return;
#endif
#endif
          break;
        }
      case email::binary_body:
        {
          // For more information on what's going here, see the
          // serialize_any_attribute() function above. Note also
          // that in this case we also call _serialize_attributes
          // since binary is a complex type.
          //

#if defined(XSDE_EXCEPTIONS) && !defined(XSDE_SERIALIZER_VALIDATION)
          bin_s_.pre (static_cast<const binary*> (b));
          bin_s_._pre_impl (ctx);
          bin_s_._serialize_attributes ();
          bin_s_._serialize_content ();
          bin_s_._post_impl ();
          bin_s_.post ();
#else
          bin_s_.pre (static_cast<const binary*> (b));

#ifndef XSDE_EXCEPTIONS
          if (bin_s_._error_type ())
            bin_s_._copy_error (ctx);

          if (ctx.error_type ())
            return;
#endif
          bin_s_._pre_impl (ctx);

          if (ctx.error_type ())
            return;

          bin_s_._serialize_attributes ();

          if (ctx.error_type ())
            return;

          bin_s_._serialize_content ();

          if (ctx.error_type ())
            return;

          bin_s_._post_impl ();

          if (ctx.error_type ())
            return;

          bin_s_.post ();

#ifndef XSDE_EXCEPTIONS
          if (bin_s_._error_type ())
            bin_s_._copy_error (ctx);

          if (ctx.error_type ())
            return;
#endif
#endif
          break;
        }
      }
    }

    // If we need to be able to reset and reuse the serializer
    // after an error then we also need to override _reset() and
    // reset the serializers that are used to handle wildcards.
    // Note that you always need to call _reset() from the base.
    //
    virtual void
    _reset ()
    {
      envelope_sskel::_reset ();

      text_s_._reset ();
      bin_s_._reset ();
      uint_s_._reset ();
    }

  private:
    // Serializers used in wildcard content serialization.
    //
    xml_schema::string_simpl& text_s_;
    binary_sskel& bin_s_;
    xml_schema::unsigned_int_simpl& uint_s_;

    const envelope* env_;
    bool tid_set_;
    envelope::body_iterator i_;
  };
}

int
main ()
{
  try
  {
    using namespace email;

    // Create a sample email with a text body and two (fake) pictures.
    //
    envelope env ("Jane Doe <jane@doe.com>",
                  "John Doe <john@doe.com>",
                  "Surfing pictures",
                  123); // thread id

    env.add_body (new text ("Hi Jane,\n"
                            "Here are cool pictures of me surfing.\n\n"
                            "Cheers,\n"
                            "John"));

    env.add_body (new binary ("pic1.jpg", "image/jpeg", "abc123", 6));
    env.add_body (new binary ("pic2.jpg", "image/jpeg", "123abc", 6));


    // Construct the serializer.
    //
    xml_schema::string_simpl string_s;
    xml_schema::unsigned_int_simpl uint_s;

    binary_simpl binary_s;
    envelope_simpl envelope_s (string_s, binary_s, uint_s);

    binary_s.serializers (string_s, string_s);
    envelope_s.serializers (string_s, string_s, string_s);

    // Serialize the sample email to XML document.
    //
    xml_schema::document_simpl doc_s (
      envelope_s,
      "http://www.codesynthesis.com/email",
      "message");

    doc_s.add_prefix ("eml", "http://www.codesynthesis.com/email");
    doc_s.add_schema ("http://www.codesynthesis.com/email", "email.xsd");

    envelope_s.pre (env);
    doc_s.serialize (cout, xml_schema::document_simpl::pretty_print);
    envelope_s.post ();
  }
  catch (const xml_schema::serializer_exception& e)
  {
    cerr << "error: " << e.text () << endl;
    return 1;
  }
  catch (const std::ios_base::failure&)
  {
    cerr << "error: write failure" << endl;
    return 1;
  }

  return 0;
}
