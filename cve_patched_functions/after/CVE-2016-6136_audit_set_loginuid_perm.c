static int audit_set_loginuid_perm(kuid_t loginuid)
{
	/* if we are unset, we don't need privs */
	if (!audit_loginuid_set(current))
		return 0;
	/* if AUDIT_FEATURE_LOGINUID_IMMUTABLE means never ever allow a change*/
	if (is_audit_feature_set(AUDIT_FEATURE_LOGINUID_IMMUTABLE))
		return -EPERM;
	/* it is set, you need permission */
	if (!capable(CAP_AUDIT_CONTROL))
		return -EPERM;
	/* reject if this is not an unset and we don't allow that */
	if (is_audit_feature_set(AUDIT_FEATURE_ONLY_UNSET_LOGINUID) && uid_valid(loginuid))
		return -EPERM;
	return 0;
}
