/* Thread-local storage descriptor handling in the ELF dynamic linker.
   x86_64 version.
   Copyright (C) 2005-2025 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <https://www.gnu.org/licenses/>.  */

#include <stdint.h>

#ifndef _X86_64_DL_TLSDESC_H
# define _X86_64_DL_TLSDESC_H 1

/* Type used to represent a TLS descriptor in the GOT.  */
struct tlsdesc
{
  /* Anonymous union is used here to ensure that GOT entry slot is always
     8 bytes for both x32 and x86-64.  */
  union
    {
      ptrdiff_t (*entry) (struct tlsdesc *on_rax);
      uint64_t entry_slot;
    };
  union
    {
      void *arg;
      uint64_t arg_slot;
    };
};

typedef struct dl_tls_index
{
  uint64_t ti_module;
  uint64_t ti_offset;
} tls_index;

/* Type used as the argument in a TLS descriptor for a symbol that
   needs dynamic TLS offsets.  */
struct tlsdesc_dynamic_arg
{
  tls_index tlsinfo;
  size_t gen_count;
};

extern ptrdiff_t attribute_hidden
  _dl_tlsdesc_return(struct tlsdesc *on_rax),
  _dl_tlsdesc_undefweak(struct tlsdesc *on_rax);

# ifdef SHARED
extern void *_dl_make_tlsdesc_dynamic (struct link_map *map,
				       size_t ti_offset)
  attribute_hidden;

extern ptrdiff_t attribute_hidden _dl_tlsdesc_dynamic(struct tlsdesc *);
# endif

#endif
