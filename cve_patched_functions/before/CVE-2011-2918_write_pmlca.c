static void write_pmlca(int idx, unsigned long val)
{
	switch (idx) {
	case 0:
		mtpmr(PMRN_PMLCA0, val);
		break;
	case 1:
		mtpmr(PMRN_PMLCA1, val);
		break;
	case 2:
		mtpmr(PMRN_PMLCA2, val);
		break;
	case 3:
		mtpmr(PMRN_PMLCA3, val);
		break;
	default:
		printk(KERN_ERR "oops trying to write PMLCA%d\n", idx);
	}

	isync();
}
