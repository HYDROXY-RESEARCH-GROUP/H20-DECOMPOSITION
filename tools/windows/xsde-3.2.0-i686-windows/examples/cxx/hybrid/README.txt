This directory contains a number of examples that show how to use the
Embedded C++/Hybrid mapping. The following list gives an overview of
each example. See the README files in example directories for more
information on each example.

hello
  A simple "Hello, world!" example that shows how to parse XML
  documents.

library
  Shows how to handle more complex data structures, modify the
  object model, and serialize the modified object model back to
  XML.
  
minimal
  Shows how to perform parsing and serialization as well as use the
  object model when the mapping is configured without support for
  STL, iostream, or C++ exceptions.

multiroot
  Shows how to parse XML vocabularies with multiple root elements.

wildcard
  Shows how to parse, store in the object model, and serialize XML
  data matched by XML Schema wildcards (any and anyAttribute).

filter
  Shows how to filter the XML data during parsing and object model
  during serialization.

streaming
  Shows how to perform partially event-driven, partially in-memory
  XML processing.

compositors
  Shows how to create, access, and modify object models with complex
  nested choice and sequence compositors.

polymorphism
  Shows how to handle XML vocabularies that use XML Schema polymorphism
  features such as the xsi:type attribute and substitution groups.

polyroot
  Shows how to handle XML vocabularies with polymorphic document root 
  elements.

allocator
  Shows how to use a custom memory allocator implementation.

custom/
  A collection of examples that show how to customize the C++/Hybrid
  object model by using custom C++ classes instead of or in addition
  to the generated ones. See the accompanying README file for an
  overview of each example in this directory.

evolution/
  A collection of examples that show how to handle schema evolution.

binary/
  A collection of examples that show how to serialize the object model
  into a number of predefined and custom binary formats.
