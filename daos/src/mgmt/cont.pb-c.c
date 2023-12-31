/* Generated by the protocol buffer compiler.  DO NOT EDIT! */
/* Generated from: cont.proto */

/* Do not generate deprecated warnings for self */
#ifndef PROTOBUF_C__NO_DEPRECATED
#define PROTOBUF_C__NO_DEPRECATED
#endif

#include "cont.pb-c.h"
void   mgmt__cont_set_owner_req__init
                     (Mgmt__ContSetOwnerReq         *message)
{
  static const Mgmt__ContSetOwnerReq init_value = MGMT__CONT_SET_OWNER_REQ__INIT;
  *message = init_value;
}
size_t mgmt__cont_set_owner_req__get_packed_size
                     (const Mgmt__ContSetOwnerReq *message)
{
  assert(message->base.descriptor == &mgmt__cont_set_owner_req__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t mgmt__cont_set_owner_req__pack
                     (const Mgmt__ContSetOwnerReq *message,
                      uint8_t       *out)
{
  assert(message->base.descriptor == &mgmt__cont_set_owner_req__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t mgmt__cont_set_owner_req__pack_to_buffer
                     (const Mgmt__ContSetOwnerReq *message,
                      ProtobufCBuffer *buffer)
{
  assert(message->base.descriptor == &mgmt__cont_set_owner_req__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
Mgmt__ContSetOwnerReq *
       mgmt__cont_set_owner_req__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (Mgmt__ContSetOwnerReq *)
     protobuf_c_message_unpack (&mgmt__cont_set_owner_req__descriptor,
                                allocator, len, data);
}
void   mgmt__cont_set_owner_req__free_unpacked
                     (Mgmt__ContSetOwnerReq *message,
                      ProtobufCAllocator *allocator)
{
  if(!message)
    return;
  assert(message->base.descriptor == &mgmt__cont_set_owner_req__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
void   mgmt__cont_set_owner_resp__init
                     (Mgmt__ContSetOwnerResp         *message)
{
  static const Mgmt__ContSetOwnerResp init_value = MGMT__CONT_SET_OWNER_RESP__INIT;
  *message = init_value;
}
size_t mgmt__cont_set_owner_resp__get_packed_size
                     (const Mgmt__ContSetOwnerResp *message)
{
  assert(message->base.descriptor == &mgmt__cont_set_owner_resp__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t mgmt__cont_set_owner_resp__pack
                     (const Mgmt__ContSetOwnerResp *message,
                      uint8_t       *out)
{
  assert(message->base.descriptor == &mgmt__cont_set_owner_resp__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t mgmt__cont_set_owner_resp__pack_to_buffer
                     (const Mgmt__ContSetOwnerResp *message,
                      ProtobufCBuffer *buffer)
{
  assert(message->base.descriptor == &mgmt__cont_set_owner_resp__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
Mgmt__ContSetOwnerResp *
       mgmt__cont_set_owner_resp__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (Mgmt__ContSetOwnerResp *)
     protobuf_c_message_unpack (&mgmt__cont_set_owner_resp__descriptor,
                                allocator, len, data);
}
void   mgmt__cont_set_owner_resp__free_unpacked
                     (Mgmt__ContSetOwnerResp *message,
                      ProtobufCAllocator *allocator)
{
  if(!message)
    return;
  assert(message->base.descriptor == &mgmt__cont_set_owner_resp__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
static const ProtobufCFieldDescriptor mgmt__cont_set_owner_req__field_descriptors[6] =
{
  {
    "sys",
    1,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_STRING,
    0,   /* quantifier_offset */
    offsetof(Mgmt__ContSetOwnerReq, sys),
    NULL,
    &protobuf_c_empty_string,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "contUUID",
    2,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_STRING,
    0,   /* quantifier_offset */
    offsetof(Mgmt__ContSetOwnerReq, contuuid),
    NULL,
    &protobuf_c_empty_string,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "poolUUID",
    3,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_STRING,
    0,   /* quantifier_offset */
    offsetof(Mgmt__ContSetOwnerReq, pooluuid),
    NULL,
    &protobuf_c_empty_string,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "owneruser",
    4,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_STRING,
    0,   /* quantifier_offset */
    offsetof(Mgmt__ContSetOwnerReq, owneruser),
    NULL,
    &protobuf_c_empty_string,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "ownergroup",
    5,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_STRING,
    0,   /* quantifier_offset */
    offsetof(Mgmt__ContSetOwnerReq, ownergroup),
    NULL,
    &protobuf_c_empty_string,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "svc_ranks",
    6,
    PROTOBUF_C_LABEL_REPEATED,
    PROTOBUF_C_TYPE_UINT32,
    offsetof(Mgmt__ContSetOwnerReq, n_svc_ranks),
    offsetof(Mgmt__ContSetOwnerReq, svc_ranks),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned mgmt__cont_set_owner_req__field_indices_by_name[] = {
  1,   /* field[1] = contUUID */
  4,   /* field[4] = ownergroup */
  3,   /* field[3] = owneruser */
  2,   /* field[2] = poolUUID */
  5,   /* field[5] = svc_ranks */
  0,   /* field[0] = sys */
};
static const ProtobufCIntRange mgmt__cont_set_owner_req__number_ranges[1 + 1] =
{
  { 1, 0 },
  { 0, 6 }
};
const ProtobufCMessageDescriptor mgmt__cont_set_owner_req__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "mgmt.ContSetOwnerReq",
  "ContSetOwnerReq",
  "Mgmt__ContSetOwnerReq",
  "mgmt",
  sizeof(Mgmt__ContSetOwnerReq),
  6,
  mgmt__cont_set_owner_req__field_descriptors,
  mgmt__cont_set_owner_req__field_indices_by_name,
  1,  mgmt__cont_set_owner_req__number_ranges,
  (ProtobufCMessageInit) mgmt__cont_set_owner_req__init,
  NULL,NULL,NULL    /* reserved[123] */
};
static const ProtobufCFieldDescriptor mgmt__cont_set_owner_resp__field_descriptors[1] =
{
  {
    "status",
    1,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_INT32,
    0,   /* quantifier_offset */
    offsetof(Mgmt__ContSetOwnerResp, status),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned mgmt__cont_set_owner_resp__field_indices_by_name[] = {
  0,   /* field[0] = status */
};
static const ProtobufCIntRange mgmt__cont_set_owner_resp__number_ranges[1 + 1] =
{
  { 1, 0 },
  { 0, 1 }
};
const ProtobufCMessageDescriptor mgmt__cont_set_owner_resp__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "mgmt.ContSetOwnerResp",
  "ContSetOwnerResp",
  "Mgmt__ContSetOwnerResp",
  "mgmt",
  sizeof(Mgmt__ContSetOwnerResp),
  1,
  mgmt__cont_set_owner_resp__field_descriptors,
  mgmt__cont_set_owner_resp__field_indices_by_name,
  1,  mgmt__cont_set_owner_resp__number_ranges,
  (ProtobufCMessageInit) mgmt__cont_set_owner_resp__init,
  NULL,NULL,NULL    /* reserved[123] */
};
