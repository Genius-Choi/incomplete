static void perf_cgroup_css_free(struct cgroup_subsys_state *css)
{
	struct perf_cgroup *jc = container_of(css, struct perf_cgroup, css);

	free_percpu(jc->info);
	kfree(jc);
}
