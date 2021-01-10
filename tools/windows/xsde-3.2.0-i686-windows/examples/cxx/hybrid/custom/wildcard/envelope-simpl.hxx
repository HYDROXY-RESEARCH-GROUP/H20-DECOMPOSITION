// file      : examples/cxx/hybrid/custom/wildcard/envelope-simpl.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : not copyrighted - public domain

#ifndef ENVELOPE_SIMPL_HXX
#define ENVELOPE_SIMPL_HXX

namespace email
{
  // Customized envelope serializer implementation. Here we implement
  // the any_next, any, and serialize_any callbacks to serialize the
  // wildcard content.
  //
  class envelope_simpl: public envelope_base_simpl
  {
  public:
    envelope_simpl ()
        : text_s_ (0), binary_s_ (0)
    {
    }

    // Additional serializers for the wildcard content.
    //
    void
    text_serializer (xml_schema::string_sskel& s)
    {
      text_s_ = &s;
    }

    void
    binary_serializer (binary_sskel& s)
    {
      binary_s_ = &s;
    }

  public:
    virtual void
    _pre ();

    virtual bool
    any_next ();

    virtual void
    any (std::string& ns, std::string& name);

    virtual void
    serialize_any ();

    // If we need to be able to reset and reuse the serializer
    // after an error then we also need to override _reset() and
    // reset the serializers that are used to handle wildcards.
    //
    virtual void
    _reset ();

  private:
    envelope::body_const_iterator i_;

    // Serializers for the text and binary elements.
    //
  private:
    xml_schema::string_sskel* text_s_;
    binary_sskel* binary_s_;
  };
}

#endif // ENVELOPE_SIMPL_HXX
