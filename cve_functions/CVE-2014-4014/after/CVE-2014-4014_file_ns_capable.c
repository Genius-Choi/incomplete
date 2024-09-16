bool file_ns_capable(const struct file *file, struct user_namespace *ns,
		     int cap)
{
	if (WARN_ON_ONCE(!cap_valid(cap)))
		return false;

	if (security_capable(file->f_cred, ns, cap) == 0)
		return true;

	return false;
}
