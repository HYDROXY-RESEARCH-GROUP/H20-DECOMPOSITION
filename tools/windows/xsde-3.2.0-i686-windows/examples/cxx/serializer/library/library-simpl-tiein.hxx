// file      : examples/cxx/serializer/library/library-simpl-tiein.hxx
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
  struct isbn_simpl: isbn_sskel
  {
    isbn_simpl ();

    virtual void
    pre (isbn);

  private:
    xml_schema::unsigned_int_simpl base_impl_;
  };

  //
  //
  struct title_simpl: title_sskel
  {
    title_simpl ();

    virtual void
    pre (const title&);

    virtual bool
    lang_present ();

    virtual std::string
    lang ();

  private:
    xml_schema::string_simpl base_impl_;
    const title* title_;
  };

  //
  //
  struct genre_simpl: genre_sskel
  {
    genre_simpl ();

    virtual void
    pre (genre);

  private:
    xml_schema::string_simpl base_impl_;
  };

  //
  //
  struct person_simpl: person_sskel
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
  struct author_simpl: author_sskel
  {
    author_simpl ();

    virtual void
    pre (const author&);

    virtual bool
    recommends_present ();

    virtual std::string
    recommends ();

  private:
    person_simpl base_impl_;
    const author* author_;
  };

  //
  //
  struct book_simpl: book_sskel
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
  struct catalog_simpl: catalog_sskel
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
