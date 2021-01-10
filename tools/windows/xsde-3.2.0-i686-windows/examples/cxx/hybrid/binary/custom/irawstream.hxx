// file      : examples/cxx/hybrid/binary/custom/irawstream.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : not copyrighted - public domain

#ifndef IRAWSTREAM_HXX
#define IRAWSTREAM_HXX

#include <stddef.h>  // size_t

#include <string>

#include "exceptions.hxx"
#include "xml-schema.hxx"

class irawstream
{
public:
  explicit
  irawstream (const xml_schema::buffer&, size_t start = 0);

public:
  struct as_size
  {
    explicit as_size (size_t& s) : s_ (s) {}
    size_t& s_;
  };

public:
  void operator>> (bool&);
  void operator>> (signed char&);
  void operator>> (unsigned char&);
  void operator>> (short&);
  void operator>> (unsigned short&);
  void operator>> (int&);
  void operator>> (unsigned int&);
  void operator>> (long&);
  void operator>> (unsigned long&);

#ifdef XSDE_LONGLONG
  void operator>> (long long&);
  void operator>> (unsigned long long&);
#endif

  void operator>> (as_size&);
  void operator>> (float&);
  void operator>> (double&);

  void operator>> (std::string&);
  void operator>> (xml_schema::buffer&);

private:
  irawstream (const irawstream&);
  irawstream& operator= (const irawstream&);

public:
  const char*
  align (size_t alignment, size_t size);

private:
  const xml_schema::buffer& buf_;
  size_t pos_;
};

void operator>> (irawstream&, xml_schema::any_type&);
void operator>> (irawstream&, xml_schema::qname&);
void operator>> (irawstream&, xml_schema::time_zone&);
void operator>> (irawstream&, xml_schema::date&);
void operator>> (irawstream&, xml_schema::date_time&);
void operator>> (irawstream&, xml_schema::duration&);
void operator>> (irawstream&, xml_schema::gday&);
void operator>> (irawstream&, xml_schema::gmonth&);
void operator>> (irawstream&, xml_schema::gmonth_day&);
void operator>> (irawstream&, xml_schema::gyear&);
void operator>> (irawstream&, xml_schema::gyear_month&);
void operator>> (irawstream&, xml_schema::time&);

void operator>> (irawstream&, xml_schema::string_sequence&);

template <typename T>
void operator>> (irawstream&, xml_schema::pod_sequence<T>&);

template <typename T>
void operator>> (irawstream&, xml_schema::fix_sequence<T>&);

template <typename T>
void operator>> (irawstream&, xml_schema::var_sequence<T>&);

#include "irawstream.ixx"
#include "irawstream.txx"

#endif  // IRAWSTREAM_HXX
