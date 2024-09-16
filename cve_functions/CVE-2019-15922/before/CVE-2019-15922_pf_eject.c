static void pf_eject(struct pf_unit *pf)
{
	char ej_cmd[12] = { ATAPI_DOOR, pf->lun << 5, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0 };

	pf_lock(pf, 0);
	pf_atapi(pf, ej_cmd, 0, pf_scratch, "eject");
}
