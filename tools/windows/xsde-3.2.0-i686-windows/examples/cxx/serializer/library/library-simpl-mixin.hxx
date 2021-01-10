// file      : examples/cxx/serializer/library/library-simpl-mixin.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : not copyrighted - public domain

#ifndef LIBRARY_SIMPL_HXX
#define LIBRARY_SIMPL_HXX

#include "library.hxx"
#include "library-sskel.hxx"

namespace library
{
  //
  //
  struct isbn_simpl: virtual isbn_sskel, xml_schema::unsigned_int_simpl
  {
    virtual void
    pre (isbn);
  };

  //
  //
  struct title_simpl: virtual title_sskel, xml_schema::string_simpl
  {
    virtual void
    pre (const title&);

    virtual bool
    lang_present ();

    virtual std::string
    lang ();

  private:
    const title* title_;
  };

  //
  //
  struct genre_simpl: virtual genre_sskel, xml_schema::string_simpl
  {
    virtual void
    pre (genre);
  };

  //
  //
  struct person_simpl: virtual person_sskel
  {
    virtual void
    pre (const person&);

    virtual std::string
    name ();

    virtual std::string
    born ();

    virtual bool
    died_present ();

    virtual std::string
    died ();

  private:
    const person* person_;
  };

  //
  //
  struct author_simpl: virtual author_sskel, person_simpl
  {
    virtual void
    pre (const author&);

    virtual bool
    recommends_present ();

    virtual std::string
    recommends ();

  private:
    const author* author_;
  };

  //
  //
  struct book_simpl: virtual book_sskel
  {
    virtual void
    pre (const book&);

    virtual library::isbn
    isbn ();

    virtual const library::title&
    title ();

    virtual library::genre
    genre ();

    virtual bool
    author_next ();

    virtual const library::author&
    author ();

    virtual bool
    available ();

    virtual std::string
    id ();

  private:
    const book* book_;
    book::authors::const_iterator ai_;
  };

  //
  //
  struct catalog_simpl: virtual catalog_sskel
  {
    virtual void
    pre (const catalog&);

    virtual bool
    book_next ();

    virtual const library::book&
    book ();

  private:
    const catalog* catalog_;
    catalog::const_iterator ci_;
  };
}

#endif // LIBRARY_SIMPL_HXX
