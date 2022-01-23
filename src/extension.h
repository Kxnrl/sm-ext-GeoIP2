#ifndef _INCLUDE_SOURCEMOD_EXTENSION_PROPER_H_
#define _INCLUDE_SOURCEMOD_EXTENSION_PROPER_H_

#include "smsdk_ext.h"
#include "maxminddb.h"
#include "am-string.h"

class Extension : public SDKExtension
{
	virtual bool SDK_OnLoad(char* error, size_t maxlength, bool late);
	virtual void SDK_OnUnload();
};

extern MMDB_s mmdb;
extern const sp_nativeinfo_t geoip_natives[];

#endif // !_INCLUDE_SOURCEMOD_EXTENSION_PROPER_H_
