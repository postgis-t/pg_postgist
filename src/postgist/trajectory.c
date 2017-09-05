/*
  Copyright (C) 2017 National Institute For Space Research (INPE) - Brazil.

  pg_postgist is free software: you can redistribute it and/or modify
  it under the terms of the GNU Lesser General Public License version 3 as
  published by the Free Software Foundation.

  pg_postgist is distributed  "AS-IS" in the hope that it will be useful,
  but WITHOUT ANY WARRANTY OF ANY KIND; without even the implied warranty
  of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public License
  along with pg_postgist. See LICENSE. If not, write to
  Gilberto Ribeiro de Queiroz at <gribeiro@dpi.inpe.br>.

 */

/* PostGIS-T*/
#include "trajectory.h"

/* PostgreSQL */
#include <libpq/pqformat.h>
#include <fmgr.h>
#include <utils/builtins.h>
#include <utils/timestamp.h>
#include <measures.h> /*para a funcao de teste*/

PG_FUNCTION_INFO_V1(TEG_in);

Datum
TEG_in(PG_FUNCTION_ARGS)
{

}

PG_FUNCTION_INFO_V1(TEG_out);

Datum
TEG_out(PG_FUNCTION_ARGS)
{
  struct TESERIALIZED *teg = (struct TESERIALIZED*)PG_DETOAST_DATUM(PG_GETARG_DATUM(0));
  struct TREGEOM *tegeom;
  char *result;
  size_t tehexwkb_size;

  tegeom = serialization_to_traj_elem(teg);
  result = tregeom_to_hexwkb(tegeom, WKB_EXTENDED, &tehexwkb_size);

  free(tegeom);
  PG_RETURN_CSTRING(result);
}

PG_FUNCTION_INFO_V1(construct);

Datum
construct_traject(PG_FUNCTION_ARGS)
{
  GSERIALIZED *geom = PG_GETARG_GSERIALIZED_P(0);

  LWGEOM *lwgeom = lwgeom_from_gserialized(geom);

  Timestamp timestamp = PG_GETARG_TIMESTAMP(1);

  PG_RETURN_POINTER(TEG_construct(lwgeom, timestamp));

}

struct TESERIALIZED *TEG_construct(LWGEOM *lwgeom, Timestamp timestamp)
{
  struct TREGEOM *tg = (struct TREGEOM *)palloc(sizeof(struct TREGEOM));
  struct TESERIALIZED *result = NULL;
  size_t ret_size = 0;

  if (lwgeom_is_empty(lwgeom)) {
    return NULL;
  }
  // verificar Timestamp

  tg->time_obj = timestamp;
  tg->geom_elem = lwgeom;

  FLAGS_SET_TIME(tg->flags, 1);
  FLAGS_SET_GEOM(tg->flags, 1);

  tg->type = lwgeom->type;


  result = tregeom_serialize(tg, &ret_size);
  SET_VARSIZE(result, ret_size);

  return result;
}
