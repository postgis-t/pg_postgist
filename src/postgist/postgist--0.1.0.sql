--
-- Complain if script is sourced in psql, rather than via CREATE EXTENSION
--
\echo Use "CREATE EXTENSION postgist" to load this file. \quit

CREATE OR REPLACE FUNCTION create_trj_element(timestamp, geometry)
    RETURNS cstring
    AS 'MODULE_PATHNAME','create_trajectory_elem'
    LANGUAGE C IMMUTABLE STRICT;
