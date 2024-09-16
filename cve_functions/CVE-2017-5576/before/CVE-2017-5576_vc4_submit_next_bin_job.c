vc4_submit_next_bin_job(struct drm_device *dev)
{
	struct vc4_dev *vc4 = to_vc4_dev(dev);
	struct vc4_exec_info *exec;

again:
	exec = vc4_first_bin_job(vc4);
	if (!exec)
		return;

	vc4_flush_caches(dev);

	/* Either put the job in the binner if it uses the binner, or
	 * immediately move it to the to-be-rendered queue.
	 */
	if (exec->ct0ca != exec->ct0ea) {
		submit_cl(dev, 0, exec->ct0ca, exec->ct0ea);
	} else {
		vc4_move_job_to_render(dev, exec);
		goto again;
	}
}
