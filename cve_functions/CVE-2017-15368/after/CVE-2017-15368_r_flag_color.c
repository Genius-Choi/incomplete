R_API const char *r_flag_color(RFlag *f, RFlagItem *it, const char *color) {
	if (!f || !it) return NULL;
	if (!color) return it->color;
	free (it->color);
	it->color = *color ? strdup (color) : NULL;
	return it->color;
}
