// file      : tests/cxx/serializer/built-in/driver.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2006-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

// Test built-in type serialization.
//

#include <stdlib.h> // strtof, strtod
#include <string.h> // memcpy, strlen, strcmp
#include <fstream>
#include <iostream>

#include "test-sskel.hxx"

using namespace std;
using namespace test;

struct any_type_simpl: xml_schema::any_type_simpl
{
  virtual void
  _serialize_attributes ()
  {
    _attribute ("foo", "one");
    _attribute ("test", "foo", "two");
  }

  virtual void
  _serialize_content ()
  {
    _start_element ("test", "inner");
    _characters ("hello");
    _end_element ();
  }
};
/*
struct any_simple_type_simpl: xml_schema::any_simple_type_simpl
{
  virtual void
  _serialize_content ()
  {
    _characters ("hello");
  }
};
*/

struct root_simpl: root_sskel
{
  virtual void
  pre ()
  {
    boolean_ = 0;
    byte_ = 0;
    unsigned_byte_ = 0;
    short__ = 0;
    unsigned_short_ = 0;
    int__ = 0;
    unsigned_int_ = 0;
    long__ = 0;
    unsigned_long_ = 0;

    integer_ = 0;
    negative_integer_ = 0;
    non_positive_integer_ = 0;
    positive_integer_ = 0;
    non_negative_integer_ = 0;

    float__ = 0;
    double__ = 0;
    decimal_ = 0;

    string_ = 0;
    normalized_string_ = 0;
    token_ = 0;
    name_ = 0;
    nmtoken_ = 0;
    nmtokens_ = 0;
    ncname_ = 0;
    id_ = 0;
    idref_ = 0;
    idrefs_ = 0;
    language_ = 0;
    uri_ = 0;
    qname_ = 0;

    base64_binary_ = 0;
    hex_binary_ = 0;

    gday_ = 0;
    gmonth_ = 0;
    gyear_ = 0;
    gmonth_day_ = 0;
    gyear_month_ = 0;
    date_ = 0;
    time_ = 0;
    date_time_ = 0;
    duration_ = 0;
  }

  virtual bool
  boolean_next ()
  {
    return boolean_ < 2;
  }

  virtual bool
  boolean ()
  {
    static const bool v[] = {true, false};
    return v[boolean_++];
  }

  virtual bool
  byte_next ()
  {
    return byte_ < 4;
  }

  virtual signed char
  byte ()
  {
    static const signed char v[] = {-128, -123, 0, 127};
    return v[byte_++];
  }

  virtual bool
  unsigned_byte_next ()
  {
    return unsigned_byte_ < 3;
  }

  virtual unsigned char
  unsigned_byte ()
  {
    static const unsigned char v[] = {0, 123, 255};
    return v[unsigned_byte_++];
  }

  virtual bool
  short__next ()
  {
    return short__ < 4;
  }

  virtual short
  short_ ()
  {
    static const short v[] = {-32768, -12345, 0, 32767};
    return v[short__++];
  }

  virtual bool
  unsigned_short_next ()
  {
    return unsigned_short_ < 3;
  }

  virtual unsigned short
  unsigned_short ()
  {
    static const unsigned short v[] = {0, 12345, 65535};
    return v[unsigned_short_++];
  }

  virtual bool
  int__next ()
  {
    return int__ < 4;
  }

  virtual int
  int_ ()
  {
    static const int v[] = {-2147483648, -1234567890, 0, 2147483647};
    return v[int__++];
  }

  virtual bool
  unsigned_int_next ()
  {
    return unsigned_int_ < 3;
  }

  virtual unsigned int
  unsigned_int ()
  {
    static const unsigned int v[] = {0, 1234567890, 4294967295};
    return v[unsigned_int_++];
  }

  virtual bool
  long__next ()
  {
    return long__ < 4;
  }

  virtual bool
  unsigned_long_next ()
  {
    return unsigned_long_ < 3;
  }

#ifdef XSDE_LONGLONG
  virtual long long
  long_ ()
  {
    static const long long v[] =
    {
      -9223372036854775807LL, -1234567890123456789LL,
      0LL, 9223372036854775807LL
    };

    return long__ == 0 ? (v[long__++] - 1) : v[long__++];
  }

