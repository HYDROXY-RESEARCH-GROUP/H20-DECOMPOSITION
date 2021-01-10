// file      : examples/cxx/serializer/library/library-simpl-tiein.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : not copyrighted - public domain

#include "library-simpl-tiein.hxx"

namespace library
{
  using namespace xml_schema;

  // isbn_simpl
  //
  isbn_simpl::
  isbn_simpl ()
      : isbn_sskel (&base_impl_)
  {
  }

  void isbn_simpl::
  pre (isbn n)
  {
    base_impl_.pre (n);
  }

  // title_simpl
  //
  title_simpl::
  title_simpl ()
      : title_sskel (&base_impl_)
  {
  }

  void title_simpl::
  pre (const title& t)
  {
    base_impl_.pre (t);
    title_ = &t;
  }

  bool title_simpl::
  lang_present ()
  {
    return !title_->lang ().empty ();
  }

  std::string title_simpl::
  lang ()
  {
    return title_->lang ();
  }

  // genre_simpl
  //
  genre_simpl::
  genre_simpl ()
      : genre_sskel (&base_impl_)
  {
  }

  const char* genre_strings[] =
  {
    "romance",
    "fiction",
    "horror",
    "history",
    "philosophy"
  };

  void genre_simpl::
  pre (genre g)
  {
    base_impl_.pre (genre_strings[g]);
  }

  // person_simpl
  //
  void person_simpl::
  pre (const person& p)
  {
    person_ = &p;
  }

  std::string person_simpl::
  name ()
  {
    return person_->name ();
  }

  std::string person_simpl::
  born ()
  {
    return person_->born ();
  }

  bool person_simpl::
  died_present ()
  {
    return !person_->died ().empty ();
  }

  std::string person_simpl::
  died ()
  {
    return person_->died ();
  }

  // author_simpl
  //
  author_simpl::
  author_simpl ()
      : author_sskel (&base_impl_)
  {
  }

  void author_simpl::
  pre (const author& a)
  {
    base_impl_.pre (a);
    author_ = &a;
  }

  bool author_simpl::
  recommends_present ()
  {
    return !author_->recommends ().empty ();
  }

  std::string author_simpl::
  recommends ()
  {
    return author_->recommends ();
  }

  // book_simpl
  //

  void book_simpl::
  pre (const book& b)
  {
    book_ = &b;
    ai_ = b.author ().begin ();
  }

  library::isbn book_simpl::
  isbn ()
  {
    return book_->isbn ();
  }

  const library::title& book_simpl::
  title ()
  {
    return book_->title ();
  }


  library::genre book_simpl::
  genre ()
  {
    return book_->genre ();
  }

  bool book_simpl::
  author_next ()
  {
    return ai_ != book_->author ().end ();
  }

  const library::author& book_simpl::
  author ()
  {
    return *ai_++;
  }

  bool book_simpl::
  available ()
  {
    return book_->available ();
  }

  std::string book_simpl::
  id ()
  {
    return book_->id ();
  }

  // catalog_simpl
  //
  void catalog_simpl::
  pre (const catalog& c)
  {
    catalog_ = &c;
    ci_ = c.begin ();
  }

  bool catalog_simpl::
  book_next ()
  {
    return ci_ != catalog_->end ();
  }

  const library::book& catalog_simpl::
  book ()
  {
    return *ci_++;
  }
}

