static int find_uid(struct posix_acl_state *state, kuid_t uid)
{
	struct posix_ace_state_array *a = state->users;
	int i;

	for (i = 0; i < a->n; i++)
		if (uid_eq(a->aces[i].uid, uid))
			return i;
	/* Not found: */
	a->n++;
	a->aces[i].uid = uid;
	a->aces[i].perms.allow = state->everyone.allow;
	a->aces[i].perms.deny  = state->everyone.deny;

	return i;
}
