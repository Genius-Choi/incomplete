static void write_pmlcb(int idx, unsigned long val)
{
	switch (idx) {
	case 0:
		mtpmr(PMRN_PMLCB0, val);
		break;
	case 1:
		mtpmr(PMRN_PMLCB1, val);
		break;
	case 2:
		mtpmr(PMRN_PMLCB2, val);
		break;
	case 3:
		mtpmr(PMRN_PMLCB3, val);
		break;
	default:
		printk(KERN_ERR "oops trying to write PMLCB%d\n", idx);
	}

	isync();
}
