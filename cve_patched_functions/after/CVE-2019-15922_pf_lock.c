static void pf_lock(struct pf_unit *pf, int func)
{
	char lo_cmd[12] = { ATAPI_LOCK, pf->lun << 5, 0, 0, func, 0, 0, 0, 0, 0, 0, 0 };

	pf_atapi(pf, lo_cmd, 0, pf_scratch, func ? "lock" : "unlock");
}
