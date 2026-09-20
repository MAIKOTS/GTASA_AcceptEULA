#ifndef ACCEPT_EULA_AMLMOD_H
#define ACCEPT_EULA_AMLMOD_H

#include <cstdint>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cctype>

#include "interface.h"

#if defined(__arm__) || defined(_WIN32)
    #define AML32
#elif defined(__aarch64__) || defined(_WIN64)
    #define AML64
#else
    #error This mod supports ARM architectures only.
#endif

struct ModVersion
{
    unsigned short major;
    unsigned short minor;
    unsigned short revision;
    unsigned short build;
};

inline char* strxcpy(char* dst, const char* src, int len)
{
    if (!len)
        return nullptr;

    while (--len && (*dst++ = *src++))
        ;

    if (!len)
    {
        *dst++ = '\0';
        return (*src ? nullptr : dst);
    }

    return dst;
}

class ModInfo
{
public:
    ModInfo(
        const char* guid,
        const char* name,
        const char* versionString,
        const char* author)
    {
        strxcpy(szGUID, guid, sizeof(szGUID));
        szGUID[sizeof(szGUID) - 1] = '\0';

        strxcpy(szName, name, sizeof(szName));
        szName[sizeof(szName) - 1] = '\0';

        strxcpy(szVersion, versionString, sizeof(szVersion));
        szVersion[sizeof(szVersion) - 1] = '\0';

        strxcpy(szAuthor, author, sizeof(szAuthor));
        szAuthor[sizeof(szAuthor) - 1] = '\0';

        version = {0, 0, 0, 0};

        for (int i = 0; szGUID[i] != '\0'; ++i)
            szGUID[i] = static_cast<char>(
                std::tolower(static_cast<unsigned char>(szGUID[i]))
            );

        if (std::sscanf(
                szVersion,
                "%hu.%hu.%hu.%hu",
                &version.major,
                &version.minor,
                &version.revision,
                &version.build) < 4)
        {
            if (std::sscanf(
                    szVersion,
                    "%hu.%hu.%hu",
                    &version.major,
                    &version.minor,
                    &version.revision) < 3)
            {
                if (std::sscanf(
                        szVersion,
                        "%hu.%hu",
                        &version.major,
                        &version.minor) < 2)
                {
                    version.major = static_cast<unsigned short>(
                        std::atoi(szVersion)
                    );
                }

                version.revision = 0;
            }

            version.build = 0;
        }
    }

private:
    char szGUID[48];
    char szName[48];
    char szVersion[24];
    char szAuthor[48];
    ModVersion version;
};

extern ModInfo* modinfo;
extern IAML* aml;

