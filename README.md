# GeoIP2
This is a rewritten geoip extension from the SourceMod distribution for the new database format from MaxMind `.mmdb`.
  
  
## Installation
1. Download latest release version and extra to game extension folder.
2. Download latest database GeoLite2-City.mmdb or [GeoLite2-Country.mmdb] and put to path `addons/sourcemod/configs/geoip/`
  
  
## Natives

``` sourcepawn
/**
 * @section IP addresses can contain ports, the ports will be stripped out.
 */

/**
 * Gets the two character country code from an IP address. (US, CA, etc)
 *
 * @param ip			Ip to determine the country code.
 * @param ccode			Destination string buffer to store the code.
 * @return				True on success, false if no country found.
 */
native bool GeoipCode2(const char[] ip, char ccode[3]);

/**
 * Gets the three character country code from an IP address. (USA, CAN, etc)
 *
 * @param ip			Ip to determine the country code.
 * @param ccode			Destination string buffer to store the code.
 * @return				True on success, false if no country found.
 */
native bool GeoipCode3(const char[] ip, char ccode[4]);

/**
 * Gets the two character continent code from an IP address. (EU, AS, etc)
 *
 * @param ip			Ip to determine the continent code.
 * @param ccode			Destination string buffer to store the code.
 * @return				True on success, false if no continent found.
 */
native bool GeoipContinentCode(const char[] ip, char ccode[3]);

/**
 * Gets the two/three region code from an IP address. (IL, CHE, etc)
 *
 * @param ip			Ip to determine the region code.
 * @param ccode			Destination string buffer to store the code.
 * @return				True on success, false if no region found.
 */
native bool GeoipRegionCode(const char[] ip, char ccode[4]);

/**
 * Gets the timezone. (max length of output string is 45)
 *
 * @param ip			Ip to determine the timezone.
 * @param name			Destination string buffer to store the timezone.
 * @param maxlength			Maximum length of output string buffer.
 * @return				True on success, false if no timezone found.
 */
native bool GeoipTimezone(const char[] ip, char[] name, int maxlength);

/**
 * Gets the full country name. (max length of output string is 45)
 *
 * @param ip			Ip to determine the country code.
 * @param name			Destination string buffer to store the country name.
 * @param maxlength			Maximum length of output string buffer.
 * @param lang			Which language to the output of result the geoip2 lookup.
 * @return				True on success, false if no country found.
 */
native bool GeoipCountry(const char[] ip, char[] name, int maxlength, const char[] lang = "en");

/**
 * Gets the full continent name. (max length of output string is 45)
 *
 * @param ip			Ip to determine the continent code.
 * @param name			Destination string buffer to store the continent name.
 * @param maxlength			Maximum length of output string buffer.
 * @param lang			Which language to the output of result the geoip2 lookup.
 * @return				True on success, false if no continent found.
 */
native bool GeoipContinent(const char[] ip, char[] name, int maxlength, const char[] lang = "en");

/**
 * Gets the full region name. (max length of output string is 45)
 *
 * @param ip			Ip to determine the region code.
 * @param name			Destination string buffer to store the region name.
 * @param maxlength			Maximum length of output string buffer.
 * @param lang			Which language to the output of result the geoip2 lookup.
 * @return				True on success, false if no region found.
 */
native bool GeoipRegion(const char[] ip, char[] name, int maxlength, const char[] lang = "en");

/**
 * Gets the city name. (max length of output string is 45)
 *
 * @param ip			Ip to determine the city code.
 * @param name			Destination string buffer to store the city name.
 * @param maxlength			Maximum length of output string buffer.
 * @param lang			Which language to the output of result the geoip2 lookup.
 * @return				True on success, false if no city found.
 */
native bool GeoipCity(const char[] ip, char[] name, int maxlength, const char[] lang = "en");
```
  
  
### Language
- English -> en
- Brazilian Portuguese -> pt-BR
- French -> fr
- German -> de
- Japanese -> ja
- Russian -> ru
- Simplified Chinese -> zh-CN
- Spanish -> es
  
  
### Credits:  
- Original GeoIP2 SDK: [MaxMind](https://maxmind.com "maxmind")  
- Original GeoIP  EXT: [Alliedmodders](https://github.com/alliedmodders/sourcemod "Alliedmodders")  
- Original GeoIP2 EXT: [Accelerator74](https://github.com/Accelerator74 "Accelerator74")  