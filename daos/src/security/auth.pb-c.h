/* Generated by the protocol buffer compiler.  DO NOT EDIT! */
/* Generated from: auth.proto */

#ifndef PROTOBUF_C_auth_2eproto__INCLUDED
#define PROTOBUF_C_auth_2eproto__INCLUDED

#include <protobuf-c/protobuf-c.h>

PROTOBUF_C__BEGIN_DECLS

#if PROTOBUF_C_VERSION_NUMBER < 1003000
# error This file was generated by a newer version of protoc-c which is incompatible with your libprotobuf-c headers. Please update your headers.
#elif 1003000 < PROTOBUF_C_MIN_COMPILER_VERSION
# error This file was generated by an older version of protoc-c which is incompatible with your libprotobuf-c headers. Please regenerate this file with a newer version of protoc-c.
#endif


typedef struct _Auth__Token Auth__Token;
typedef struct _Auth__Sys Auth__Sys;
typedef struct _Auth__Credential Auth__Credential;
typedef struct _Auth__GetCredResp Auth__GetCredResp;
typedef struct _Auth__ValidateCredReq Auth__ValidateCredReq;
typedef struct _Auth__ValidateCredResp Auth__ValidateCredResp;


/* --- enums --- */

/*
 * Types of authentication token
 */
typedef enum _Auth__Flavor {
  AUTH__FLAVOR__AUTH_NONE = 0,
  AUTH__FLAVOR__AUTH_SYS = 1
    PROTOBUF_C__FORCE_ENUM_TO_BE_INT_SIZE(AUTH__FLAVOR)
} Auth__Flavor;

/* --- messages --- */

struct  _Auth__Token
{
  ProtobufCMessage base;
  /*
   * flavor of this authentication token
   */
  Auth__Flavor flavor;
  /*
   * packed structure of the specified flavor
   */
  ProtobufCBinaryData data;
};
#define AUTH__TOKEN__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&auth__token__descriptor) \
    , AUTH__FLAVOR__AUTH_NONE, {0,NULL} }


/*
 * Token structure for AUTH_SYS flavor cred
 */
struct  _Auth__Sys
{
  ProtobufCMessage base;
  /*
   * timestamp
   */
  uint64_t stamp;
  /*
   * machine name
   */
  char *machinename;
  /*
   * user name
   */
  char *user;
  /*
   * primary group name
   */
  char *group;
  /*
   * secondary group names
   */
  size_t n_groups;
  char **groups;
  /*
   * Additional field for MAC label
   */
  char *secctx;
};
#define AUTH__SYS__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&auth__sys__descriptor) \
    , 0, (char *)protobuf_c_empty_string, (char *)protobuf_c_empty_string, (char *)protobuf_c_empty_string, 0,NULL, (char *)protobuf_c_empty_string }


/*
 * Token and verifier are expected to have the same flavor type.
 */
struct  _Auth__Credential
{
  ProtobufCMessage base;
  /*
   * authentication token
   */
  Auth__Token *token;
  /*
   * to verify integrity of the token
   */
  Auth__Token *verifier;
  /*
   * the agent that created this credential
   */
  char *origin;
};
#define AUTH__CREDENTIAL__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&auth__credential__descriptor) \
    , NULL, NULL, (char *)protobuf_c_empty_string }


/*
 * GetCredResp represents the result of a request to fetch authentication
 * credentials.
 */
struct  _Auth__GetCredResp
{
  ProtobufCMessage base;
  /*
   * Status of the request
   */
  int32_t status;
  /*
   * Caller's authentication credential
   */
  Auth__Credential *cred;
};
#define AUTH__GET_CRED_RESP__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&auth__get_cred_resp__descriptor) \
    , 0, NULL }


/*
 * ValidateCredReq represents a request to verify a set of authentication
 * credentials.
 */
struct  _Auth__ValidateCredReq
{
  ProtobufCMessage base;
  /*
   * Credential to be validated
   */
  Auth__Credential *cred;
};
#define AUTH__VALIDATE_CRED_REQ__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&auth__validate_cred_req__descriptor) \
    , NULL }


/*
 * ValidateCredResp represents the result of a request to validate
 * authentication credentials.
 */
struct  _Auth__ValidateCredResp
{
  ProtobufCMessage base;
  /*
   * Status of the request
   */
  int32_t status;
  /*
   * Validated authentication token from the credential
   */
  Auth__Token *token;
};
#define AUTH__VALIDATE_CRED_RESP__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&auth__validate_cred_resp__descriptor) \
    , 0, NULL }


/* Auth__Token methods */
void   auth__token__init
                     (Auth__Token         *message);
size_t auth__token__get_packed_size
                     (const Auth__Token   *message);
size_t auth__token__pack
                     (const Auth__Token   *message,
                      uint8_t             *out);
size_t auth__token__pack_to_buffer
                     (const Auth__Token   *message,
                      ProtobufCBuffer     *buffer);
