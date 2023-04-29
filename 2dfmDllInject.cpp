// 2dfmDllInject.cpp : Definisce le funzioni esportate per la DLL.
//

#include "pch.h"
#include "winsock.h"
#include "2dfmDllInject.h"

#pragma comment(lib, "ws2_32.lib")
// Esempio di variabile esportata
//MY2DFMDLLINJECT_API int nMy2dfmDllInject=0;
//
//// Esempio di funzione esportata.
//MY2DFMDLLINJECT_API int fnMy2dfmDllInject(void)
//{
//    return 0;
//}

MY2DFMDLLINJECT_API u_short int_ntohs(u_short s)
{
    return ntohs(s);
}
MY2DFMDLLINJECT_API u_long int_ntohl(u_long l)
{
    return ntohl(l);
}

MY2DFMDLLINJECT_API struct hostent FAR* PASCAL FAR int_gethostbyname(_In_z_ const char FAR* name) {
    return gethostbyname(name);
}

MY2DFMDLLINJECT_API int PASCAL FAR int_gethostname(
    _Out_writes_bytes_to_(namelen, return) char FAR* name,
    _In_ int namelen) {
    return gethostname(name, namelen);
}

MY2DFMDLLINJECT_API int PASCAL FAR int_WSAStartup(
    _In_ WORD wVersionRequired,
    _Out_ LPWSADATA lpWSAData) {
    return WSAStartup(wVersionRequired, lpWSAData);
}
//
//// Costruttore di una classe esportata.
//CMy2dfmDllInject::CMy2dfmDllInject()
//{
//    return;
//}