  virtual unsigned long long
  unsigned_long ()
  {
    static const unsigned long long v[] =
    {
      0ULL, 12345678901234567890ULL, 18446744073709551615ULL
    };

    return v[unsigned_long_++];
  }
#else
  virtual long
  long_ ()
  {
    static const long v[] = {-2147483647L, -1234567890L, 0L, 2147483647L};
    return long__ == 0 ? (v[long__++] - 1) : v[long__++];
  }

  virtual unsigned long
  unsigned_long ()
  {
    static const unsigned long v[] = {0UL, 1234567890UL, 4294967295UL};
    return v[unsigned_long_++];
  }
#endif

  //
  //
  virtual bool
  integer_next ()
  {
    return integer_ < 4;
  }

  virtual long
  integer ()
  {
    static const long v[] = {-2147483647L, -1234567890L, 0L, 2147483647L};
    return integer_ == 0 ? (v[integer_++] - 1) : v[integer_++];
  }

  virtual bool
  negative_integer_next ()
  {
    return negative_integer_ < 2;
  }

  virtual long
  negative_integer ()
  {
    static const long v[] = {-2147483647L, -1234567890L};
    return negative_integer_ == 0
      ? (v[negative_integer_++] - 1)
      : v[negative_integer_++];
  }

  virtual bool
  non_positive_integer_next ()
  {
    return non_positive_integer_ < 3;
  }

  virtual long
  non_positive_integer ()
  {
    static const long v[] = {-2147483647L, -1234567890L, 0L};
    return non_positive_integer_ == 0
      ? (v[non_positive_integer_++] - 1)
      : v[non_positive_integer_++];
  }

  virtual bool
  positive_integer_next ()
  {
    return positive_integer_ < 2;
  }

  virtual unsigned long
  positive_integer ()
  {
    static const unsigned long v[] = {1234567890UL, 4294967295UL};
    return v[positive_integer_++];
  }

  virtual bool
  non_negative_integer_next ()
  {
    return non_negative_integer_ < 3;
  }

  virtual unsigned long
  non_negative_integer ()
  {
    static const unsigned long v[] = {0UL, 1234567890UL, 4294967295UL};
    return v[non_negative_integer_++];
  }

  //
  //
  virtual bool
  float__next ()
  {
    return float__ < 9;
  }

  virtual float
  float_ ()
  {
    static const float v[] = {0.0, 0.0, 0.0, 0.0, 1.0, -1.0,
                              123.567, -123.567e5, -0.45e-5};

    switch (float__)
    {
    case 0:
      {
        float__++;
        return strtof ("INF", 0);
      }
    case 1:
      {
        float__++;
        return strtof ("-INF", 0);
      }
    case 2:
      {
        float__++;
        return strtof ("NAN", 0);
      }
    default:
      {
        return v[float__++];
      }
    }
  }

  virtual bool
  double__next ()
  {
    return double__ < 9;
  }

  virtual double
  double_ ()
  {
    static const double v[] = {0.0, 0.0, 0.0, 0.0, 1.0, -1.0,
                               123.56789, -123.56789e8, -0.45E-5};

    switch (double__)
    {
    case 0:
      {
        double__++;
        return strtod ("INF", 0);
      }
    case 1:
      {
        double__++;
        return strtod ("-INF", 0);
      }
    case 2:
      {
        double__++;
        return strtod ("NAN", 0);
      }
    default:
      {
        return v[double__++];
      }
    }
  }

  virtual bool
  decimal_next ()
  {
    return decimal_ < 5;
  }

  virtual double
  decimal ()
  {
    static const double v[] = {0.0, 1.0, -1.0, 123.56789, -123.56789};
    return v[decimal_++];
  }

  //
  //

#ifdef XSDE_STL

  virtual std::string
  any_simple_type ()
  {
    return "hello";
  }

  virtual bool
  string_next ()
  {
    return string_++ < 1;
  }

  virtual std::string
  string ()
  {
    return " test \n string ";
  }

  virtual bool
  normalized_string_next ()
  {
    return normalized_string_++ < 1;
  }

  virtual std::string
  normalized_string ()
  {
    return "test  normalized  string";
  }

  virtual bool
  token_next ()
  {
    return token_++ < 1;
  }

  virtual std::string
  token ()
  {
    return "test token";
  }

  virtual bool
  name_next ()
  {
    return name_++ < 1;
  }

  virtual std::string
  name ()
  {
    return "as123:345-.abs";
  }

