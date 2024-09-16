static int mem_cgroup_reset(struct cgroup *cont, unsigned int event)
{
	struct mem_cgroup *memcg;
	int type, name;

	memcg = mem_cgroup_from_cont(cont);
	type = MEMFILE_TYPE(event);
	name = MEMFILE_ATTR(event);
	switch (name) {
	case RES_MAX_USAGE:
		if (type == _MEM)
			res_counter_reset_max(&memcg->res);
		else
			res_counter_reset_max(&memcg->memsw);
		break;
	case RES_FAILCNT:
		if (type == _MEM)
			res_counter_reset_failcnt(&memcg->res);
		else
			res_counter_reset_failcnt(&memcg->memsw);
		break;
	}

	return 0;
}
