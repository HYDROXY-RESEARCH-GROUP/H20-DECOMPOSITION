This directory contains a number of examples that show how to use the
Embedded C++/Serializer mapping. The following list gives an overview
of each example. See the README files in example directories for more
information on each example.

hello
  A simple "Hello, world!" example that shows how to serialize
  XML documents.

library
  Shows how to handle more complex data structures and serialize
  a custom in-memory object model.

minimal
  This example is a minimal serializer implementation that is
  intended to work without STL, iostream, or C++ exceptions.

wildcard
  Shows how to serialize XML data matched by XML Schema wildcards
  (any and anyAttribute).

polymorphism
  Shows how to handle XML vocabularies that use XML Schema polymorphism
  features such as the xsi:type attribute and substitution groups.

polyroot
  Shows how to handle XML vocabularies with polymorphic document root 
  elements.
