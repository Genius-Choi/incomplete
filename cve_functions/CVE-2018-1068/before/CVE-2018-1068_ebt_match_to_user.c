static inline int ebt_match_to_user(const struct ebt_entry_match *m,
				    const char *base, char __user *ubase)
{
	return ebt_obj_to_user(ubase + ((char *)m - base),
			       m->u.match->name, m->data, sizeof(*m),
			       m->u.match->usersize, m->match_size);
}