  virtual bool
  nmtoken_next ()
  {
    return nmtoken_++ < 1;
  }

  virtual std::string
  nmtoken ()
  {
    return "1as123:345-.abs";
  }

  virtual bool
  nmtokens_next ()
  {
    return nmtokens_ < 2;
  }

  virtual xml_schema::string_sequence*
  nmtokens ()
  {
    using xml_schema::string_sequence;

    switch (nmtokens_++)
    {
    case 0:
      {
        string_sequence* r = new string_sequence;
        r->push_back ("one");
        return r;
      }
    case 1:
      {
        string_sequence* r = new string_sequence;
        r->push_back ("one");
        r->push_back ("two");
        r->push_back ("three");
        return r;
      }
    default:
      return 0;
    }
  }

  virtual bool
  ncname_next ()
  {
    return ncname_++ < 1;
  }

  virtual std::string
  ncname ()
  {
    return "as123_345-.abs";
  }

  virtual bool
  id_next ()
  {
    return id_ < 4;
  }

  virtual std::string
  id ()
  {
    static const char* v[] = {"as123_345-.abs", "one", "two", "three"};
    return v[id_++];
  }

  virtual bool
  idref_next ()
  {
    return idref_++ < 1;
  }

  virtual std::string
  idref ()
  {
    return "as123_345-.abs";
  }

  virtual bool
  idrefs_next ()
  {
    return idrefs_ < 2;
  }

  virtual xml_schema::string_sequence*
  idrefs ()
  {
    using xml_schema::string_sequence;

    switch (idrefs_++)
    {
    case 0:
      {
        string_sequence* r = new string_sequence;
        r->push_back ("one");
        return r;
      }
    case 1:
      {
        string_sequence* r = new string_sequence;
        r->push_back ("two");
        r->push_back ("three");
        return r;
      }
    default:
      return 0;
    }
  }

  virtual bool
  language_next ()
  {
    return language_++ < 1;
  }

  virtual std::string
  language ()
  {
    return "en-us";
  }

  virtual bool
  uri_next ()
  {
    return uri_++ < 1;
  }

  virtual std::string
  uri ()
  {
    return "http://www.example.com/foo#bar";
  }

  virtual bool
  qname_next ()
  {
    return qname_ < 2;
  }

  virtual xml_schema::qname
  qname ()
  {
    using xml_schema::qname;

    switch (qname_++)
    {
    case 0:
      {
        qname r ("g1", "qname");
        return r;
      }
    case 1:
      {
        qname r ("qname");
        return r;
      }
    default:
      return qname ("bad");
    }
  }

#else

  virtual const char*
  any_simple_type ()
  {
    return "hello";
  }

  virtual bool
  string_next ()
  {
    return string_++ < 1;
  }

  virtual const char*
  string ()
  {
    return " test \n string ";
  }

  virtual bool
  normalized_string_next ()
  {
    return normalized_string_++ < 1;
  }

  virtual const char*
  normalized_string ()
  {
    return "test  normalized  string";
  }

  virtual bool
  token_next ()
  {
    return token_++ < 1;
  }

  virtual const char*
  token ()
  {
    return "test token";
  }

  virtual bool
  name_next ()
  {
    return name_++ < 1;
  }

  virtual const char*
  name ()
  {
    return "as123:345-.abs";
  }

  virtual bool
  nmtoken_next ()
  {
    return nmtoken_++ < 1;
  }

  virtual const char*
  nmtoken ()
  {
    return "1as123:345-.abs";
  }

  virtual bool
  nmtokens_next ()
  {
    return nmtokens_ < 2;
  }

  virtual const xml_schema::string_sequence*
  nmtokens ()
  {
    using xml_schema::string_sequence;

    switch (nmtokens_++)
    {
    case 0:
      {
        string_sequence* r = new string_sequence ();
        r->push_back_copy ("one");
        return r;
      }
    case 1:
      {
        string_sequence* r = new string_sequence ();
        r->push_back_copy ("one");
        r->push_back_copy ("two");
        r->push_back_copy ("three");
        return r;
      }
    default:
      return 0;
    }
  }

  virtual bool
  ncname_next ()
  {
    return ncname_++ < 1;
  }

  virtual const char*
  ncname ()
  {
    return "as123_345-.abs";
  }

  virtual bool
  id_next ()
  {
    return id_ < 4;
  }

