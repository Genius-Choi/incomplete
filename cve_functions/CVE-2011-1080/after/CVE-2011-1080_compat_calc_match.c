static int compat_calc_match(struct ebt_entry_match *m, int *off)
{
	*off += ebt_compat_match_offset(m->u.match, m->match_size);
	*off += ebt_compat_entry_padsize();
	return 0;
}
