static u64 mem_cgroup_read(struct cgroup *cont, struct cftype *cft)
{
	struct mem_cgroup *memcg = mem_cgroup_from_cont(cont);
	u64 val;
	int type, name;

	type = MEMFILE_TYPE(cft->private);
	name = MEMFILE_ATTR(cft->private);
	switch (type) {
	case _MEM:
		if (name == RES_USAGE)
			val = mem_cgroup_usage(memcg, false);
		else
			val = res_counter_read_u64(&memcg->res, name);
		break;
	case _MEMSWAP:
		if (name == RES_USAGE)
			val = mem_cgroup_usage(memcg, true);
		else
			val = res_counter_read_u64(&memcg->memsw, name);
		break;
	default:
		BUG();
		break;
	}
	return val;
}
