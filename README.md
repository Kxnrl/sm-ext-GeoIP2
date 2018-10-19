# GeoIP2
This is a rewritten geoip extension from the SourceMod distribution for the new database format from MaxMind `.mmdb`.

## Installation
1. Download latest release version.
2. Extract all files from the archive with replacement to your game server.
3. Download last database [GeoLite2-City.mmdb](http://geolite.maxmind.com/download/geoip/database/GeoLite2-City.mmdb.gz) or [GeoLite2-Country.mmdb](http://geolite.maxmind.com/download/geoip/database/GeoLite2-Country.mmdb.gz) and put to path `addons/sourcemod/configs/geoip/`
4. Recompile all plugins that use `geoip.inc`.

## Natives

```javascript
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
