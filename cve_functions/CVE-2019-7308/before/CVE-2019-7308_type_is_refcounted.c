static bool type_is_refcounted(enum bpf_reg_type type)
{
	return type == PTR_TO_SOCKET;
}
