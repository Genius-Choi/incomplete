static int pf_atapi(struct pf_unit *pf, char *cmd, int dlen, char *buf, char *fun)
{
	int r;

	r = pf_command(pf, cmd, dlen, fun);
	mdelay(1);
	if (!r)
		r = pf_completion(pf, buf, fun);
	if (r)
		pf_req_sense(pf, !fun);

	return r;
}
