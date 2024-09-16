static void pf_mode_sense(struct pf_unit *pf)
{
	char ms_cmd[12] =
	    { ATAPI_MODE_SENSE, pf->lun << 5, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0 };
	char buf[8];

	pf_atapi(pf, ms_cmd, 8, buf, "mode sense");
	pf->media_status = PF_RW;
	if (buf[3] & 0x80)
		pf->media_status = PF_RO;
}
