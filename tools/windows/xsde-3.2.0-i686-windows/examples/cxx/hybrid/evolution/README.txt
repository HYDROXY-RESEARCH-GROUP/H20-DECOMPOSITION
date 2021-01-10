This directory contains a number of examples that show how to handle schema
evolution using the C++/Hybrid mapping. The following list gives an overview
of each example:

ignore
  Shows how to handle schema evolution using substitution groups. This
  example ignores unknown elements.

passthrough
  Shows how to handle schema evolution using substitution groups. This
  example passes the unknown content through parsing and serialization
  so that the output XML contains all the unknown elements.

