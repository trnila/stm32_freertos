/* Automatically generated nanopb constant definitions */
/* Generated by nanopb-0.4.0-dev at Tue Nov 21 23:19:51 2017. */

#include "messages.pb.h"

/* @@protoc_insertion_point(includes) */
#if PB_PROTO_HEADER_VERSION != 30
#error Regenerate this file with the current version of nanopb generator.
#endif



const pb_field_t AckMsg_fields[2] = {
    PB_FIELD(  1, INT32   , REQUIRED, STATIC  , FIRST, AckMsg, id, id, 0),
    PB_LAST_FIELD
};

const pb_field_t ReverseMsg_fields[3] = {
    PB_FIELD(  1, STRING  , REQUIRED, STATIC  , FIRST, ReverseMsg, name, name, 0),
    PB_FIELD(  2, INT32   , REQUIRED, STATIC  , OTHER, ReverseMsg, num, name, 0),
    PB_LAST_FIELD
};

const pb_field_t GpioControlMsg_fields[4] = {
    PB_FIELD(  1, UENUM   , REQUIRED, STATIC  , FIRST, GpioControlMsg, port, port, 0),
    PB_FIELD(  2, INT32   , REQUIRED, STATIC  , OTHER, GpioControlMsg, pin, port, 0),
    PB_FIELD(  3, BOOL    , REQUIRED, STATIC  , OTHER, GpioControlMsg, state, pin, 0),
    PB_LAST_FIELD
};



/* @@protoc_insertion_point(eof) */
