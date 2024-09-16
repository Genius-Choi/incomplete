bool ns_capable(struct user_namespace *ns, int cap)
{
	if (unlikely(!cap_valid(cap))) {
		pr_crit("capable() called with invalid cap=%u\n", cap);
		BUG();
	}

	if (security_capable(current_cred(), ns, cap) == 0) {
		current->flags |= PF_SUPERPRIV;
		return true;
	}
	return false;
}
