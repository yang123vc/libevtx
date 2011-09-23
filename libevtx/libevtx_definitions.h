/*
 * The internal definitions
 *
 * Copyright (c) 2011, Joachim Metz <jbmetz@users.sourceforge.net>
 *
 * Refer to AUTHORS for acknowledgements.
 *
 * This software is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public License
 * along with this software.  If not, see <http://www.gnu.org/licenses/>.
 */

#if !defined( _LIBEVTX_INTERNAL_DEFINITIONS_H )
#define _LIBEVTX_INTERNAL_DEFINITIONS_H

#include <common.h>
#include <byte_stream.h>

#define LIBEVTX_ENDIAN_BIG				_BYTE_STREAM_ENDIAN_BIG
#define LIBEVTX_ENDIAN_LITTLE				_BYTE_STREAM_ENDIAN_LITTLE

/* Define HAVE_LOCAL_LIBEVTX for local use of libevtx
 */
#if !defined( HAVE_LOCAL_LIBEVTX )
#include <libevtx/definitions.h>

/* The definitions in <libevtx/definitions.h> are copied here
 * for local use of libevtx
 */
#else
#define LIBEVTX_VERSION					20110920

/* The version string
 */
#define LIBEVTX_VERSION_STRING				"20110920"

/* The access flags definitions
 * bit 1        set to 1 for read access
 * bit 2        set to 1 for write access
 * bit 3-8      not used
 */
enum LIBEVTX_ACCESS_FLAGS
{
	LIBEVTX_ACCESS_FLAG_READ			= 0x01,
/* Reserved: not supported yet */
	LIBEVTX_ACCESS_FLAG_WRITE			= 0x02
};

/* The file access macros
 */
#define LIBEVTX_OPEN_READ				( LIBEVTX_ACCESS_FLAG_READ )
/* Reserved: not supported yet */
#define LIBEVTX_OPEN_WRITE				( LIBEVTX_ACCESS_FLAG_WRITE )
/* Reserved: not supported yet */
#define LIBEVTX_OPEN_READ_WRITE				( LIBEVTX_ACCESS_FLAG_READ | LIBEVTX_ACCESS_FLAG_WRITE )

#endif /* !defined( HAVE_LOCAL_LIBEVTX ) */

/* The maximum number of cache entries defintions
 */
#define LIBEVTX_MAXIMUM_CACHE_ENTRIES_CHUNKS		64

#endif