  virtual const char*
  id ()
  {
    static const char* v[] = {"as123_345-.abs", "one", "two", "three"};
    return v[id_++];
  }

  virtual bool
  idref_next ()
  {
    return idref_++ < 1;
  }

  virtual const char*
  idref ()
  {
    return "as123_345-.abs";
  }

  virtual bool
  idrefs_next ()
  {
    return idrefs_ < 2;
  }

  virtual const xml_schema::string_sequence*
  idrefs ()
  {
    using xml_schema::string_sequence;

    switch (idrefs_++)
    {
    case 0:
      {
        string_sequence* r = new string_sequence ();
        r->push_back_copy ("one");
        return r;
      }
    case 1:
      {
        string_sequence* r = new string_sequence ();
        r->push_back_copy ("two");
        r->push_back_copy ("three");
        return r;
      }
    default:
      return 0;
    }
  }

  virtual bool
  language_next ()
  {
    return language_++ < 1;
  }

  virtual const char*
  language ()
  {
    return "en-us";
  }

  virtual bool
  uri_next ()
  {
    return uri_++ < 1;
  }

  virtual const char*
  uri ()
  {
    return "http://www.example.com/foo#bar";
  }

  virtual bool
  qname_next ()
  {
    return qname_ < 2;
  }

  virtual const xml_schema::qname*
  qname ()
  {
    using xml_schema::qname;

    switch (qname_++)
    {
    case 0:
      {
        qname* r = new qname ();
        r->prefix_copy ("g1");
        r->name_copy ("qname");
        return r;
      }
    case 1:
      {
        qname* r = new qname ();
        r->name_copy ("qname");
        return r;
      }
    default:
      return 0;
    }
  }
#endif

  //
  //
  virtual bool
  base64_binary_next ()
  {
    return base64_binary_ < 6;
  }

  virtual const xml_schema::buffer*
  base64_binary ()
  {
    xml_schema::buffer* r = new xml_schema::buffer ();

    switch (base64_binary_++)
    {
    case 0:
      {
        // Empty buffer.
        //
        break;
      }
    case 1:
      {
        const char data[] = "12345abcjk";
        const size_t size = sizeof (data) - 1;
        r->size (size);
        memcpy (r->data (), data, size);
        break;
      }
    case 2:
      {
        const char data[] = "a";
        const size_t size = sizeof (data) - 1;
        r->size (size);
        memcpy (r->data (), data, size);
        break;
      }
    case 3:
      {
        const char data[] = "ab";
        const size_t size = sizeof (data) -1;
        r->size (size);
        memcpy (r->data (), data, size);
        break;
      }
    case 4:
      {
        const char data[] = "abc";
        const size_t size = sizeof (data) - 1;
        r->size (size);
        memcpy (r->data (), data, size);
        break;
      }
    case 5:
      {
        const size_t size = 345;

        r->size (size);
        unsigned char v = 0;

        for (size_t i = 0; i < size; ++i)
        {
          r->data ()[i] = static_cast<char> (v++);
        }

        break;
      }
    }

    return r;
  }

  virtual bool
  hex_binary_next ()
  {
    return hex_binary_ < 3;
  }

  virtual const xml_schema::buffer*
  hex_binary ()
  {
    xml_schema::buffer* r = new xml_schema::buffer ();

    switch (hex_binary_++)
    {
    case 0:
      {
        // Empty buffer.
        //
        break;
      }
    case 1:
      {
        const char data[] = "12345abcjk";
        const size_t size = sizeof (data) - 1;
        r->size (size);
        memcpy (r->data (), data, size);
        break;
      }
    case 2:
      {
        const size_t size = 345;

        r->size (size);
        unsigned char v = 0;

        for (size_t i = 0; i < size; ++i)
        {
          r->data ()[i] = static_cast<char> (v++);
        }

        break;
      }
    }

    return r;
  }

  virtual bool
  gday_next ()
  {
    return gday_ < 3;
  }

  virtual xml_schema::gday
  gday ()
  {
    using xml_schema::gday;

    switch (gday_++)
    {
    case 0:
      return gday (23);
    case 1:
      return gday (31, 2, 30);
    case 2:
      return gday (15, 0, 0);
    }

    return gday (0);
  }

  virtual bool
  gmonth_next ()
  {
    return gmonth_ < 2;
  }