#define MYMOD(_guid, _name, _version, _author)                         \
    static ModInfo modinfoLocal(#_guid, #_name, #_version, #_author);  \
    ModInfo* modinfo = &modinfoLocal;                                  \
    extern "C" JNIEXPORT ModInfo* __GetModInfo()                      \
    {                                                                  \
        return modinfo;                                                \
    }                                                                  \
    IAML* aml = nullptr;                                                \
    struct AMLInitStub                                                   \
    {                                                                  \
        AMLInitStub()                                                    \
        {                                                                \
            aml = static_cast<IAML*>(GetInterface("AMLInterface"));     \
        }                                                                \
    };                                                                   \
    static AMLInitStub amlStub;

#define NEEDGAME(_pkg_name)                                             \
    extern "C" JNIEXPORT const char* __INeedASpecificGame()            \
    {                                                                   \
        return #_pkg_name;                                               \
    }

#endifbool is_pow2(int x) // if its 1,2,4,8, ... , 256, 512, ...
{
    return ( (x > 0) && ((x & (x - 1)) == 0) );
}
inline unsigned int next_pow2(unsigned int x)
{
    if (x == 0) return 1;
    --x;
    x |= x >> 1;
    x |= x >> 2;
    x |= x >> 4;
    x |= x >> 8;
    x |= x >> 16;
    return ++x;
}
inline int bitcount(unsigned int x)
{
    int count = 0;
    while(x)
    {
        x &= (x - 1);
        ++count;
    }
    return count;
}
inline unsigned int rotl(unsigned int value, unsigned int shift)
{
    const unsigned int mask = (8 * sizeof(value)) - 1;
    shift &= mask;
    return (value << shift) | (value >> ((-shift) & mask));
}
inline unsigned int rotr(unsigned int value, unsigned int shift)
{
    const unsigned int mask = (8 * sizeof(value)) - 1;
    shift &= mask;
    return (value >> shift) | (value << ((-shift) & mask));
}
inline bool evenvalue(int v)
{
    return ((v & 0x1) == 0);
}
inline bool oddvalue(int v)
{
    return !evenvalue(v);
}
inline float roundsnap(float val, float step_val)
{
    if(step_val == 0.0) return val;
    return floorf((val / step_val) + 0.5) * step_val;
}
inline float ceilsnap(float val, float step_val)
{
    if(step_val == 0.0f) return val;
    return ceilf(val / step_val) * step_val;
}
inline float floorsnap(float val, float step_val)
{
    if(step_val == 0.0f) return val;
    return floorf(val / step_val) * step_val;
}



#define ARRAY_SIZE(__aVar)  ((size_t)( sizeof(__aVar) / sizeof(__aVar[0]) ))
#define RAD_TO_DEG(__f) ( (__f) * (180.0f / M_PI) )
#define DEG_TO_RAD(__f) ( (__f) * (M_PI / 180.0f) )

class ModInfo
{
public:
    ModInfo(const char* szGUID, const char* szName, const char* szVersion, const char* szAuthor)
    {
        /* No buffer overflow! */
        strxcpy(this->szGUID, szGUID, sizeof(ModInfo::szGUID)); this->szGUID[sizeof(ModInfo::szGUID) - 1] = '\0';
        strxcpy(this->szName, szName, sizeof(ModInfo::szName)); this->szName[sizeof(ModInfo::szName) - 1] = '\0';
        strxcpy(this->szVersion, szVersion, sizeof(ModInfo::szVersion)); this->szVersion[sizeof(ModInfo::szVersion) - 1] = '\0';
        strxcpy(this->szAuthor, szAuthor, sizeof(ModInfo::szAuthor)); this->szAuthor[sizeof(ModInfo::szAuthor) - 1] = '\0';

        version.major = 0;
        version.minor = 0;
        version.revision = 0;
        version.build = 0;

        /* GUID should be lowcase */
        for(int i = 0; this->szGUID[i] != '\0'; ++i)
        {
            this->szGUID[i] = (char)tolower((unsigned char)this->szGUID[i]);
        }

        /* Parse version string */
        if(sscanf(this->szVersion, "%hu.%hu.%hu.%hu", &version.major, &version.minor, &version.revision, &version.build) < 4)
        {
            if(sscanf(this->szVersion, "%hu.%hu.%hu", &version.major, &version.minor, &version.revision) < 3)
            {
                if(sscanf(this->szVersion, "%hu.%hu", &version.major, &version.minor) < 2)
                {
                    version.major = (unsigned short)atoi(this->szVersion);
                }
                version.revision = 0;
            }
            version.build = 0;
        }
    }
    inline const char* GUID() { return szGUID; }
    inline const char* Name() { return szName; }
    inline const char* VersionString() { return szVersion; }
    inline const char* Author() { return szAuthor; }
    inline unsigned short Major() { return version.major; }
    inline unsigned short Minor() { return version.minor; }
    inline unsigned short Revision() { return version.revision; }
    inline unsigned short Build() { return version.build; }

private:
    char szGUID[48];
    char szName[48];
    char szVersion[24];
    char szAuthor[48];
    ModVersion version;

    friend class ModsList;
    friend struct Mods;
};

typedef ModInfo* (*GetModInfoFn)();
extern ModInfo* modinfo;


#include "iaml.h"

#endif // _AMLMOD
