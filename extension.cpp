#include "extension.h"
#include "maxminddb.h"
#include "am-string.h"

/**
 * @file extension.cpp
 * @brief Implement extension code here.
 */
GeoIP_Extension g_GeoIP;
MMDB_s mmdb;

SMEXT_LINK(&g_GeoIP);

bool GeoIP_Extension::SDK_OnLoad(char *error, size_t maxlength, bool late)
{
	char path[PLATFORM_MAX_PATH];
	int status;

	g_pSM->BuildPath(Path_SM, path, sizeof(path), "configs/geoip/GeoLite2-City.mmdb");

	status = MMDB_open(path, MMDB_MODE_MMAP, &mmdb);

	if (MMDB_SUCCESS != status) {
		g_pSM->BuildPath(Path_SM, path, sizeof(path), "configs/geoip/GeoLite2-Country.mmdb");
	}

	status = MMDB_open(path, MMDB_MODE_MMAP, &mmdb);

	if (MMDB_SUCCESS != status) {
        	ke::SafeStrcpy(error, maxlength, "Could not load configs/geoip/[GeoLite2-City|GeoLite2-Country].mmdb");
		return false;
	}

	g_pShareSys->AddNatives(myself, geoip_natives);
	g_pShareSys->RegisterLibrary(myself, "GeoIP2");

	char date[40];
	const time_t epoch = (const time_t)mmdb.metadata.build_epoch;
	strftime(date, 40, "%F %T UTC", gmtime(&epoch));

	g_pSM->LogMessage(myself, "GeoIP2 database loaded: %s (%s)", mmdb.metadata.database_type, date);

	char buf[64];
	for (size_t i = 0; i < mmdb.metadata.languages.count; i++) {
		if (i == 0) {
			strcpy(buf, mmdb.metadata.languages.names[i]);
		}
		else {
			strcat(buf, " ");
			strcat(buf, mmdb.metadata.languages.names[i]);
		}
	}
	g_pSM->LogMessage(myself, "GeoIP2 supported languages: %s", buf);

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
	const char *ccode;

	pCtx->LocalToString(params[1], &ip);
	StripPort(ip);

	int gai_error, mmdb_error;
	MMDB_lookup_result_s result = MMDB_lookup_string(&mmdb, ip, &gai_error, &mmdb_error);

	if (0 != gai_error) {
		return 0;
	}

	if (MMDB_SUCCESS != mmdb_error) {
		return 0;
	}

	if (!result.found_entry) {
		return 0;
	}

	MMDB_entry_data_s entry_data;
	int res = MMDB_get_value(&result.entry, &entry_data, "country", "iso_code", NULL);

	if (MMDB_SUCCESS != res) {
		return 0;
	}

	if (!entry_data.has_data || MMDB_DATA_TYPE_UTF8_STRING != entry_data.type) {
		return 0;
	}

	ke::AString l(entry_data.utf8_string, entry_data.data_size);
	ccode = l.chars();

	pCtx->StringToLocal(params[2], 3, (ccode) ? ccode : "");

	return ccode ? 1 : 0;
}

static cell_t sm_Geoip_Code3(IPluginContext *pCtx, const cell_t *params)
{
	char *ip;
	const char *ccode;

	pCtx->LocalToString(params[1], &ip);
	StripPort(ip);

	int gai_error, mmdb_error;
	MMDB_lookup_result_s result = MMDB_lookup_string(&mmdb, ip, &gai_error, &mmdb_error);

	if (0 != gai_error) {
		return 0;
	}

	if (MMDB_SUCCESS != mmdb_error) {
		return 0;
	}

	if (!result.found_entry) {
		return 0;
	}

	MMDB_entry_data_s entry_data;
	int res = MMDB_get_value(&result.entry, &entry_data, "country", "iso_code", NULL);

	if (MMDB_SUCCESS != res) {
		return 0;
	}

	if (!entry_data.has_data || MMDB_DATA_TYPE_UTF8_STRING != entry_data.type) {
		return 0;
	}

	ke::AString l(entry_data.utf8_string, entry_data.data_size);
	ccode = l.chars();

	if (!ccode) {
		return 0;
	}

	int ccode3 = 0;
	for (size_t i = 0; i < sizeof(GeoIP_country_code); i++)
	{
		if (strcmp(ccode, GeoIP_country_code[i]) == 0)
			ccode3 = i;
	}

	pCtx->StringToLocal(params[2], 4, (ccode3) ? GeoIP_country_code3[ccode3] : "");

	return ccode3 ? 1 : 0;
}

static cell_t sm_Geoip_Country(IPluginContext *pCtx, const cell_t *params)
{
	char *ip;
	char *lang;
	const char *ccode;

	pCtx->LocalToString(params[1], &ip);
	pCtx->LocalToString(params[4], &lang);
	StripPort(ip);

	int gai_error, mmdb_error;
	MMDB_lookup_result_s result = MMDB_lookup_string(&mmdb, ip, &gai_error, &mmdb_error);

	if (0 != gai_error) {
		return 0;
	}

	if (MMDB_SUCCESS != mmdb_error) {
		return 0;
	}

	if (!result.found_entry) {
		return 0;
	}

	if (strlen(lang) == 0) strcpy(lang, "en");

	MMDB_entry_data_s entry_data;
	int res = MMDB_get_value(&result.entry, &entry_data, "country", "names", lang, NULL);

	if (MMDB_SUCCESS != res) {
		return 0;
	}

	if (!entry_data.has_data || MMDB_DATA_TYPE_UTF8_STRING != entry_data.type) {
		return 0;
	}

	ke::AString l(entry_data.utf8_string, entry_data.data_size);
	ccode = l.chars();

	pCtx->StringToLocal(params[2], params[3], (ccode) ? ccode : "");

	return ccode ? 1 : 0;
}

static cell_t sm_Geoip_City(IPluginContext *pCtx, const cell_t *params)
{
	char *ip;
	char *lang;
	const char *ccode;

	pCtx->LocalToString(params[1], &ip);
	pCtx->LocalToString(params[4], &lang);
	StripPort(ip);

	int gai_error, mmdb_error;
	MMDB_lookup_result_s result = MMDB_lookup_string(&mmdb, ip, &gai_error, &mmdb_error);

	if (0 != gai_error) {
		return 0;
	}

	if (MMDB_SUCCESS != mmdb_error) {
		return 0;
	}

	if (!result.found_entry) {
		return 0;
	}

	if (strlen(lang) == 0) strcpy(lang, "en");

	MMDB_entry_data_s entry_data;
	int res = MMDB_get_value(&result.entry, &entry_data, "city", "names", lang, NULL);

	if (MMDB_SUCCESS != res) {
		return 0;
	}

	if (!entry_data.has_data || MMDB_DATA_TYPE_UTF8_STRING != entry_data.type) {
		return 0;
	}

	ke::AString l(entry_data.utf8_string, entry_data.data_size);
	ccode = l.chars();

	pCtx->StringToLocal(params[2], params[3], (ccode) ? ccode : "");

	return ccode ? 1 : 0;
}

const sp_nativeinfo_t geoip_natives[] = 
{
	{"GeoipCode2",			sm_Geoip_Code2},
	{"GeoipCode3",			sm_Geoip_Code3},
	{"GeoipCountry",		sm_Geoip_Country},
	{"GeoipCity",			sm_Geoip_City},
	{NULL,					NULL},
};

