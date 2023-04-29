#pragma once
#include "pch.h"

struct  hostent {
    char    FAR* h_name;           /* official name of host */
    char    FAR* FAR* h_aliases;  /* alias list */
    short   h_addrtype;             /* host address type */
    short   h_length;               /* length of address */
    char    FAR* FAR* h_addr_list; /* list of addresses */
#define h_addr  h_addr_list[0]          /* address, for backward compat */
};
//
// IPv4 Internet address
// This is an 'on-wire' format structure.
//
typedef struct in_addr {
    union {
        struct { UCHAR s_b1, s_b2, s_b3, s_b4; } S_un_b;
        struct { USHORT s_w1, s_w2; } S_un_w;
        ULONG S_addr;
    } S_un;
#define s_addr  S_un.S_addr /* can be used for most tcp & ip code */
#define s_host  S_un.S_un_b.s_b2    // host on imp
#define s_net   S_un.S_un_b.s_b1    // network
#define s_imp   S_un.S_un_w.s_w2    // imp
#define s_impno S_un.S_un_b.s_b4    // imp #
#define s_lh    S_un.S_un_b.s_b3    // logical host
} IN_ADDR, * PIN_ADDR, FAR* LPIN_ADDR;
/*
 * Socket address, internet style.
 */
struct sockaddr_in {
    short   sin_family;
    u_short sin_port;
    struct  in_addr sin_addr;
    char    sin_zero[8];
};

#define WSADESCRIPTION_LEN      256
#define WSASYS_STATUS_LEN       128

typedef struct WSAData {
    WORD                    wVersion;
    WORD                    wHighVersion;
#ifdef _WIN64
    unsigned short          iMaxSockets;
    unsigned short          iMaxUdpDg;
    char FAR* lpVendorInfo;
    char                    szDescription[WSADESCRIPTION_LEN + 1];
    char                    szSystemStatus[WSASYS_STATUS_LEN + 1];
#else
    char                    szDescription[WSADESCRIPTION_LEN + 1];
    char                    szSystemStatus[WSASYS_STATUS_LEN + 1];
    unsigned short          iMaxSockets;
    unsigned short          iMaxUdpDg;
    char FAR* lpVendorInfo;
#endif
} WSADATA;

typedef WSADATA FAR* LPWSADATA;