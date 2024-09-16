static int id_fxfd(struct sh_fpu_soft_struct *fregs, int x)
{
	const int flag[] = { FPSCR_SZ, FPSCR_PR, FPSCR_FR, 0 };
	switch (x & 3) {
	case 3:
		fxchg(fregs, flag[x >> 2]);
		break;
	case 1:
		ftrv(fregs, x - 1);
		break;
	default:
		fsca(fregs, x);
	}
	return 0;
}
