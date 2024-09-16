static int pcd_atapi(struct pcd_unit *cd, char *cmd, int dlen, char *buf, char *fun)
{
	int r;

	r = pcd_command(cd, cmd, dlen, fun);
	mdelay(1);
	if (!r)
		r = pcd_completion(cd, buf, fun);
	if (r)
		pcd_req_sense(cd, fun);

	return r;
}
