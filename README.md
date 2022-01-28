# GeoIP2
This is a rewritten geoip extension from the SourceMod distribution for the new database format from MaxMind `.mmdb`.
Redux edition credits:
- Kxnrl
- laper32
  
## Installation
1. Download latest release version and extra to game extension folder.
2. Download latest database GeoLite2-City.mmdb or [GeoLite2-Country.mmdb] and put to path `addons/sourcemod/configs/geoip/`
  
## Build instruction
1. `git clone https://github.com/Kxnrl/sm-ext-GeoIP2.git` (HTTP) or `git clone git@github.com:Kxnrl/sm-ext-GeoIP2.git` (SSH)
2. `git submodule update --init --recursive`
3. `mkdir build; cd build;` (Bash/Powershell)
4. Configure: Different platform has different instructions.
    - Windows: `cmake -G "Visual Studio 17 2022" -A Win32 -DUSE_SDK=OFF -DSM_USE_VENDOR=OFF -DMMS_USE_VENDOR=OFF -DTARGET_ARCH=x86 -DBUILD_TESTING=OFF ../`
    - Linux: `cmake -DUSE_SDK=OFF -DSM_USE_VENDOR=OFF -DMMS_USE_VENDOR=OFF -DTARGET_ARCH=x86 -DBUILD_TESTING=OFF -DCMAKE_BUILD_TYPE=Release ../`
5. Build: Different platform has different instructions.
    - Windows: `cmake --build . --config Release`
    - Linux: `cmake --build . --config Release -j NumOfThreads` (NumOfThreads: How many thread you want to use to build)

N.B.: 
1. Instructions above requires you to predefine `SOURCEMOD` and `METAMOD_SOURCE` environment variables.
2. Indeed, you can still not using environment variables to build this extension, but requires you place sm and mm at the root of the project.
3. Noting that submodules are using SSH clone, make sure **YOU HAVE BEEN PRECONFIGURED SSH KEY!**

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
native bool GeoIP2_Code2(const char[] ip, char ccode[3]);

/**
 * Gets the three character country code from an IP address. (USA, CAN, etc)
 *
 * @param ip			Ip to determine the country code.
 * @param ccode			Destination string buffer to store the code.
 * @return				True on success, false if no country found.
 */
native bool GeoIP2_Code3(const char[] ip, char ccode[4]);

/**
 * Gets the two character continent code from an IP address. (EU, AS, etc)
 *
 * @param ip			Ip to determine the continent code.
 * @param ccode			Destination string buffer to store the code.
 * @return				True on success, false if no continent found.
 */
native bool GeoIP2_ContinentCode(const char[] ip, char ccode[3]);

/**
 * Gets the two/three region code from an IP address. (IL, CHE, etc)
 *
 * @param ip			Ip to determine the region code.
 * @param ccode			Destination string buffer to store the code.
 * @return				True on success, false if no region found.
 */
native bool GeoIP2_RegionCode(const char[] ip, char ccode[4]);

/**
 * Gets the timezone. (max length of output string is 45)
 *
 * @param ip			Ip to determine the timezone.
 * @param name			Destination string buffer to store the timezone.
 * @param maxlength			Maximum length of output string buffer.
 * @return				True on success, false if no timezone found.
 */
native bool GeoIP2_Timezone(const char[] ip, char[] name, int maxlength);

/**
 * Gets the full country name. (max length of output string is 45)
 *
 * @param ip			Ip to determine the country code.
 * @param name			Destination string buffer to store the country name.
 * @param maxlength			Maximum length of output string buffer.
 * @param lang			Which language to the output of result the geoip2 lookup.
 * @return				True on success, false if no country found.
 */
native bool GeoIP2_Country(const char[] ip, char[] name, int maxlength, const char[] lang = "en");

/**
 * Gets the full continent name. (max length of output string is 45)
 *
 * @param ip			Ip to determine the continent code.
 * @param name			Destination string buffer to store the continent name.
 * @param maxlength			Maximum length of output string buffer.
 * @param lang			Which language to the output of result the geoip2 lookup.
 * @return				True on success, false if no continent found.
 */
native bool GeoIP2_Continent(const char[] ip, char[] name, int maxlength, const char[] lang = "en");

/**
 * Gets the full region name. (max length of output string is 45)
 *
 * @param ip			Ip to determine the region code.
 * @param name			Destination string buffer to store the region name.
 * @param maxlength			Maximum length of output string buffer.
 * @param lang			Which language to the output of result the geoip2 lookup.
 * @return				True on success, false if no region found.
 */
native bool GeoIP2_Region(const char[] ip, char[] name, int maxlength, const char[] lang = "en");

/**
 * Gets the city name. (max length of output string is 45)
 *
 * @param ip			Ip to determine the city code.
 * @param name			Destination string buffer to store the city name.
 * @param maxlength			Maximum length of output string buffer.
 * @param lang			Which language to the output of result the geoip2 lookup.
 * @return				True on success, false if no city found.
 */
native bool GeoIP2_City(const char[] ip, char[] name, int maxlength, const char[] lang = "en");
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
