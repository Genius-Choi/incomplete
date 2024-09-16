static int samldb_first_step(struct samldb_ctx *ac)
{
	if (ac->steps == NULL) {
		return ldb_operr(ldb_module_get_ctx(ac->module));
	}

	ac->curstep = ac->steps;
	return ac->curstep->fn(ac);
}
