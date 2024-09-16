MergeIncludedCompatMaps(CompatInfo *into, CompatInfo *from,
                        enum merge_mode merge)
{
    if (from->errorCount > 0) {
        into->errorCount += from->errorCount;
        return;
    }

    into->mods = from->mods;

    if (into->name == NULL) {
        into->name = from->name;
        from->name = NULL;
    }

    if (darray_empty(into->interps)) {
        into->interps = from->interps;
        darray_init(from->interps);
    }
    else {
        SymInterpInfo *si;
        darray_foreach(si, from->interps) {
            si->merge = (merge == MERGE_DEFAULT ? si->merge : merge);
            if (!AddInterp(into, si, false))
                into->errorCount++;
        }
    }

    if (into->num_leds == 0) {
        memcpy(into->leds, from->leds, sizeof(*from->leds) * from->num_leds);
        into->num_leds = from->num_leds;
        from->num_leds = 0;
    }
    else {
        for (xkb_led_index_t i = 0; i < from->num_leds; i++) {
            LedInfo *ledi = &from->leds[i];
            ledi->merge = (merge == MERGE_DEFAULT ? ledi->merge : merge);
            if (!AddLedMap(into, ledi, false))
                into->errorCount++;
        }
    }
}
