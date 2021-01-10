// file      : examples/cxx/hybrid/custom/wildcard/envelope.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : not copyrighted - public domain

#ifndef ENVELOPE_HXX
#define ENVELOPE_HXX

namespace email
{
  // Customized envelope type. It adds a sequence of body objects
  // to the generated version.
  //
  class body;

  class envelope: public envelope_base
  {
  public:
    typedef xml_schema::var_sequence<email::body> body_sequence;
    typedef body_sequence::iterator body_iterator;
    typedef body_sequence::const_iterator body_const_iterator;

    const body_sequence&
    body () const
    {
      return body_;
    }

    body_sequence&
    body ()
    {
      return body_;
    }

  private:
    body_sequence body_;
  };
}

#endif // ENVELOPE_HXX