  virtual ::xml_schema::gmonth
  gmonth ()
  {
    using xml_schema::gmonth;

    switch (gmonth_++)
    {
    case 0:
      return gmonth (6);
    case 1:
      return gmonth (12, 2, 30);
    }

    return gmonth (0);
  }

  virtual bool
  gyear_next ()
  {
    return gyear_ < 2;
  }

  virtual ::xml_schema::gyear
  gyear ()
  {
    using xml_schema::gyear;

    switch (gyear_++)
    {
    case 0:
      return gyear (2007);
    case 1:
      return gyear (-2007, -2, -30);
    }

    return gyear (0);
  }

  virtual bool
  gmonth_day_next ()
  {
    return gmonth_day_ < 2;
  }

  virtual ::xml_schema::gmonth_day
  gmonth_day ()
  {
    using xml_schema::gmonth_day;

    switch (gmonth_day_++)
    {
    case 0:
      return gmonth_day (6, 15);
    case 1:
      return gmonth_day (12, 31, 2, 30);
    }

    return gmonth_day (0, 0);
  }

  virtual bool
  gyear_month_next ()
  {
    return gyear_month_ < 2;
  }

  virtual ::xml_schema::gyear_month
  gyear_month ()
  {
    using xml_schema::gyear_month;

    switch (gyear_month_++)
    {
    case 0:
      return gyear_month (2007, 10);
    case 1:
      return gyear_month (-2007, 12, -2, -30);
    }

    return gyear_month (0, 0);
  }

  virtual bool
  date_next ()
  {
    return date_ < 2;
  }

  virtual ::xml_schema::date
  date ()
  {
    using xml_schema::date;

    switch (date_++)
    {
    case 0:
      return date (2007, 6, 15);
    case 1:
      return date (-2007, 12, 31, -2, -30);
    }

    return date (0, 0, 0);
  }

  virtual bool
  time_next ()
  {
    return time_ < 2;
  }

  virtual ::xml_schema::time
  time ()
  {
    using xml_schema::time;

    switch (time_++)
    {
    case 0:
      return time (12, 30, 30.0);
    case 1:
      return time (23, 59, 59.55, 2, 30);
    }

    return time (0, 0, 0);
  }

  virtual bool
  date_time_next ()
  {
    return date_time_ < 2;
  }

  virtual ::xml_schema::date_time
  date_time ()
  {
    using xml_schema::date_time;

    switch (date_time_++)
    {
    case 0:
      return date_time (2007, 6, 15, 12, 30, 30.0);
    case 1:
      return date_time (-2007, 12, 31, 23, 59, 59.55, -2, -30);
    }

    return date_time (0, 0, 0, 0, 0, 0);
  }

  virtual bool
  duration_next ()
  {
    return duration_ < 7;
  }

  virtual ::xml_schema::duration
  duration ()
  {
    using xml_schema::duration;

    switch (duration_++)
    {
    case 0:
      return duration (false, 1, 0, 0, 0, 0, 0.0);
    case 1:
      return duration (true, 0, 1, 0, 0, 0, 0.0);
    case 2:
      return duration (false, 0, 0, 1, 0, 0, 0.0);
    case 3:
      return duration (true, 0, 0, 0, 1, 0, 0.0);
    case 4:
      return duration (false, 0, 0, 0, 0, 1, 0.0);
    case 5:
      return duration (true, 0, 0, 0, 0, 0, 1.1);
    case 6:
      return duration (false, 1, 2, 3, 4, 5, 6.7);
    }

    return duration (false, 0, 0, 0, 0, 0, 0);
  }

private:
  int boolean_;
  int byte_;
  int unsigned_byte_;
  int short__;
  int unsigned_short_;
  int int__;
  int unsigned_int_;
  int long__;
  int unsigned_long_;

  int integer_;
  int negative_integer_;
  int non_positive_integer_;
  int positive_integer_;
  int non_negative_integer_;

  int float__;
  int double__;
  int decimal_;

  int string_;
  int normalized_string_;
  int token_;
  int name_;
  int nmtoken_;
  int nmtokens_;
  int ncname_;
  int id_;
  int idref_;
  int idrefs_;
  int language_;
  int uri_;
  int qname_;

  int base64_binary_;
  int hex_binary_;

  int gday_;
  int gmonth_;
  int gyear_;
  int gmonth_day_;
  int gyear_month_;
  int date_;
  int time_;
  int date_time_;
  int duration_;
};

