vc4_hangcheck_elapsed(unsigned long data)
{
	struct drm_device *dev = (struct drm_device *)data;
	struct vc4_dev *vc4 = to_vc4_dev(dev);
	uint32_t ct0ca, ct1ca;
	unsigned long irqflags;
	struct vc4_exec_info *bin_exec, *render_exec;

	spin_lock_irqsave(&vc4->job_lock, irqflags);

	bin_exec = vc4_first_bin_job(vc4);
	render_exec = vc4_first_render_job(vc4);

	/* If idle, we can stop watching for hangs. */
	if (!bin_exec && !render_exec) {
		spin_unlock_irqrestore(&vc4->job_lock, irqflags);
		return;
	}

	ct0ca = V3D_READ(V3D_CTNCA(0));
	ct1ca = V3D_READ(V3D_CTNCA(1));

	/* If we've made any progress in execution, rearm the timer
	 * and wait.
	 */
	if ((bin_exec && ct0ca != bin_exec->last_ct0ca) ||
	    (render_exec && ct1ca != render_exec->last_ct1ca)) {
		if (bin_exec)
			bin_exec->last_ct0ca = ct0ca;
		if (render_exec)
			render_exec->last_ct1ca = ct1ca;
		spin_unlock_irqrestore(&vc4->job_lock, irqflags);
		vc4_queue_hangcheck(dev);
		return;
	}

	spin_unlock_irqrestore(&vc4->job_lock, irqflags);

	/* We've gone too long with no progress, reset.  This has to
	 * be done from a work struct, since resetting can sleep and
	 * this timer hook isn't allowed to.
	 */
	schedule_work(&vc4->hangcheck.reset_work);
}
