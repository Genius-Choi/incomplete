perf_cgroup_from_task(struct task_struct *task)
{
	return container_of(task_css(task, perf_event_cgrp_id),
			    struct perf_cgroup, css);
}
