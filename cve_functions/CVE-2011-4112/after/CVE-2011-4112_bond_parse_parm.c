int bond_parse_parm(const char *buf, const struct bond_parm_tbl *tbl)
{
	int modeint = -1, i, rv;
	char *p, modestr[BOND_MAX_MODENAME_LEN + 1] = { 0, };

	for (p = (char *)buf; *p; p++)
		if (!(isdigit(*p) || isspace(*p)))
			break;

	if (*p)
		rv = sscanf(buf, "%20s", modestr);
	else
		rv = sscanf(buf, "%d", &modeint);

	if (!rv)
		return -1;

	for (i = 0; tbl[i].modename; i++) {
		if (modeint == tbl[i].mode)
			return tbl[i].mode;
		if (strcmp(modestr, tbl[i].modename) == 0)
			return tbl[i].mode;
	}

	return -1;
}
