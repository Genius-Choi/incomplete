static int srpt_xfer_data(struct srpt_rdma_ch *ch,
			  struct srpt_send_ioctx *ioctx)
{
	int ret;

	ret = srpt_map_sg_to_ib_sge(ch, ioctx);
	if (ret) {
		pr_err("%s[%d] ret=%d\n", __func__, __LINE__, ret);
		goto out;
	}

	ret = srpt_perform_rdmas(ch, ioctx);
	if (ret) {
		if (ret == -EAGAIN || ret == -ENOMEM)
			pr_info("%s[%d] queue full -- ret=%d\n",
				__func__, __LINE__, ret);
		else
			pr_err("%s[%d] fatal error -- ret=%d\n",
			       __func__, __LINE__, ret);
		goto out_unmap;
	}

out:
	return ret;
out_unmap:
	srpt_unmap_sg_to_ib_sge(ch, ioctx);
	goto out;
}
