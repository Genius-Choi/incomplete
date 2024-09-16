static int target_revfn(u8 af, const char *name, u8 revision, int *bestp)
{
	const struct xt_target *t;
	int have_rev = 0;

	list_for_each_entry(t, &xt[af].target, list) {
		if (strcmp(t->name, name) == 0) {
			if (t->revision > *bestp)
				*bestp = t->revision;
			if (t->revision == revision)
				have_rev = 1;
		}
	}

	if (af != NFPROTO_UNSPEC && !have_rev)
		return target_revfn(NFPROTO_UNSPEC, name, revision, bestp);

	return have_rev;
}
