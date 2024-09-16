archive_acl_add_entry_len_l(struct archive_acl *acl,
    int type, int permset, int tag, int id, const char *name, size_t len,
    struct archive_string_conv *sc)
{
	struct archive_acl_entry *ap;
	int r;

	if (acl_special(acl, type, permset, tag) == 0)
		return ARCHIVE_OK;
	ap = acl_new_entry(acl, type, permset, tag, id);
	if (ap == NULL) {
		/* XXX Error XXX */
		return ARCHIVE_FAILED;
	}
	if (name != NULL  &&  *name != '\0' && len > 0) {
		r = archive_mstring_copy_mbs_len_l(&ap->name, name, len, sc);
	} else {
		r = 0;
		archive_mstring_clean(&ap->name);
	}
	if (r == 0)
		return (ARCHIVE_OK);
	else if (errno == ENOMEM)
		return (ARCHIVE_FATAL);
	else
		return (ARCHIVE_WARN);
}
