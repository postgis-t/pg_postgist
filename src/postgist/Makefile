# The name of the shared library to be built from the multiple
# source files in the Postgist codebase.
MODULE_big = postgist

# As our extension uses multiple files, we have to
# set OBJS
OBJS = postgist.o trajectory.o hexutils.o lwutils.o traject_serialized.o

# The extension name: postgist
EXTENSION = postgist

# Files that will be installed under prefix/share/postgist
DATA = postgist--0.1.0.sql  # the script used to install the extension

# Should be changed according to your version of PostGIS
SHLIB_LINK = /opt/postgis-2.3.3/libpgcommon/libpgcommon.a /opt/postgis-2.3.3/postgis/postgis-2.3.so -L/usr/local/lib -lgeos_c -lproj -llwgeom
PG_CPPFLAGS = -I/usr/local/include -I/opt/postgis-2.3.3/liblwgeom/ -I/opt/postgis-2.3.3/libpgcommon/ -I/opt/postgis-2.3.3/postgis/ -fPIC


# Files that will be installed under prefix/doc/postgist
#DOCS = README.postgist

# Build based on pg_config framework
PG_CONFIG = pg_config

PGXS := $(shell $(PG_CONFIG) --pgxs)
include $(PGXS)
