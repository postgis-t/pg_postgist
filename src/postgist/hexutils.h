/*Copyright (C) 2017 National Institute For Space Research (INPE) - Brazil.*/

/*!
 *
 * \file postgist/hexutils.h
 *
 * \brief Hex-utilities for postgis-t.
 *
 * \author Gilberto Ribeiro de Queiroz
 * \author Fabiana Zioti
 *
 * \date 2017
 *
 * \copyright GNU Lesser Public License version 3
 *
 */

#ifndef __GEOEXT_HEXUTILS_H__
#define __GEOEXT_HEXUTILS_H__


/*
 * \brief Encode the byte array to a null terminated hex-string.
 *
 * \note Clients of this function must assure that the buffer pointed by
 *       'hex_str' has enough space for encoding the data. This means: 2 * length(byte_str) + 1.
 *
 */
void binary2hex(const char *byte_str, int size, char *hex_str);


/*
 * \brief Decode an hex-string to a byte array.
 *
 * \note Clients of this function must assure that the buffer pointed by
 *       'byte_str' has enough space for decoding the data.
 *
 */
void hex2binary(const char *hex_str, int h_size, char *byte_str);

#endif  /* __GEOEXT_HEXUTILS_H__ */
