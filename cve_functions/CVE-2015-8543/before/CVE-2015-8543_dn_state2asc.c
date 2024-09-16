static char *dn_state2asc(unsigned char state)
{
	switch (state) {
	case DN_O:
		return "OPEN";
	case DN_CR:
		return "  CR";
	case DN_DR:
		return "  DR";
	case DN_DRC:
		return " DRC";
	case DN_CC:
		return "  CC";
	case DN_CI:
		return "  CI";
	case DN_NR:
		return "  NR";
	case DN_NC:
		return "  NC";
	case DN_CD:
		return "  CD";
	case DN_RJ:
		return "  RJ";
	case DN_RUN:
		return " RUN";
	case DN_DI:
		return "  DI";
	case DN_DIC:
		return " DIC";
	case DN_DN:
		return "  DN";
	case DN_CL:
		return "  CL";
	case DN_CN:
		return "  CN";
	}

	return "????";
}