int
main (int argc, char* argv[])
{
  if (argc != 2)
  {
    cerr << "usage: " << argv[0] << " <test-id>" << endl;
    return 1;
  }

  // Ignore one of the tests depending on whether long long is available.
  //
  {
    char* s = argv[1];
    size_t n = strlen (s);

    if (strcmp (s + n - 12,
#ifdef XSDE_LONGLONG
                "test-000.xml"
#else
                "test-001.xml"
#endif
        ) == 0)
    {
      s[n - 3] = 's';
      s[n - 2] = 't';
      s[n - 1] = 'd';

      ifstream ifs (s);
      cout << ifs.rdbuf ();
      return 0;
    }
  }

  any_type_simpl any_type_s;
  xml_schema::any_simple_type_simpl any_simple_type_s;

  xml_schema::boolean_simpl boolean_s;

  xml_schema::byte_simpl byte_s;
  xml_schema::unsigned_byte_simpl unsigned_byte_s;
  xml_schema::short_simpl short_s;
  xml_schema::unsigned_short_simpl unsigned_short_s;
  xml_schema::int_simpl int_s;
  xml_schema::unsigned_int_simpl unsigned_int_s;
  xml_schema::long_simpl long_s;
  xml_schema::unsigned_long_simpl unsigned_long_s;

  xml_schema::integer_simpl integer_s;
  xml_schema::negative_integer_simpl negative_integer_s;
  xml_schema::non_positive_integer_simpl non_sositive_integer_s;
  xml_schema::positive_integer_simpl positive_integer_s;
  xml_schema::non_negative_integer_simpl non_negative_integer_s;

  xml_schema::float_simpl float_s;
  xml_schema::double_simpl double_s;
  xml_schema::decimal_simpl decimal_s;

  xml_schema::string_simpl string_s;
  xml_schema::normalized_string_simpl normalized_string_s;
  xml_schema::token_simpl token_s;
  xml_schema::name_simpl name_s;
  xml_schema::nmtoken_simpl nmtoken_s;
  xml_schema::ncname_simpl ncname_s;
  xml_schema::id_simpl id_s;
  xml_schema::idref_simpl idref_s;

  xml_schema::language_simpl language_s;
  xml_schema::uri_simpl uri_s;

#ifdef XSDE_STL
  xml_schema::qname_simpl qname_s;
#else
  xml_schema::qname_simpl qname_s (true);
#endif

  xml_schema::idrefs_simpl idrefs_s (true);
  xml_schema::nmtokens_simpl nmtokens_s (true);

  xml_schema::base64_binary_simpl base64_binary_s (true);
  xml_schema::hex_binary_simpl hex_binary_s (true);

  xml_schema::gday_simpl gday_s;
  xml_schema::gmonth_simpl gmonth_s;
  xml_schema::gyear_simpl gyear_s;
  xml_schema::gmonth_day_simpl gmonth_day_s;
  xml_schema::gyear_month_simpl gyear_month_s;
  xml_schema::date_simpl date_s;
  xml_schema::time_simpl time_s;
  xml_schema::date_time_simpl date_time_s;
  xml_schema::duration_simpl duration_s;

  root_simpl root_s;

  root_s.serializers (any_type_s,
                      any_simple_type_s,
                      boolean_s,
                      byte_s,
                      unsigned_byte_s,
                      short_s,
                      unsigned_short_s,
                      int_s,
                      unsigned_int_s,
                      long_s,
                      unsigned_long_s,
                      integer_s,
                      negative_integer_s,
                      non_sositive_integer_s,
                      positive_integer_s,
                      non_negative_integer_s,
                      float_s,
                      double_s,
                      decimal_s,
                      string_s,
                      normalized_string_s,
                      token_s,
                      name_s,
                      nmtoken_s,
                      nmtokens_s,
                      ncname_s,
                      id_s,
                      idref_s,
                      idrefs_s,
                      language_s,
                      uri_s,
                      qname_s,
                      base64_binary_s,
                      hex_binary_s,
                      gday_s,
                      gmonth_s,
                      gyear_s,
                      gmonth_day_s,
                      gyear_month_s,
                      date_s,
                      time_s,
                      date_time_s,
                      duration_s);

  xml_schema::document_simpl doc_s (root_s, "test", "root");

  root_s.pre ();
  doc_s.serialize (cout);
  root_s.post ();

  return 0;
}
