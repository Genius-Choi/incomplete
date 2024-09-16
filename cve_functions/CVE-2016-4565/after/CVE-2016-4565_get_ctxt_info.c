static int get_ctxt_info(struct file *fp, void __user *ubase, __u32 len)
{
	struct hfi1_ctxt_info cinfo;
	struct hfi1_filedata *fd = fp->private_data;
	struct hfi1_ctxtdata *uctxt = fd->uctxt;
	int ret = 0;

	memset(&cinfo, 0, sizeof(cinfo));
	ret = hfi1_get_base_kinfo(uctxt, &cinfo);
	if (ret < 0)
		goto done;
	cinfo.num_active = hfi1_count_active_units();
	cinfo.unit = uctxt->dd->unit;
	cinfo.ctxt = uctxt->ctxt;
	cinfo.subctxt = fd->subctxt;
	cinfo.rcvtids = roundup(uctxt->egrbufs.alloced,
				uctxt->dd->rcv_entries.group_size) +
		uctxt->expected_count;
	cinfo.credits = uctxt->sc->credits;
	cinfo.numa_node = uctxt->numa_id;
	cinfo.rec_cpu = fd->rec_cpu_num;
	cinfo.send_ctxt = uctxt->sc->hw_context;

	cinfo.egrtids = uctxt->egrbufs.alloced;
	cinfo.rcvhdrq_cnt = uctxt->rcvhdrq_cnt;
	cinfo.rcvhdrq_entsize = uctxt->rcvhdrqentsize << 2;
	cinfo.sdma_ring_size = fd->cq->nentries;
	cinfo.rcvegr_size = uctxt->egrbufs.rcvtid_size;

	trace_hfi1_ctxt_info(uctxt->dd, uctxt->ctxt, fd->subctxt, cinfo);
	if (copy_to_user(ubase, &cinfo, sizeof(cinfo)))
		ret = -EFAULT;
done:
	return ret;
}
