ApplyInterpsToKey(struct xkb_keymap *keymap, struct xkb_key *key)
{
    xkb_mod_mask_t vmodmap = 0;
    xkb_layout_index_t group;
    xkb_level_index_t level;

    /* If we've been told not to bind interps to this key, then don't. */
    if (key->explicit & EXPLICIT_INTERP)
        return true;

    for (group = 0; group < key->num_groups; group++) {
        for (level = 0; level < XkbKeyNumLevels(key, group); level++) {
            const struct xkb_sym_interpret *interp;

            interp = FindInterpForKey(keymap, key, group, level);
            if (!interp)
                continue;

            /* Infer default key behaviours from the base level. */
            if (group == 0 && level == 0)
                if (!(key->explicit & EXPLICIT_REPEAT) && interp->repeat)
                    key->repeats = true;

            if ((group == 0 && level == 0) || !interp->level_one_only)
                if (interp->virtual_mod != XKB_MOD_INVALID)
                    vmodmap |= (1u << interp->virtual_mod);

            if (interp->action.type != ACTION_TYPE_NONE)
                key->groups[group].levels[level].action = interp->action;
        }
    }

    if (!(key->explicit & EXPLICIT_VMODMAP))
        key->vmodmap = vmodmap;

    return true;
}
