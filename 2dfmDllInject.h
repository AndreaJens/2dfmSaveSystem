#ifdef MY2DFMDLLINJECT_EXPORTS
#define MY2DFMDLLINJECT_API //__declspec(dllexport)
#else
#define MY2DFMDLLINJECT_API __declspec(dllimport)
#endif

extern "C" MY2DFMDLLINJECT_API u_short int_ntohs(u_short s);
extern "C" MY2DFMDLLINJECT_API u_long int_ntohl(u_long l);
extern "C" MY2DFMDLLINJECT_API struct hostent FAR * PASCAL FAR int_gethostbyname(_In_z_ const char FAR * name);
extern "C" MY2DFMDLLINJECT_API int PASCAL FAR int_gethostname(
	_Out_writes_bytes_to_(namelen, return) char FAR* name,
	_In_ int namelen);
extern "C" MY2DFMDLLINJECT_API int PASCAL FAR int_WSAStartup(
	_In_ WORD wVersionRequired,
	_Out_ LPWSADATA lpWSAData);
