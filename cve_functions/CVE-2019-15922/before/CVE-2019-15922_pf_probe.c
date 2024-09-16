static int pf_probe(struct pf_unit *pf)
{
	if (pf->drive == -1) {
		for (pf->drive = 0; pf->drive <= 1; pf->drive++)
			if (!pf_reset(pf)) {
				if (pf->lun != -1)
					return pf_identify(pf);
				else
					for (pf->lun = 0; pf->lun < 8; pf->lun++)
						if (!pf_identify(pf))
							return 0;
			}
	} else {
		if (pf_reset(pf))
			return -1;
		if (pf->lun != -1)
			return pf_identify(pf);
		for (pf->lun = 0; pf->lun < 8; pf->lun++)
			if (!pf_identify(pf))
				return 0;
	}
	return -1;
}
