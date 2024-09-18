static void write_pmc(int idx, unsigned long val)
{
	switch (idx) {
	case 0:
		mtpmr(PMRN_PMC0, val);
		break;
	case 1:
		mtpmr(PMRN_PMC1, val);
		break;
	case 2:
		mtpmr(PMRN_PMC2, val);
		break;
	case 3:
		mtpmr(PMRN_PMC3, val);
		break;
	default:
		printk(KERN_ERR "oops trying to write PMC%d\n", idx);
	}

	isync();
}
