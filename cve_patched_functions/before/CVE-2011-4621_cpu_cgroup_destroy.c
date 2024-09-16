cpu_cgroup_destroy(struct cgroup_subsys *ss, struct cgroup *cgrp)
{
	struct task_group *tg = cgroup_tg(cgrp);

	sched_destroy_group(tg);
}
