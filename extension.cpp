#include "extension.h"
#include "geoip_util.h"

#ifdef _WIN32
#pragma comment(lib, "ws2_32.lib")
#endif

/**
 * @file extension.cpp
 * @brief Implement extension code here.
 */
GeoIP_Extension g_GeoIP;
MMDB_s mmdb;

SMEXT_LINK(&g_GeoIP);

bool GeoIP_Extension::SDK_OnLoad(char *error, size_t maxlength, bool late)
{
	if (mmdb.filename) // Already loaded.
	{
		return true;
	}

	const char *databases[] =
	{
		"GeoIP2-City",
		"GeoLite2-City",
		"GeoIP2-Country",
		"GeoLite2-Country"
	};

	char path[PLATFORM_MAX_PATH];
	int status;

	for (size_t i = 0; i < SM_ARRAYSIZE(databases); ++i)
	{
		g_pSM->BuildPath(Path_SM, path, sizeof(path), "configs/geoip/%s.mmdb", databases[i]);

		status = MMDB_open(path, MMDB_MODE_MMAP, &mmdb);

		if (status == MMDB_SUCCESS)
		{
			break;
		}
	
	}

	if (status != MMDB_SUCCESS)
	{
		ke::SafeStrcpy(error, maxlength, "Could not find GeoIP2 databases. download url -> https://dev.maxmind.com/geoip/geoip2/geolite2 .");
		return false;
	}

	g_pShareSys->AddNatives(myself, geoip_natives);
	g_pShareSys->RegisterLibrary(myself, "GeoIP2");

	char date[40];
	const time_t epoch = (const time_t)mmdb.metadata.build_epoch;
	strftime(date, 40, "%F %T UTC", gmtime(&epoch));

	g_pSM->LogMessage(myself, "GeoIP2 database loaded: %s (%s)", mmdb.metadata.database_type, date);

	return true;
}

void GeoIP_Extension::SDK_OnUnload()
{
	MMDB_close(&mmdb);
}

inline void StripPort(char *ip)
{
	char *tmp = strchr(ip, ':');
	if (!tmp)
		return;
	*tmp = '\0';
}

static cell_t sm_Geoip_Code2(IPluginContext *pCtx, const cell_t *params)
{
	char *ip;

	pCtx->LocalToString(params[1], &ip);
	StripPort(ip);

	const char *path[] = {"country", "iso_code", NULL};
	ke::AString str = lookupString(ip, path);
	const char *ccode = str.chars();

	pCtx->StringToLocal(params[2], 3, ccode);

	return (strlen(ccode) != 0) ? 1 : 0;
}

static cell_t sm_Geoip_Code3(IPluginContext *pCtx, const cell_t *params)
{
	char *ip;

	pCtx->LocalToString(params[1], &ip);
	StripPort(ip);

	const char *path[] = {"country", "iso_code", NULL};
	ke::AString str = lookupString(ip, path);
	const char *ccode = str.chars();

	for (size_t i = 0; i < SM_ARRAYSIZE(GeoIPCountryCode); i++)
	{
		if (!strncmp(ccode, GeoIPCountryCode[i], 2))
		{
			ccode = GeoIPCountryCode3[i];
			break;
		}
	}

	pCtx->StringToLocal(params[2], 4, ccode);

	return (strlen(ccode) != 0) ? 1 : 0;
}

static cell_t sm_Geoip_ContinentCode(IPluginContext *pCtx, const cell_t *params)
{
	char *ip;

	pCtx->LocalToString(params[1], &ip);
	StripPort(ip);

	const char *path[] = {"continent", "code", NULL};
	ke::AString str = lookupString(ip, path);
	const char *ccode = str.chars();

	pCtx->StringToLocal(params[2], 3, ccode);

	return (strlen(ccode) != 0) ? 1 : 0;
}

