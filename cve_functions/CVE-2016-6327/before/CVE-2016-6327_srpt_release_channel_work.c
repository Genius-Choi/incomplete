static void srpt_release_channel_work(struct work_struct *w)
{
	struct srpt_rdma_ch *ch;
	struct srpt_device *sdev;
	struct se_session *se_sess;

	ch = container_of(w, struct srpt_rdma_ch, release_work);
	pr_debug("ch = %p; ch->sess = %p; release_done = %p\n", ch, ch->sess,
		 ch->release_done);

	sdev = ch->sport->sdev;
	BUG_ON(!sdev);

	se_sess = ch->sess;
	BUG_ON(!se_sess);

	target_wait_for_sess_cmds(se_sess);

	transport_deregister_session_configfs(se_sess);
	transport_deregister_session(se_sess);
	ch->sess = NULL;

	ib_destroy_cm_id(ch->cm_id);

	srpt_destroy_ch_ib(ch);

	srpt_free_ioctx_ring((struct srpt_ioctx **)ch->ioctx_ring,
			     ch->sport->sdev, ch->rq_size,
			     ch->rsp_size, DMA_TO_DEVICE);

	spin_lock_irq(&sdev->spinlock);
	list_del(&ch->list);
	spin_unlock_irq(&sdev->spinlock);

	if (ch->release_done)
		complete(ch->release_done);

	wake_up(&sdev->ch_releaseQ);

	kfree(ch);
}
