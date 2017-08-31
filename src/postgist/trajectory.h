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


struct trajectory_elem
{
  // int32 dummy;    /* Padding to make it double aligned. */
  Timestamp time_obj;
  LWGEOM *geom_elem;       /* Geometry Object - */
};

#define DatumGetTrajectoryElem(X)      ((struct trajectory_elem*) PG_DETOAST_DATUM(X))
#define PG_GETARG_TRAJECTELEM_TYPE_P(n)  DatumGetTrajectoryElem(PG_GETARG_DATUM(n))
#define PG_RETURN_TRAJECTELEM_TYPE_P(x)  PG_RETURN_POINTER(x)


extern Datum create_trajectory_elem(PG_FUNCTION_ARGS);
extern Datum trajectory_elem_in(PG_FUNCTION_ARGS);
extern Datum trajectory_elem_out(PG_FUNCTION_ARGS);

#endif  /* __POSTGIST_H__ */
