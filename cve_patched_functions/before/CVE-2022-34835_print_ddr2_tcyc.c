static void print_ddr2_tcyc (u_char const b)
{
	printf ("%d.", (b >> 4) & 0x0F);
	switch (b & 0x0F) {
	case 0x0:
	case 0x1:
	case 0x2:
	case 0x3:
	case 0x4:
	case 0x5:
	case 0x6:
	case 0x7:
	case 0x8:
	case 0x9:
		printf ("%d ns\n", b & 0x0F);
		break;
	case 0xA:
		puts ("25 ns\n");
		break;
	case 0xB:
		puts ("33 ns\n");
		break;
	case 0xC:
		puts ("66 ns\n");
		break;
	case 0xD:
		puts ("75 ns\n");
		break;
	default:
		puts ("?? ns\n");
		break;
	}
}
