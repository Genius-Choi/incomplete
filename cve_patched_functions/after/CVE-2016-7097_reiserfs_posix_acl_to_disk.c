static void *reiserfs_posix_acl_to_disk(const struct posix_acl *acl, size_t * size)
{
	reiserfs_acl_header *ext_acl;
	char *e;
	int n;

	*size = reiserfs_acl_size(acl->a_count);
	ext_acl = kmalloc(sizeof(reiserfs_acl_header) +
						  acl->a_count *
						  sizeof(reiserfs_acl_entry),
						  GFP_NOFS);
	if (!ext_acl)
		return ERR_PTR(-ENOMEM);
	ext_acl->a_version = cpu_to_le32(REISERFS_ACL_VERSION);
	e = (char *)ext_acl + sizeof(reiserfs_acl_header);
	for (n = 0; n < acl->a_count; n++) {
		const struct posix_acl_entry *acl_e = &acl->a_entries[n];
		reiserfs_acl_entry *entry = (reiserfs_acl_entry *) e;
		entry->e_tag = cpu_to_le16(acl->a_entries[n].e_tag);
		entry->e_perm = cpu_to_le16(acl->a_entries[n].e_perm);
		switch (acl->a_entries[n].e_tag) {
		case ACL_USER:
			entry->e_id = cpu_to_le32(
				from_kuid(&init_user_ns, acl_e->e_uid));
			e += sizeof(reiserfs_acl_entry);
			break;
		case ACL_GROUP:
			entry->e_id = cpu_to_le32(
				from_kgid(&init_user_ns, acl_e->e_gid));
			e += sizeof(reiserfs_acl_entry);
			break;

		case ACL_USER_OBJ:
		case ACL_GROUP_OBJ:
		case ACL_MASK:
		case ACL_OTHER:
			e += sizeof(reiserfs_acl_entry_short);
			break;

		default:
			goto fail;
		}
	}
	return (char *)ext_acl;

fail:
	kfree(ext_acl);
	return ERR_PTR(-EINVAL);
}
