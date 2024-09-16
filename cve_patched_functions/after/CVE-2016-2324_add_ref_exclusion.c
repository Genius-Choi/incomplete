void add_ref_exclusion(struct string_list **ref_excludes_p, const char *exclude)
{
	if (!*ref_excludes_p) {
		*ref_excludes_p = xcalloc(1, sizeof(**ref_excludes_p));
		(*ref_excludes_p)->strdup_strings = 1;
	}
	string_list_append(*ref_excludes_p, exclude);
}
