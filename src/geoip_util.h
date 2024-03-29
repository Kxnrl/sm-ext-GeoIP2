#ifndef _INCLUDE_SOURCEMOD_GEOIPUTIL_H_
#define _INCLUDE_SOURCEMOD_GEOIPUTIL_H_

// Why this guy spilt implementation and declaration?

#include <string>

#include "extension.h"

const char GeoIPCountryCode[252][3] =
{
	"AP", "EU", "AD", "AE", "AF", "AG", "AI", "AL", "AM", "AN",
	"AO", "AQ", "AR", "AS", "AT", "AU", "AW", "AZ", "BA", "BB",
	"BD", "BE", "BF", "BG", "BH", "BI", "BJ", "BM", "BN", "BO",
	"BR", "BS", "BT", "BV", "BW", "BY", "BZ", "CA", "CC", "CD",
	"CF", "CG", "CH", "CI", "CK", "CL", "CM", "CN", "CO", "CR",
	"CU", "CV", "CX", "CY", "CZ", "DE", "DJ", "DK", "DM", "DO",
	"DZ", "EC", "EE", "EG", "EH", "ER", "ES", "ET", "FI", "FJ",
	"FK", "FM", "FO", "FR", "FX", "GA", "GB", "GD", "GE", "GF",
	"GH", "GI", "GL", "GM", "GN", "GP", "GQ", "GR", "GS", "GT",
	"GU", "GW", "GY", "HK", "HM", "HN", "HR", "HT", "HU", "ID",
	"IE", "IL", "IN", "IO", "IQ", "IR", "IS", "IT", "JM", "JO",
	"JP", "KE", "KG", "KH", "KI", "KM", "KN", "KP", "KR", "KW",
	"KY", "KZ", "LA", "LB", "LC", "LI", "LK", "LR", "LS", "LT",
	"LU", "LV", "LY", "MA", "MC", "MD", "MG", "MH", "MK", "ML",
	"MM", "MN", "MO", "MP", "MQ", "MR", "MS", "MT", "MU", "MV",
	"MW", "MX", "MY", "MZ", "NA", "NC", "NE", "NF", "NG", "NI",
	"NL", "NO", "NP", "NR", "NU", "NZ", "OM", "PA", "PE", "PF",
	"PG", "PH", "PK", "PL", "PM", "PN", "PR", "PS", "PT", "PW",
	"PY", "QA", "RE", "RO", "RU", "RW", "SA", "SB", "SC", "SD",
	"SE", "SG", "SH", "SI", "SJ", "SK", "SL", "SM", "SN", "SO",
	"SR", "ST", "SV", "SY", "SZ", "TC", "TD", "TF", "TG", "TH",
	"TJ", "TK", "TM", "TN", "TO", "TL", "TR", "TT", "TV", "TW",
	"TZ", "UA", "UG", "UM", "US", "UY", "UZ", "VA", "VC", "VE",
	"VG", "VI", "VN", "VU", "WF", "WS", "YE", "YT", "RS", "ZA",
	"ZM", "ME", "ZW", "A1", "A2", "O1", "AX", "GG", "IM", "JE",
	"BL", "MF"
};

const char GeoIPCountryCode3[252][4] =
{
	"AP", "EU", "AND", "ARE", "AFG", "ATG", "AIA", "ALB", "ARM", "ANT",
	"AGO", "AQ", "ARG", "ASM", "AUT", "AUS", "ABW", "AZE", "BIH", "BRB",
	"BGD", "BEL", "BFA", "BGR", "BHR", "BDI", "BEN", "BMU", "BRN", "BOL",
	"BRA", "BHS", "BTN", "BV", "BWA", "BLR", "BLZ", "CAN", "CC", "COD",
	"CAF", "COG", "CHE", "CIV", "COK", "CHL", "CMR", "CHN", "COL", "CRI",
	"CUB", "CPV", "CX", "CYP", "CZE", "DEU", "DJI", "DNK", "DMA", "DOM",
	"DZA", "ECU", "EST", "EGY", "ESH", "ERI", "ESP", "ETH", "FIN", "FJI",
	"FLK", "FSM", "FRO", "FRA", "FX", "GAB", "GBR", "GRD", "GEO", "GUF",
	"GHA", "GIB", "GRL", "GMB", "GIN", "GLP", "GNQ", "GRC", "GS", "GTM",
	"GUM", "GNB", "GUY", "HKG", "HM", "HND", "HRV", "HTI", "HUN", "IDN",
	"IRL", "ISR", "IND", "IO", "IRQ", "IRN", "ISL", "ITA", "JAM", "JOR",
	"JPN", "KEN", "KGZ", "KHM", "KIR", "COM", "KNA", "PRK", "KOR", "KWT",
	"CYM", "KAZ", "LAO", "LBN", "LCA", "LIE", "LKA", "LBR", "LSO", "LTU",
	"LUX", "LVA", "LBY", "MAR", "MCO", "MDA", "MDG", "MHL", "MKD", "MLI",
	"MMR", "MNG", "MAC", "MNP", "MTQ", "MRT", "MSR", "MLT", "MUS", "MDV",
	"MWI", "MEX", "MYS", "MOZ", "NAM", "NCL", "NER", "NFK", "NGA", "NIC",
	"NLD", "NOR", "NPL", "NRU", "NIU", "NZL", "OMN", "PAN", "PER", "PYF",
	"PNG", "PHL", "PAK", "POL", "SPM", "PCN", "PRI", "PSE", "PRT", "PLW",
	"PRY", "QAT", "REU", "ROU", "RUS", "RWA", "SAU", "SLB", "SYC", "SDN",
	"SWE", "SGP", "SHN", "SVN", "SJM", "SVK", "SLE", "SMR", "SEN", "SOM",
	"SUR", "STP", "SLV", "SYR", "SWZ", "TCA", "TCD", "TF", "TGO", "THA",
	"TJK", "TKL", "TKM", "TUN", "TON", "TLS", "TUR", "TTO", "TUV", "TWN",
	"TZA", "UKR", "UGA", "UM", "USA", "URY", "UZB", "VAT", "VCT", "VEN",
	"VGB", "VIR", "VNM", "VUT", "WLF", "WSM", "YEM", "YT", "SRB", "ZAF",
	"ZMB", "MNE", "ZWE", "A1", "A2", "O1", "ALA", "GGY", "IMN", "JEY",
	"BLM", "MAF"
};

inline bool lookupByIp(const char* ip, const char** path, MMDB_entry_data_s* result)
{
	int gai_error = 0, mmdb_error = 0;
	MMDB_lookup_result_s lookup = MMDB_lookup_string(&mmdb, ip, &gai_error, &mmdb_error);

	if (gai_error != 0 || mmdb_error != MMDB_SUCCESS || !lookup.found_entry)
	{
		return false;
	}

	MMDB_entry_data_s entry_data;
	MMDB_aget_value(&lookup.entry, &entry_data, path);

	if (!entry_data.has_data)
	{
		return false;
	}

	*result = entry_data;

	return true;
}

inline std::string lookupString(const char* ip, const char** path)
{
	MMDB_entry_data_s result;

	if (!lookupByIp(ip, path, &result))
	{
		return std::string("");
	}

	return std::string(result.utf8_string, result.data_size);
}

#endif // _INCLUDE_SOURCEMOD_GEOIPUTIL_H_
