/*Copyright (C) 2017 National Institute For Space Research (INPE) - Brazil.*/
/*!
 *
 * \file postgist/hexutils.c
 *
 * \brief Hex-utilities for GeoExt.
 *
 * \author Gilberto Ribeiro de Queiroz
 * \author Fabiana Zioti
 *
 * \date 2017
 *
 *
 */

/* GeoExt */
#include "hexutils.h"


/* C Standard Library */
#include <assert.h>


static char hex_table[]={"0123456789ABCDEF" };


/*
 * \brief Encode the byte 'c' as a double-byte hex-string
 *
 */
static inline void char2hex(unsigned char c, char *r)
{
  int h;  // high byte
  int l;  // low byte

  h = (c >> 4);
  l = (c & 0x0F);

  r[0] = hex_table[h];
  r[1] = hex_table[l];
}


void binary2hex(const char *byte_str, int size, char *hex_str)
{
  int i = 0;

  for(; i < size; ++i)
    char2hex(byte_str[i], hex_str + (i * 2));

  hex_str[i * 2] = '\0';
}


void hex2binary(const char *hex_str, int h_size, char *byte_str)
{
  int size = h_size / 2;

  char h, l;

  assert((h_size % 2) == 0);

  for(int i = 0; i < size; ++i)
  {
    char c = hex_str[i * 2];

    if(c >= '0' && c <= '9')
      h = c - 48;
    else
      h = c + 10 - 65;

    c = hex_str[i * 2 + 1];

    if((c >= '0') && (c <= '9'))
      l = c - 48;
    else
      l = c + 10 - 65;

    byte_str[i] = (h << 4) + l;
  }
}
