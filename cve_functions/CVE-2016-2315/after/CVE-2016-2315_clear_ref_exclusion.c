void clear_ref_exclusion(struct string_list **ref_excludes_p)
{
	if (*ref_excludes_p) {
		string_list_clear(*ref_excludes_p, 0);
		free(*ref_excludes_p);
	}
	*ref_excludes_p = NULL;
}
