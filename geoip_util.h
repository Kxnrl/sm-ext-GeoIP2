#ifndef _INCLUDE_SOURCEMOD_GEOIPUTIL_H_
#define _INCLUDE_SOURCEMOD_GEOIPUTIL_H_

#include <string>

#include "extension.h"

bool lookupByIp(const char *ip, const char **path, MMDB_entry_data_s *result);
std::string lookupString(const char *ip, const char **path);

extern const char GeoIPCountryCode[252][3];
extern const char GeoIPCountryCode3[252][4];

#endif // _INCLUDE_SOURCEMOD_GEOIPUTIL_H_
