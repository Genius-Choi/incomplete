pace_gt(struct posix_acl_entry *pace1, struct posix_acl_entry *pace2)
{
	if (pace1->e_tag != pace2->e_tag)
		return pace1->e_tag > pace2->e_tag;
	if (pace1->e_tag == ACL_USER)
		return uid_gt(pace1->e_uid, pace2->e_uid);
	if (pace1->e_tag == ACL_GROUP)
		return gid_gt(pace1->e_gid, pace2->e_gid);
	return false;
}
