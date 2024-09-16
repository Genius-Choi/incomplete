int bpf_obj_pin_user(u32 ufd, const char __user *pathname)
{
	struct filename *pname;
	enum bpf_type type;
	void *raw;
	int ret;

	pname = getname(pathname);
	if (IS_ERR(pname))
		return PTR_ERR(pname);

	raw = bpf_fd_probe_obj(ufd, &type);
	if (IS_ERR(raw)) {
		ret = PTR_ERR(raw);
		goto out;
	}

	ret = bpf_obj_do_pin(pname, raw, type);
	if (ret != 0)
		bpf_any_put(raw, type);
out:
	putname(pname);
	return ret;
}
