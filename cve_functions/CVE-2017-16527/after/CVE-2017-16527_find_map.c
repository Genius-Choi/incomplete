find_map(struct mixer_build *state, int unitid, int control)
{
	const struct usbmix_name_map *p = state->map;

	if (!p)
		return NULL;

	for (p = state->map; p->id; p++) {
		if (p->id == unitid &&
		    (!control || !p->control || control == p->control))
			return p;
	}
	return NULL;
}
