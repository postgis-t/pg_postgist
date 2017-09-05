
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

/* Global variables */
#include "../postgis_config.h"
#include "liblwgeom_internal.h"
#include "lwgeom_log.h"

int
clamp_srid(int srid)
{
	int newsrid = srid;

	if ( newsrid <= 0 ) {
		if ( newsrid != SRID_UNKNOWN ) {
			newsrid = SRID_UNKNOWN;
			lwnotice("SRID value %d converted to the officially unknown SRID value %d", srid, newsrid);
		}
	} else if ( srid > SRID_MAXIMUM ) {
    newsrid = SRID_USER_MAXIMUM + 1 +
      /* -1 is to reduce likelyhood of clashes */
      /* NOTE: must match implementation in postgis_restore.pl */
      ( srid % ( SRID_MAXIMUM - SRID_USER_MAXIMUM - 1 ) );
		lwnotice("SRID value %d > SRID_MAXIMUM converted to %d", srid, newsrid);
	}

	return newsrid;
}
