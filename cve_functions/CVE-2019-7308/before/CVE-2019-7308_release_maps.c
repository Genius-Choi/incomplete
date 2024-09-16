static void release_maps(struct bpf_verifier_env *env)
{
	enum bpf_cgroup_storage_type stype;
	int i;

	for_each_cgroup_storage_type(stype) {
		if (!env->prog->aux->cgroup_storage[stype])
			continue;
		bpf_cgroup_storage_release(env->prog,
			env->prog->aux->cgroup_storage[stype]);
	}

	for (i = 0; i < env->used_map_cnt; i++)
		bpf_map_put(env->used_maps[i]);
}
