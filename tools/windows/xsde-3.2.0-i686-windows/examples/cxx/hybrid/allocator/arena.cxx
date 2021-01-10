// file      : examples/cxx/hybrid/allocator/arena.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : not copyrighted - public domain

#include <stdio.h>
#include <string.h> // memcpy

#include "arena.hxx"

arena::
arena (void* memory, size_t size)
    : alloc_count_ (0),
      realloc_count_ (0),
      free_count_ (0),
      cur_allocated_ (0),
      max_allocated_ (0)
{
  head_ = static_cast<block*> (memory);
  head_->cap  = size - sizeof (block);
  head_->next = 0;
  head_->used = false;
}

void* arena::
allocate (size_t size)
{
  block* b = head_;

  while (b != 0)
  {
    if (!b->used)
    {
      if (b->cap >= size)
      {
        // See if it makes sense to fragment this block.
        //
        if (b->cap - size >= sizeof (block) * 2)
        {
          block* b1 = reinterpret_cast<block*> (
            reinterpret_cast<char*> (b) + sizeof (block) + size);

          b1->cap = b->cap - size - sizeof (block);
          b1->next = b->next;
          b1->used = false;

          b->next = b1;
          b->cap = size;
        }

        b->used = true;
        b->size = size;

        alloc_count_++;
        cur_allocated_ += size;

        if (cur_allocated_ > max_allocated_)
          max_allocated_ = cur_allocated_;

        return b + 1;
      }

      // This block is not big enough. See if we can merge it
      // with the next block.
      //
      if (b->next != 0 && !b->next->used)
      {
        block* b1 = b->next;
        b->cap += b1->cap + sizeof (block);
        b->next = b1->next;

        // Try the merged block again.
        //
        continue;
      }
    }

    // This block is either in use or not big enough. Continue
    // searching.
    //
    b = b->next;
  }

  return 0;
}

void* arena::
reallocate (void* p, size_t size)
{
  // If the passed pointer is NULL, reallocate is equivalent to
  // allocate.
  //
  if (!p)
    return allocate (size);

  block* b = static_cast<block*> (p) - 1;

  // If the passed size is NULL, reallocate is equivalent to free.
  //
  if (size == 0)
  {
    free (p);
    return 0;
  }

  // If this block is not large enough to satisfy the request, try to
  // merge it with the next block(s).
  //
  while (b->cap < size && b->next != 0 && !b->next->used)
  {
    block* b1 = b->next;
    b->cap += b1->cap + sizeof (block);
    b->next = b1->next;
  }

  // If this block is now large enough then we can reuse the same
  // memory region.
  //
  if (b->cap >= size)
  {
    realloc_count_++;
    cur_allocated_ += size - b->size;

    if (cur_allocated_ > max_allocated_)
      max_allocated_ = cur_allocated_;

    b->size = size;
    return p;
  }

  // Otherwise allocate a new block and copy the data over.
  //
  void* r = allocate (size);

  if (r)
  {
    memcpy (r, p, b->size);
    free (p);
  }

  return r;
}

void arena::
free (void* p)
{
  if (p)
  {
    block* b = static_cast<block*> (p) - 1;

    cur_allocated_ -= b->size;
    free_count_++;

    b->used = false;
  }
}

void arena::
print_statistics ()
{
  printf ("\n");
  printf ("allocations:      %lu\n", alloc_count_);
  printf ("reallocations:    %lu\n", realloc_count_);
  printf ("deallocations:    %lu\n", free_count_);
  printf ("currently in use: %lu bytes\n", cur_allocated_);
  printf ("maximum in use:   %lu bytes\n", max_allocated_);
  printf ("\n");
}
