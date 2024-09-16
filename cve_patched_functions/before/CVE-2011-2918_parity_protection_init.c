static inline void parity_protection_init(void)
{
	switch (current_cpu_type()) {
	case CPU_24K:
	case CPU_34K:
	case CPU_74K:
	case CPU_1004K:
		{
#define ERRCTL_PE	0x80000000
#define ERRCTL_L2P	0x00800000
			unsigned long errctl;
			unsigned int l1parity_present, l2parity_present;

			errctl = read_c0_ecc();
			errctl &= ~(ERRCTL_PE|ERRCTL_L2P);

			/* probe L1 parity support */
			write_c0_ecc(errctl | ERRCTL_PE);
			back_to_back_c0_hazard();
			l1parity_present = (read_c0_ecc() & ERRCTL_PE);

			/* probe L2 parity support */
			write_c0_ecc(errctl|ERRCTL_L2P);
			back_to_back_c0_hazard();
			l2parity_present = (read_c0_ecc() & ERRCTL_L2P);

			if (l1parity_present && l2parity_present) {
				if (l1parity)
					errctl |= ERRCTL_PE;
				if (l1parity ^ l2parity)
					errctl |= ERRCTL_L2P;
			} else if (l1parity_present) {
				if (l1parity)
					errctl |= ERRCTL_PE;
			} else if (l2parity_present) {
				if (l2parity)
					errctl |= ERRCTL_L2P;
			} else {
				/* No parity available */
			}

			printk(KERN_INFO "Writing ErrCtl register=%08lx\n", errctl);

			write_c0_ecc(errctl);
			back_to_back_c0_hazard();
			errctl = read_c0_ecc();
			printk(KERN_INFO "Readback ErrCtl register=%08lx\n", errctl);

			if (l1parity_present)
				printk(KERN_INFO "Cache parity protection %sabled\n",
				       (errctl & ERRCTL_PE) ? "en" : "dis");

			if (l2parity_present) {
				if (l1parity_present && l1parity)
					errctl ^= ERRCTL_L2P;
				printk(KERN_INFO "L2 cache parity protection %sabled\n",
				       (errctl & ERRCTL_L2P) ? "en" : "dis");
			}
		}
		break;

	case CPU_5KC:
		write_c0_ecc(0x80000000);
		back_to_back_c0_hazard();
		/* Set the PE bit (bit 31) in the c0_errctl register. */
		printk(KERN_INFO "Cache parity protection %sabled\n",
		       (read_c0_ecc() & 0x80000000) ? "en" : "dis");
		break;
	case CPU_20KC:
	case CPU_25KF:
		/* Clear the DE bit (bit 16) in the c0_status register. */
		printk(KERN_INFO "Enable cache parity protection for "
		       "MIPS 20KC/25KF CPUs.\n");
		clear_c0_status(ST0_DE);
		break;
	default:
		break;
	}
}
