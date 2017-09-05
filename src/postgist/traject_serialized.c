/* postgist extension */
#include "trajectory.h"
#include "hexutils.h"


/****
** This code reuse some code of postgis g_serialized.c and VAGUEGEOMETRY
** links into doc
**/



int32_t tegserialized_get_srid(const struct TESERIALIZED *s)
{
	int32_t srid = 0;
	srid = srid | (s->srid[0] << 16);
	srid = srid | (s->srid[1] << 8);
	srid = srid | s->srid[2];
	/* Only the first 21 bits are set. Slide up and back to pull
	   the negative bits down, if we need them. */
	srid = (srid<<11)>>11;

	/* 0 is our internal unknown value. We'll map back and forth here for now */
	if ( srid == 0 )
		return SRID_UNKNOWN;
	else
		return clamp_srid(srid);
}
uint32_t gserialized_get_type(const GSERIALIZED *tj)
{
	uint8_t type;
	uint8_t *pt;
	// assert(tj);

	pt = (uint8_t*)(tj->data);
	pt += sizeof(uint32_t);


}

// size_t gserialized_from_lwgeom_size(const LWGEOM *geom)
// {
// 	size_t size = 8; /* Header overhead. */
// 	assert(geom);
//
// 	if ( geom->bbox )
// 		size += gbox_serialized_size(geom->flags);
//
// 	size += gserialized_from_any_size(geom);
// 	elog(NOTICE, "g_serialize size = %d", size);
//
// 	return size;
// }
/***********************************************************************
* Serialize an LWGEOM into GSERIALIZED.
*/

/* Private functions */

static size_t gserialized_from_lwgeom_any(const LWGEOM *geom, uint8_t *buf);

static size_t gserialized_from_lwpoint(const LWPOINT *point, uint8_t *buf)
{
	uint8_t *loc;
	int ptsize = ptarray_point_size(point->point);
	int type = POINTTYPE;

	assert(point);
	assert(buf);

	if ( FLAGS_GET_ZM(point->flags) != FLAGS_GET_ZM(point->point->flags) )
		lwerror("Dimensions mismatch in lwpoint");

	LWDEBUGF(2, "lwpoint_to_gserialized(%p, %p) called", point, buf);

	loc = buf;

	/* Write in the type. */
	memcpy(loc, &type, sizeof(uint32_t));
	loc += sizeof(uint32_t);
	/* Write in the number of points (0 => empty). */
	memcpy(loc, &(point->point->npoints), sizeof(uint32_t));
	loc += sizeof(uint32_t);

	/* Copy in the ordinates. */
	if ( point->point->npoints > 0 )
	{
		memcpy(loc, getPoint_internal(point->point, 0), ptsize);
		loc += ptsize;
	}

	return (size_t)(loc - buf);
}

struct TREGEOM *serialization_to_traj_elem(const struct TESERIALIZED *tg)
{
  LWGEOM *geom_elem = NULL;
  Timestamp time_obj = 0;

  uint8_t g_flags = 0;
  int32_t g_srid = 0;
  uint32_t g_type = 0;
  uint8_t *data_ptr = NULL;
  GBOX bbox;
  size_t g_size = 0;

  g_srid = tegserialized_get_srid(tg);
	g_type = gserialized_get_type(tg);

}

static size_t trjserialized_from_tj(const struct TREGEOM * tgeom, uint8_t *buf)
{
	uint8_t *loc = buf;
	size_t return_size, subsize;

	if(HAS_BOTH(tgeom->flags))
	{
		size_t time_elem_size, geom_elem_size;

		// get size timestamp
		time_elem_size = sizeof(Timestamp);


		memcpy(loc, &time_elem_size, sizeof(uint32_t));
		loc += sizeof(uint32_t);

		//get size geom_elem
		geom_elem_size += (gserialized_from_lwgeom_size(tgeom->geom_elem)-8);
		geom_elem_size += sizeof(uint8_t); //one byte because of its flags
		geom_elem_size += 7; // padding

		memcpy(loc, &geom_elem_size, sizeof(uint32_t));
		loc += sizeof(uint32_t);
	}
}

/*Calcula o segmento de memoria necessaria para conter o tipo TREGEOM */
static size_t trserialized_from_tj_size(const struct TREGEOM * tgeom);
size_t trjserialized_from_tj_size(const struct TREGEOM * tgeom)
{
	size_t size = 0;
	// assert(tgeom);

	if(HAS_NOTHING(tgeom->flags))
	{
		size = sizeof(uint32_t) + sizeof(uint32_t);
	}
	if(HAS_TIME(tgeom->flags))
	{
		size += sizeof(uint8_t);
		size += sizeof(uint8_t);
		size += sizeof(uint8_t);
		size += sizeof(uint8_t);
		size += sizeof(uint8_t);
		size += sizeof(uint32_t);

		/*por ser de tamanho fixo posso utilizar assim */
		size += sizeof(Timestamp);
	}

	if (HAS_GEOM(tgeom->flags)) {
		size += sizeof(uint8_t);
		size += sizeof(uint8_t);
		size += sizeof(uint8_t);
		size += sizeof(uint8_t);
		size += sizeof(uint32_t);

		size += (gserialized_from_lwgeom_size((tgeom->geom_elem))-8);

	}

	return size;
}
// static void teserialized_harmonize_bbox_component(LWGEOM *comp)
// {
// 	/*adcionar bounding box*/
// 	/*no caso o lwgeom, jah vem pronto, portanto esta parte fica para o postgis*/
// }

struct TESERIALIZED *tregeom_serialize(struct TREGEOM *geom, size_t *size)
{
	size_t expected_size = 0;
	size_t return_size = 0;
	uint8_t *serialize = NULL;
	uint8_t *ptr;
	struct TESERIALIZED *result = NULL;

	expected_size = 8;
	expected_size += trjserialized_from_tj_size(geom);

	serialize = (uint8_t *) lwalloc(expected_size);
	ptr = serialize;

  /*move past size, srid and flag*/
	ptr += 8;

	/*serialization process*/
	ptr += trjserialized_from_tj(geom, ptr);
}
