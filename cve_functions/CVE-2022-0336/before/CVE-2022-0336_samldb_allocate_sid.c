static int samldb_allocate_sid(struct samldb_ctx *ac)
{
	uint32_t rid;
	struct dom_sid *sid;
	struct ldb_context *ldb = ldb_module_get_ctx(ac->module);
	int ret;

	ret = ridalloc_allocate_rid(ac->module, &rid, ac->req);
	if (ret != LDB_SUCCESS) {
		return ret;
	}

	sid = dom_sid_add_rid(ac, samdb_domain_sid(ldb), rid);
	if (sid == NULL) {
		return ldb_module_oom(ac->module);
	}

	if ( ! samldb_msg_add_sid(ac->msg, "objectSid", sid)) {
		return ldb_operr(ldb);
	}

	return samldb_next_step(ac);
}
