struct mem_cgroup *mem_cgroup_iter(struct mem_cgroup *root,
				   struct mem_cgroup *prev,
				   struct mem_cgroup_reclaim_cookie *reclaim)
{
	struct mem_cgroup *memcg = NULL;
	int id = 0;

	if (mem_cgroup_disabled())
		return NULL;

	if (!root)
		root = root_mem_cgroup;

	if (prev && !reclaim)
		id = css_id(&prev->css);

	if (prev && prev != root)
		css_put(&prev->css);

	if (!root->use_hierarchy && root != root_mem_cgroup) {
		if (prev)
			return NULL;
		return root;
	}

	while (!memcg) {
		struct mem_cgroup_reclaim_iter *uninitialized_var(iter);
		struct cgroup_subsys_state *css;

		if (reclaim) {
			int nid = zone_to_nid(reclaim->zone);
			int zid = zone_idx(reclaim->zone);
			struct mem_cgroup_per_zone *mz;

			mz = mem_cgroup_zoneinfo(root, nid, zid);
			iter = &mz->reclaim_iter[reclaim->priority];
			if (prev && reclaim->generation != iter->generation)
				return NULL;
			id = iter->position;
		}

		rcu_read_lock();
		css = css_get_next(&mem_cgroup_subsys, id + 1, &root->css, &id);
		if (css) {
			if (css == &root->css || css_tryget(css))
				memcg = container_of(css,
						     struct mem_cgroup, css);
		} else
			id = 0;
		rcu_read_unlock();

		if (reclaim) {
			iter->position = id;
			if (!css)
				iter->generation++;
			else if (!prev && memcg)
				reclaim->generation = iter->generation;
		}

		if (prev && !css)
			return NULL;
	}
	return memcg;
}
