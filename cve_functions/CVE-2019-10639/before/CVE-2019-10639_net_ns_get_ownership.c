void net_ns_get_ownership(const struct net *net, kuid_t *uid, kgid_t *gid)
{
	if (net) {
		kuid_t ns_root_uid = make_kuid(net->user_ns, 0);
		kgid_t ns_root_gid = make_kgid(net->user_ns, 0);

		if (uid_valid(ns_root_uid))
			*uid = ns_root_uid;

		if (gid_valid(ns_root_gid))
			*gid = ns_root_gid;
	} else {
		*uid = GLOBAL_ROOT_UID;
		*gid = GLOBAL_ROOT_GID;
	}
}
