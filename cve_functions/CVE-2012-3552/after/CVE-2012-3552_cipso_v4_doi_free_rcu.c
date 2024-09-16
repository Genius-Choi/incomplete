static void cipso_v4_doi_free_rcu(struct rcu_head *entry)
{
	struct cipso_v4_doi *doi_def;

	doi_def = container_of(entry, struct cipso_v4_doi, rcu);
	cipso_v4_doi_free(doi_def);
}
