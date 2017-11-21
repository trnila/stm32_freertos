/* Automatically generated nanopb header */
/* Generated by nanopb-0.4.0-dev at Mon Nov 13 20:23:02 2017. */

#ifndef PB_MESSAGES_PB_H_INCLUDED
#define PB_MESSAGES_PB_H_INCLUDED
#include <pb.h>

/* @@protoc_insertion_point(includes) */
#if PB_PROTO_HEADER_VERSION != 30
#error Regenerate this file with the current version of nanopb generator.
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* Enum definitions */
typedef enum _GpioControlMsg_Port {
    GpioControlMsg_Port_PortA = 0,
    GpioControlMsg_Port_PortB = 1,
    GpioControlMsg_Port_PortC = 2
} GpioControlMsg_Port;
#define _GpioControlMsg_Port_MIN GpioControlMsg_Port_PortA
#define _GpioControlMsg_Port_MAX GpioControlMsg_Port_PortC
#define _GpioControlMsg_Port_ARRAYSIZE ((GpioControlMsg_Port)(GpioControlMsg_Port_PortC+1))

/* Struct definitions */
typedef struct _GpioControlMsg {
    GpioControlMsg_Port port;
    int32_t pin;
    bool state;
/* @@protoc_insertion_point(struct:GpioControlMsg) */
} GpioControlMsg;

typedef struct _ReverseMsg {
    char name[16];
    int32_t num;
/* @@protoc_insertion_point(struct:ReverseMsg) */
} ReverseMsg;

/* Default values for struct fields */

/* Initializer values for message structs */
#define ReverseMsg_init_default                  {"", 0}
#define GpioControlMsg_init_default              {(GpioControlMsg_Port)0, 0, 0}
#define ReverseMsg_init_zero                     {"", 0}
#define GpioControlMsg_init_zero                 {(GpioControlMsg_Port)0, 0, 0}

/* Field tags (for use in manual encoding/decoding) */
#define GpioControlMsg_port_tag                  1
#define GpioControlMsg_pin_tag                   2
#define GpioControlMsg_state_tag                 3
#define ReverseMsg_name_tag                      1
#define ReverseMsg_num_tag                       2

/* Struct field encoding specification for nanopb */
extern const pb_field_t ReverseMsg_fields[3];
extern const pb_field_t GpioControlMsg_fields[4];

/* Maximum encoded size of messages (where known) */
#define ReverseMsg_size                          29
#define GpioControlMsg_size                      15

/* Message IDs (where set with "msgid" option) */
#ifdef PB_MSGID

#define MESSAGES_MESSAGES \


#endif

#ifdef __cplusplus
} /* extern "C" */
#endif
/* @@protoc_insertion_point(eof) */

#endif
