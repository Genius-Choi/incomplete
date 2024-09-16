static bool type_is_refcounted_or_null(enum bpf_reg_type type)
{
	return type == PTR_TO_SOCKET || type == PTR_TO_SOCKET_OR_NULL;
}
