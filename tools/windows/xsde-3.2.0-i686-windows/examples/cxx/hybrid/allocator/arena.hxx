// file      : examples/cxx/hybrid/allocator/arena.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : not copyrighted - public domain

#ifndef ARENA_HXX
#define ARENA_HXX

#include <stddef.h> // size_t

// Sample pooled memory arena. The primary goal here is to provide a
// simple, if naive, implementation. As a result, it probably shouldn't
// be used in production.
//
class arena
{
public:
  arena (void* memory, size_t size);

  void*
  allocate (size_t);

  void*
  reallocate (void*, size_t);

  void
  free (void*);

  void
  print_statistics ();

private:
  struct block
  {
    size_t cap;  // block capacity
    size_t size; // allocated size
    block* next; // next block
    size_t used; // used flag
  };

  block* head_; // Linked list of blocks.

  // Statistics.
  //
  size_t alloc_count_;
  size_t realloc_count_;
  size_t free_count_;

  size_t cur_allocated_;
  size_t max_allocated_;
};

#endif // ARENA_HXX
