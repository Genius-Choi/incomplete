void bpf_register_prog_type(struct bpf_prog_type_list *tl)
{
	list_add(&tl->list_node, &bpf_prog_types);
}
