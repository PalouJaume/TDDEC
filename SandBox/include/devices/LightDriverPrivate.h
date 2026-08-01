#ifndef D_LightDriverPrivate_H
#define D_LightDriverPrivate_H

typedef struct LightDriverStruct
{
    LightDriverInterface vtable;
    const char *type;
    int id;
} LightDriverStruct;

typedef struct LightDriverInterfaceStruct
{
    void (*TurnOn)(LightDriver);
    void (*TurnOff)(LightDriver);
    void (*Destroy)(LightDriver);
} LightDriverInterfaceStruct;

#endif /* D_LightDriverPrivate_H */