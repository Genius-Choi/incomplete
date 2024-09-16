static int find_free_ctxt(int unit, struct file *fp,
			  const struct qib_user_info *uinfo)
{
	struct qib_devdata *dd = qib_lookup(unit);
	int ret;

	if (!dd || (uinfo->spu_port && uinfo->spu_port > dd->num_pports))
		ret = -ENODEV;
	else
		ret = choose_port_ctxt(fp, dd, uinfo->spu_port, uinfo);

	return ret;
}
