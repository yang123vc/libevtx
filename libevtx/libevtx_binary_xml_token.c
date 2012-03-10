/*
 * Binary XML token functions
 *
 * Copyright (c) 2011-2012, Joachim Metz <jbmetz@users.sourceforge.net>
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

#include <common.h>
#include <byte_stream.h>
#include <memory.h>
#include <types.h>

#include <liberror.h>
#include <libnotify.h>

#include "libevtx_binary_xml_token.h"
#include "libevtx_definitions.h"

/* Initialize binary XML token
 * Make sure the value binary XML token is pointing to is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libevtx_binary_xml_token_initialize(
     libevtx_binary_xml_token_t **binary_xml_token,
     liberror_error_t **error )
{
	static char *function = "libevtx_binary_xml_token_initialize";

	if( binary_xml_token == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid binary XML token.",
		 function );

		return( -1 );
	}
	if( *binary_xml_token != NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid binary XML token value already set.",
		 function );

		return( -1 );
	}
	*binary_xml_token = memory_allocate_structure(
	                 libevtx_binary_xml_token_t );

	if( *binary_xml_token == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_MEMORY,
		 LIBERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create binary XML token.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     ( *binary_xml_token ),
	     0,
	     sizeof( libevtx_binary_xml_token_t ) ) == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_MEMORY,
		 LIBERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear binary XML token.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( *binary_xml_token != NULL )
	{
		memory_free(
		 *binary_xml_token );

		*binary_xml_token = NULL;
	}
	return( -1 );
}

/* Frees binary XML token
 * Returns 1 if successful or -1 on error
 */
int libevtx_binary_xml_token_free(
     libevtx_binary_xml_token_t **binary_xml_token,
     liberror_error_t **error )
{
	static char *function = "libevtx_binary_xml_token_free";
	int result            = 1;

	if( binary_xml_token == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid binary XML token.",
		 function );

		return( -1 );
	}
	if( *binary_xml_token != NULL )
	{
		memory_free(
		 *binary_xml_token );

		*binary_xml_token = NULL;
	}
	return( result );
}

/* Reads the binary XML token
 * Returns 1 if successful or -1 on error
 */
int libevtx_binary_xml_token_read(
     libevtx_binary_xml_token_t *binary_xml_token,
     libevtx_io_handle_t *io_handle,
     const uint8_t *chunk_data,
     size_t chunk_data_size,
     size_t chunk_data_offset,
     liberror_error_t **error )
{
	const uint8_t *binary_xml_token_data = NULL;
	static char *function                = "libevtx_binary_xml_token_read";
	size_t binary_xml_token_data_size    = 0;

	if( binary_xml_token == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid binary XML token.",
		 function );

		return( -1 );
	}
	if( io_handle == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid IO handle.",
		 function );

		return( -1 );
	}
	if( chunk_data == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid chunk data.",
		 function );

		return( -1 );
	}
	if( chunk_data_size > (size_t) SSIZE_MAX )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid binary XML token data size value exceeds maximum.",
		 function );

		goto on_error;
	}
	if( chunk_data_offset >= chunk_data_size )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid chunk data offset value out of bounds.",
		 function );

		goto on_error;
	}
	binary_xml_token_data      = &( chunk_data[ chunk_data_offset ] );
	binary_xml_token_data_size = chunk_data_size - chunk_data_offset;

	if( binary_xml_token_data_size < 1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid binary XML token data size value too small.",
		 function );

		goto on_error;
	}
	switch( binary_xml_token_data[ 0 ] & 0x3f )
	{
		case LIBEVTX_BINARY_XML_TOKEN_END_OF_FILE:
		case LIBEVTX_BINARY_XML_TOKEN_CLOSE_START_ELEMENT_TAG:
		case LIBEVTX_BINARY_XML_TOKEN_CLOSE_EMPTY_ELEMENT_TAG:
		case LIBEVTX_BINARY_XML_TOKEN_END_ELEMENT_TAG:
			binary_xml_token->size = 1;
			break;

		case LIBEVTX_BINARY_XML_TOKEN_OPEN_START_ELEMENT_TAG:
			byte_stream_copy_to_uint32_little_endian(
			 &( binary_xml_token_data[ 3 ] ),
			 binary_xml_token->size );

			break;

		case LIBEVTX_BINARY_XML_TOKEN_VALUE:
		case LIBEVTX_BINARY_XML_TOKEN_ATTRIBUTE:
		case LIBEVTX_BINARY_XML_TOKEN_CDATA_SECTION:
		case LIBEVTX_BINARY_XML_TOKEN_CHARACTER_REFERENCE:
		case LIBEVTX_BINARY_XML_TOKEN_ENTITY_REFERENCE:
		case LIBEVTX_BINARY_XML_TOKEN_PI_TARGET:
		case LIBEVTX_BINARY_XML_TOKEN_PI_DATA:
			binary_xml_token->size = 1;
			break;

		case LIBEVTX_BINARY_XML_TOKEN_TEMPLATE_INSTANCE:
			binary_xml_token->size = 34;
			break;

		case LIBEVTX_BINARY_XML_TOKEN_NORMAL_SUBSTITUTION:
		case LIBEVTX_BINARY_XML_TOKEN_OPTIONAL_SUBSTITUTION:
		case LIBEVTX_BINARY_XML_TOKEN_REPEATED_SUBSTITUTION:
			binary_xml_token->size = 4;
			break;

		default:
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
			 "%s: unsupported binary XML token type: 0x%02" PRIx8 ".",
			 function,
			 binary_xml_token_data[ 0 ] & 0x3f );

			goto on_error;
	}
	binary_xml_token->type = binary_xml_token_data[ 0 ];

#if defined( HAVE_DEBUG_OUTPUT )
	if( libnotify_verbose != 0 )
	{
		libnotify_printf(
		 "%s: binary XML token header data:\n",
		 function );
		libnotify_print_data(
		 binary_xml_token_data,
		 binary_xml_token->size,
		 0 );
	}
#endif
	return( 1 );

on_error:
	return( -1 );
}
