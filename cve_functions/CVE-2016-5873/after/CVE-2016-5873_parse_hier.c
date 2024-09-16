static const char *parse_hier(struct parse_state *state)
{
	if (*state->ptr == '/') {
		if (state->end - state->ptr > 1) {
			if (*(state->ptr + 1) == '/') {
				state->ptr += 2;
				if (!(state->ptr = parse_authority(state))) {
					return NULL;
				}
			}
		}
	}
	return parse_path(state);
}
