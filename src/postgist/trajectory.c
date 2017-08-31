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


 PG_FUNCTION_INFO_V1(create_trajectory_elem);

 Datum
 create_trajectory_elem(PG_FUNCTION_ARGS)
 {
   Timestamp *time_geom = PG_GETARG_TIMESTAMP(0);
   GSERIALIZED *geom = (GSERIALIZED*)PG_DETOAST_DATUM(PG_GETARG_DATUM(1));

   struct trajectory_elem *trje = (struct trajectory_elem *) palloc(sizeof(struct trajectory_elem));

   trje->time_obj = time_geom;

   /*get lwgeom from GSERIALIZED varlena*/
   trje->geom_elem = lwgeom_from_gserialized(geom);

   if ( lwgeom_is_empty(trje->geom_elem))
   {
     PG_FREE_IF_COPY(geom, 0);
     PG_RETURN_NULL();
   }


    /*test for create_trajectory_elem function */
    /*should return hex string*/
    char *hexwkb;
    size_t hexwkb_size;

    //  @param variant. Unsigned bitmask value. Accepts one of: WKB_ISO, WKB_EXTENDED, WKB_SFSQL.
    hexwkb = lwgeom_to_hexwkb(trje->geom_elem, WKB_EXTENDED, &hexwkb_size);

    elog(NOTICE, "sizeof %d ", strlen(hexwkb));

    PG_FREE_IF_COPY(geom, 0);

    elog(NOTICE, "trajectory_elem Finished");

    PG_RETURN_CSTRING(hexwkb);

  //  PG_RETURN_TRAJECTELEM_TYPE_P(trje);
 }

 PG_FUNCTION_INFO_V1(trajectory_elem_in);

 Datum
 trajectory_elem_in(PG_FUNCTION_ARGS)
 {

 }

 PG_FUNCTION_INFO_V1(trajectory_elem_out);

 Datum
 trajectory_elem_out(PG_FUNCTION_ARGS)
 {
  //  struct trajectory_elem *trje = (struct trajectory_elem *) palloc(sizeof(struct trajectory_elem));
   //
  //  int size = sizeof(Timestamp) + sizeof(LWGEOM); /*get size from lwgeom_to_wkb_size*/
   //
  //  char *hstr = palloc(2 * size + 1);
   //
  //  char *cp = NULL;

 }
