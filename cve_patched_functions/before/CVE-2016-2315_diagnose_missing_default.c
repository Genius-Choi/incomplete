static void NORETURN diagnose_missing_default(const char *def)
{
	unsigned char sha1[20];
	int flags;
	const char *refname;

	refname = resolve_ref_unsafe(def, 0, sha1, &flags);
	if (!refname || !(flags & REF_ISSYMREF) || (flags & REF_ISBROKEN))
		die(_("your current branch appears to be broken"));

	skip_prefix(refname, "refs/heads/", &refname);
	die(_("your current branch '%s' does not have any commits yet"),
	    refname);
}
