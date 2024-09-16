resolve_modifier(const char *name)
{
    static const struct {
        const char *name;
        xkb_mod_index_t mod;
    } mods[] = {
        { "Shift", 0 },
        { "Ctrl", 2 },
        { "Alt", 3 },
        { "Meta", 3 },
        { "Lock", 1 },
        { "Caps", 1 },
    };

    for (unsigned i = 0; i < ARRAY_SIZE(mods); i++)
        if (streq(name, mods[i].name))
            return mods[i].mod;

    return XKB_MOD_INVALID;
}
