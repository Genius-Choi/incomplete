lookup_identity(struct sshkey *key, int version)
{
	Identity *id;

	Idtab *tab = idtab_lookup(version);
	TAILQ_FOREACH(id, &tab->idlist, next) {
		if (sshkey_equal(key, id->key))
			return (id);
	}
	return (NULL);
}
