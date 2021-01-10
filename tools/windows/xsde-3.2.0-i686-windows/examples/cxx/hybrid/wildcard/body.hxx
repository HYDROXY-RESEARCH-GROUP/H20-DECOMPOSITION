// file      : examples/cxx/hybrid/wildcard/body.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : not copyrighted - public domain

#ifndef BODY_HXX
#define BODY_HXX

#include "email.hxx"

namespace email
{
  // Custom email body type which can hold text or binary.
  //
  class body
  {
  public:
    enum type
    {
      type_none,
      type_text,
      type_binary
    };

    body ()
        : body_type_ (type_none), binary_ (0)
    {
    }

    ~body ()
    {
      body_type (type_none);
    }

    type
    body_type () const
    {
      return body_type_;
    }

    const std::string&
    text () const
    {
      return text_;
    }

    void
    text (const std::string& t)
    {
      body_type (type_text);
      text_ = t;
    }

    const email::binary&
    binary () const
    {
      return *binary_;
    }

    void
    binary (email::binary* b)
    {
      body_type (type_binary);
      binary_ = b;
    }

  private:
    void
    body_type (type t);

    type body_type_;
    std::string text_;
    email::binary* binary_;
  };

  // Custom data destructor for body.
  //
  void
  destroy_body (void*, size_t);
}

#endif // BODY_HXX