static cell_t sm_Geoip_RegionCode(IPluginContext *pCtx, const cell_t *params)
{
	char *ip;

	pCtx->LocalToString(params[1], &ip);
	StripPort(ip);

	const char *path[] = {"subdivisions", "0", "iso_code", NULL};
	ke::AString str = lookupString(ip, path);
	const char *ccode = str.chars();

	pCtx->StringToLocal(params[2], 4, ccode);

	return (strlen(ccode) != 0) ? 1 : 0;
}

static cell_t sm_Geoip_Timezone(IPluginContext *pCtx, const cell_t *params)
{
	char *ip;

	pCtx->LocalToString(params[1], &ip);
	StripPort(ip);

	const char *path[] = {"location", "time_zone", NULL};
	ke::AString str = lookupString(ip, path);
	const char *ccode = str.chars();

	pCtx->StringToLocal(params[2], params[3], ccode);

	return (strlen(ccode) != 0) ? 1 : 0;
}

static cell_t sm_Geoip_Country(IPluginContext *pCtx, const cell_t *params)
{
	char *ip;
	char *lang;

	pCtx->LocalToString(params[1], &ip);
	pCtx->LocalToString(params[4], &lang);
	StripPort(ip);

	if (strlen(lang) == 0) strcpy(lang, "en");

	const char *path[] = {"country", "names", lang, NULL};
	ke::AString str = lookupString(ip, path);
	const char *ccode = str.chars();

	pCtx->StringToLocal(params[2], params[3], ccode);

	return (strlen(ccode) != 0) ? 1 : 0;
}

static cell_t sm_Geoip_Continent(IPluginContext *pCtx, const cell_t *params)
{
	char *ip;
	char *lang;

	pCtx->LocalToString(params[1], &ip);
	pCtx->LocalToString(params[4], &lang);
	StripPort(ip);

	if (strlen(lang) == 0) strcpy(lang, "en");

	const char *path[] = {"continent", "names", lang, NULL};
	ke::AString str = lookupString(ip, path);
	const char *ccode = str.chars();

	pCtx->StringToLocal(params[2], params[3], ccode);

	return (strlen(ccode) != 0) ? 1 : 0;
}

static cell_t sm_Geoip_Region(IPluginContext *pCtx, const cell_t *params)
{
	char *ip;
	char *lang;

	pCtx->LocalToString(params[1], &ip);
	pCtx->LocalToString(params[4], &lang);
	StripPort(ip);

	if (strlen(lang) == 0) strcpy(lang, "en");

	const char *path[] = {"subdivisions", "0", "names", lang, NULL};
	ke::AString str = lookupString(ip, path);
	const char *ccode = str.chars();

	pCtx->StringToLocal(params[2], params[3], ccode);

	return (strlen(ccode) != 0) ? 1 : 0;
}

static cell_t sm_Geoip_City(IPluginContext *pCtx, const cell_t *params)
{
	char *ip;
	char *lang;

	pCtx->LocalToString(params[1], &ip);
	pCtx->LocalToString(params[4], &lang);
	StripPort(ip);

	if (strlen(lang) == 0) strcpy(lang, "en");

	const char *path[] = {"city", "names", lang, NULL};
	ke::AString str = lookupString(ip, path);
	const char *ccode = str.chars();

	pCtx->StringToLocal(params[2], params[3], ccode);

	return (strlen(ccode) != 0) ? 1 : 0;
}

const sp_nativeinfo_t geoip_natives[] = 
{
	{"GeoIP2_Code2",			sm_Geoip_Code2},
	{"GeoIP2_Code3",			sm_Geoip_Code3},
	{"GeoIP2_ContinentCode",	sm_Geoip_ContinentCode},
	{"GeoIP2_RegionCode",		sm_Geoip_RegionCode},
	{"GeoIP2_Timezone",		    sm_Geoip_Timezone},
	{"GeoIP2_Country",		    sm_Geoip_Country},
	{"GeoIP2_Continent",		sm_Geoip_Continent},
	{"GeoIP2_Region",			sm_Geoip_Region},
	{"GeoIP2_City",			    sm_Geoip_City},
	{NULL,					    NULL},
};

