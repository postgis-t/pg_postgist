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

 /*!
  *
  * \file postgist/trajectory.h
  *
  * \brief
  *
  * \author Gilberto Ribeiro de Queiroz
  * \author Fabiana Zioti
  *
  * \date 2017
  *
  * \copyright GNU Lesser Public License version 3
  *
  */

#ifndef __POSTGIST_TRAJECTORY_H__
#define __POSTGIST_TRAJECTORY_H__

/* PostgreSQL */
#include <postgres.h>
#include <liblwgeom.h>
#include <lwgeom_pg.h>
#include <utils/timestamp.h>


#define HAS_TIME(flags) ((flags) & 0x01)
#define HAS_GEOM(flags) ((flags) & 0x02>>1)

#define FLAGS_SET_TIME(flags, value) ((flags) = (value) ? ((flags) | 0x01) : ((flags) & 0xFE))
#define FLAGS_SET_GEOM(flags, value) ((flags) = (value) ? ((flags) | 0x02) : ((flags) & 0xFD))

#define HAS_BOTH(flags) (HAS_TIME(flags) == 1 && HAS_GEOM(flags) == 1)
#define HAS_NOTHING(flags) (HAS_TIME(flags) == 0 && HAS_GEOM(flags) == 0)


/* TRAJYPE */
/*can be a POINT, LINETYPE, POLYGONTYPE
The TREGEOM must be same SRID and type of LWGEOM*/
struct TREGEOM
{
  uint8_t type;
  uint8_t flags;
  Timestamp time_obj;
  LWGEOM *geom_elem;       /* Geometry Object */
};

/**************************************************
* GSERIALIZED
***************************************************/
struct TESERIALIZED
{
  uint32_t size; /* For PgSQL use only, use VAR* macros to manipulate. - 4bytes */
  uint8_t srid[3]; /* 3 bytes of SRID */
  uint8_t flags; /* 1 byte flag*/
  uint8_t data[1]; /* data */
};


extern Datum TEG_in(PG_FUNCTION_ARGS);
extern Datum TEG_out(PG_FUNCTION_ARGS);
extern Datum construct_traject(PG_FUNCTION_ARGS);


extern struct TREGEOM *serialization_to_traj_elem(const struct TESERIALIZED *);
extern struct TESERIALIZED *tregeom_serialize(struct TREGEOM *geom, size_t *size);

struct TESERIALIZED *TEG_construct(LWGEOM *lwgeom, Timestamp timestamp);

int32_t tegserialized_get_srid(const struct TESERIALIZED *);
uint32_t gserialized_get_type(const GSERIALIZED *s);

extern LWGEOM *get_geom_from_serialization();
extern Timestamp *get_time_obj_from_serialization();

#endif  /* __POSTGIST_H__ */
