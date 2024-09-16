static int rtecp_create_file(sc_card_t *card, sc_file_t *file)
{
	int r;

	assert(card && card->ctx && file);
	if (file->sec_attr_len == 0)
	{
		r = set_sec_attr_from_acl(card, file);
		SC_TEST_RET(card->ctx, SC_LOG_DEBUG_NORMAL, r, "Set sec_attr from ACL failed");
	}
	assert(iso_ops && iso_ops->create_file);
	r = iso_ops->create_file(card, file);
	SC_FUNC_RETURN(card->ctx, SC_LOG_DEBUG_VERBOSE, r);
}