Auth__Token *
       auth__token__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   auth__token__free_unpacked
                     (Auth__Token *message,
                      ProtobufCAllocator *allocator);
/* Auth__Sys methods */
void   auth__sys__init
                     (Auth__Sys         *message);
size_t auth__sys__get_packed_size
                     (const Auth__Sys   *message);
size_t auth__sys__pack
                     (const Auth__Sys   *message,
                      uint8_t             *out);
size_t auth__sys__pack_to_buffer
                     (const Auth__Sys   *message,
                      ProtobufCBuffer     *buffer);
Auth__Sys *
       auth__sys__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   auth__sys__free_unpacked
                     (Auth__Sys *message,
                      ProtobufCAllocator *allocator);
/* Auth__Credential methods */
void   auth__credential__init
                     (Auth__Credential         *message);
size_t auth__credential__get_packed_size
                     (const Auth__Credential   *message);
size_t auth__credential__pack
                     (const Auth__Credential   *message,
                      uint8_t             *out);
size_t auth__credential__pack_to_buffer
                     (const Auth__Credential   *message,
                      ProtobufCBuffer     *buffer);
Auth__Credential *
       auth__credential__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   auth__credential__free_unpacked
                     (Auth__Credential *message,
                      ProtobufCAllocator *allocator);
/* Auth__GetCredResp methods */
void   auth__get_cred_resp__init
                     (Auth__GetCredResp         *message);
size_t auth__get_cred_resp__get_packed_size
                     (const Auth__GetCredResp   *message);
size_t auth__get_cred_resp__pack
                     (const Auth__GetCredResp   *message,
                      uint8_t             *out);
size_t auth__get_cred_resp__pack_to_buffer
                     (const Auth__GetCredResp   *message,
                      ProtobufCBuffer     *buffer);
Auth__GetCredResp *
       auth__get_cred_resp__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   auth__get_cred_resp__free_unpacked
                     (Auth__GetCredResp *message,
                      ProtobufCAllocator *allocator);
/* Auth__ValidateCredReq methods */
void   auth__validate_cred_req__init
                     (Auth__ValidateCredReq         *message);
size_t auth__validate_cred_req__get_packed_size
                     (const Auth__ValidateCredReq   *message);
size_t auth__validate_cred_req__pack
                     (const Auth__ValidateCredReq   *message,
                      uint8_t             *out);
size_t auth__validate_cred_req__pack_to_buffer
                     (const Auth__ValidateCredReq   *message,
                      ProtobufCBuffer     *buffer);
Auth__ValidateCredReq *
       auth__validate_cred_req__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   auth__validate_cred_req__free_unpacked
                     (Auth__ValidateCredReq *message,
                      ProtobufCAllocator *allocator);
/* Auth__ValidateCredResp methods */
void   auth__validate_cred_resp__init
                     (Auth__ValidateCredResp         *message);
size_t auth__validate_cred_resp__get_packed_size
                     (const Auth__ValidateCredResp   *message);
size_t auth__validate_cred_resp__pack
                     (const Auth__ValidateCredResp   *message,
                      uint8_t             *out);
size_t auth__validate_cred_resp__pack_to_buffer
                     (const Auth__ValidateCredResp   *message,
                      ProtobufCBuffer     *buffer);
Auth__ValidateCredResp *
       auth__validate_cred_resp__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   auth__validate_cred_resp__free_unpacked
                     (Auth__ValidateCredResp *message,
                      ProtobufCAllocator *allocator);
/* --- per-message closures --- */

typedef void (*Auth__Token_Closure)
                 (const Auth__Token *message,
                  void *closure_data);
typedef void (*Auth__Sys_Closure)
                 (const Auth__Sys *message,
                  void *closure_data);
typedef void (*Auth__Credential_Closure)
                 (const Auth__Credential *message,
                  void *closure_data);
typedef void (*Auth__GetCredResp_Closure)
                 (const Auth__GetCredResp *message,
                  void *closure_data);
typedef void (*Auth__ValidateCredReq_Closure)
                 (const Auth__ValidateCredReq *message,
                  void *closure_data);
typedef void (*Auth__ValidateCredResp_Closure)
                 (const Auth__ValidateCredResp *message,
                  void *closure_data);

/* --- services --- */


/* --- descriptors --- */

extern const ProtobufCEnumDescriptor    auth__flavor__descriptor;
extern const ProtobufCMessageDescriptor auth__token__descriptor;
extern const ProtobufCMessageDescriptor auth__sys__descriptor;
extern const ProtobufCMessageDescriptor auth__credential__descriptor;
extern const ProtobufCMessageDescriptor auth__get_cred_resp__descriptor;
extern const ProtobufCMessageDescriptor auth__validate_cred_req__descriptor;
extern const ProtobufCMessageDescriptor auth__validate_cred_resp__descriptor;

PROTOBUF_C__END_DECLS


#endif  /* PROTOBUF_C_auth_2eproto__INCLUDED */
