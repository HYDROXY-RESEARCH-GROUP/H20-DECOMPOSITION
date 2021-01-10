// file      : examples/cxx/hybrid/binary/custom/orawstream.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : not copyrighted - public domain

#ifndef ORAWSTREAM_HXX
#define ORAWSTREAM_HXX

#include <stddef.h>  // size_t

#include <string>

#include "exceptions.hxx"
#include "xml-schema.hxx"

class orawstream
{
public:
  explicit
  orawstream (xml_schema::buffer&);

public:
  struct as_size
  {
    explicit as_size (size_t s) : s_ (s) {}
    size_t s_;
  };

public:
  void operator<< (bool);
  void operator<< (signed char);
  void operator<< (unsigned char);
  void operator<< (short);
  void operator<< (unsigned short);
  void operator<< (int);
  void operator<< (unsigned int);
  void operator<< (long);
  void operator<< (unsigned long);

#ifdef XSDE_LONGLONG
  void operator<< (long long);
  void operator<< (unsigned long long);
#endif

  void operator<< (as_size);
  void operator<< (float);
  void operator<< (double);

  void operator<< (const std::string&);
  void operator<< (const xml_schema::buffer&);

private:
  orawstream (const orawstream&);
  orawstream& operator= (const orawstream&);

public:
  char*
  align (size_t alignment, size_t size);

private:
  xml_schema::buffer& buf_;
};

void operator<< (orawstream&, const xml_schema::any_type&);
void operator<< (orawstream&, const xml_schema::qname&);
void operator<< (orawstream&, const xml_schema::time_zone&);
void operator<< (orawstream&, const xml_schema::date&);
void operator<< (orawstream&, const xml_schema::date_time&);
void operator<< (orawstream&, const xml_schema::duration&);
void operator<< (orawstream&, const xml_schema::gday&);
void operator<< (orawstream&, const xml_schema::gmonth&);
void operator<< (orawstream&, const xml_schema::gmonth_day&);
void operator<< (orawstream&, const xml_schema::gyear&);
void operator<< (orawstream&, const xml_schema::gyear_month&);
void operator<< (orawstream&, const xml_schema::time&);

void operator<< (orawstream&, const xml_schema::string_sequence&);

template <typename T>
void operator<< (orawstream&, const xml_schema::pod_sequence<T>&);

template <typename T>
void operator<< (orawstream&, const xml_schema::fix_sequence<T>&);

template <typename T>
void operator<< (orawstream&, const xml_schema::var_sequence<T>&);

#include "orawstream.ixx"
#include "orawstream.txx"

#endif  // ORAWSTREAM_HXX
