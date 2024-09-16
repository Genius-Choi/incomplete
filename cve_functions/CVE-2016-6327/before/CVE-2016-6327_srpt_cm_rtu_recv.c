static void srpt_cm_rtu_recv(struct ib_cm_id *cm_id)
{
	struct srpt_rdma_ch *ch;
	int ret;

	ch = srpt_find_channel(cm_id->context, cm_id);
	BUG_ON(!ch);

	if (srpt_test_and_set_ch_state(ch, CH_CONNECTING, CH_LIVE)) {
		struct srpt_recv_ioctx *ioctx, *ioctx_tmp;

		ret = srpt_ch_qp_rts(ch, ch->qp);

		list_for_each_entry_safe(ioctx, ioctx_tmp, &ch->cmd_wait_list,
					 wait_list) {
			list_del(&ioctx->wait_list);
			srpt_handle_new_iu(ch, ioctx, NULL);
		}
		if (ret)
			srpt_close_ch(ch);
	}
}
