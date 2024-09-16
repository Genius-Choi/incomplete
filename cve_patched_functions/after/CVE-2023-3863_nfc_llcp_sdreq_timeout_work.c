static void nfc_llcp_sdreq_timeout_work(struct work_struct *work)
{
	unsigned long time;
	HLIST_HEAD(nl_sdres_list);
	struct hlist_node *n;
	struct nfc_llcp_sdp_tlv *sdp;
	struct nfc_llcp_local *local = container_of(work, struct nfc_llcp_local,
						    sdreq_timeout_work);

	mutex_lock(&local->sdreq_lock);

	time = jiffies - msecs_to_jiffies(3 * local->remote_lto);

	hlist_for_each_entry_safe(sdp, n, &local->pending_sdreqs, node) {
		if (time_after(sdp->time, time))
			continue;

		sdp->sap = LLCP_SDP_UNBOUND;

		hlist_del(&sdp->node);

		hlist_add_head(&sdp->node, &nl_sdres_list);
	}

	if (!hlist_empty(&local->pending_sdreqs))
		mod_timer(&local->sdreq_timer,
			  jiffies + msecs_to_jiffies(3 * local->remote_lto));

	mutex_unlock(&local->sdreq_lock);

	if (!hlist_empty(&nl_sdres_list))
		nfc_genl_llc_send_sdres(local->dev, &nl_sdres_list);
}
