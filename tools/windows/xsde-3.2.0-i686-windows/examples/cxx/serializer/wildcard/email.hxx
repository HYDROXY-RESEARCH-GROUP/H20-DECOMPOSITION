// file      : examples/cxx/serializer/wildcard/email.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : not copyrighted - public domain

#ifndef EMAIL_HXX
#define EMAIL_HXX

#include <string>
#include <vector>
#include <cstddef> // std::size_t
#include <cstring> // std::memcpy

namespace email
{
  //
  //
  enum body_type
  {
    text_body,
    binary_body
  };

  struct body
  {
    virtual body_type
    type () const = 0;

    virtual
    ~body ()
    {
    }
  };

  //
  //
  struct text: body
  {
    text (const std::string& content)
        : content_ (content)
    {
    }

    virtual body_type
    type () const
    {
      return text_body;
    }

    const std::string&
    content () const
    {
      return content_;
    }

  private:
    std::string content_;
  };

  //
  //
  struct binary: body
  {
    binary (const std::string& name,
            const std::string& mime,
            const char* data,
            std::size_t size)
        : name_ (name), mime_ (mime), data_ (0), size_ (size)
    {
      if (size_ != 0)
      {
        data_ = new char[size_];
        std::memcpy (data_, data, size_);
      }
    }

    virtual
    ~binary ()
    {
      delete[] data_;
    }

    virtual body_type
    type () const
    {
      return binary_body;
    }

    const std::string&
    name () const
    {
      return name_;
    }

    const std::string&
    mime () const
    {
      return mime_;
    }

    const char*
    data () const
    {
      return data_;
    }

    std::size_t
    size () const
    {
      return size_;
    }

  private:
    std::string name_;
    std::string mime_;
    char* data_;
    std::size_t size_;
  };

  //
  //
  struct envelope
  {
    envelope (const std::string& to,
              const std::string& from,
              const std::string& subject,
              unsigned int thread_id)
        : to_ (to), from_ (from), subject_ (subject), thread_id_ (thread_id)
    {
    }

    const std::string&
    to () const
    {
      return to_;
    }

    const std::string&
    from () const
    {
      return from_;
    }

    const std::string&
    subject () const
    {
      return subject_;
    }

    unsigned int
    thread_id () const
    {
      return thread_id_;
    }

    // Assumes ownership of the passed object.
    //
    void
    add_body (body* b)
    {
      bodies_.push_back (b);
    }

    typedef std::vector<body*> bodies;
    typedef bodies::const_iterator body_iterator;

    body_iterator
    begin_body () const
    {
      return bodies_.begin ();
    }

    body_iterator
    end_body () const
    {
      return bodies_.end ();
    }

    ~envelope ()
    {
      for (body_iterator i = begin_body (); i != end_body (); ++i)
        delete *i;
    }

  private:
    const std::string to_;
    const std::string from_;
    const std::string subject_;
    unsigned int thread_id_;

    bodies bodies_;
  };
}

#endif // EMAIL_HXX
