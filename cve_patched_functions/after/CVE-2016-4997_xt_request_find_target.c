struct xt_target *xt_request_find_target(u8 af, const char *name, u8 revision)
{
	struct xt_target *target;

	target = xt_find_target(af, name, revision);
	if (IS_ERR(target)) {
		request_module("%st_%s", xt_prefix[af], name);
		target = xt_find_target(af, name, revision);
	}

	return target;
}
