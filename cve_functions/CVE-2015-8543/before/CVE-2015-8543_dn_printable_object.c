static void dn_printable_object(struct sockaddr_dn *dn, unsigned char *buf)
{
	int i;

	switch (le16_to_cpu(dn->sdn_objnamel)) {
	case 0:
		sprintf(buf, "%d", dn->sdn_objnum);
		break;
	default:
		for (i = 0; i < le16_to_cpu(dn->sdn_objnamel); i++) {
			buf[i] = dn->sdn_objname[i];
			if (IS_NOT_PRINTABLE(buf[i]))
				buf[i] = '.';
		}
		buf[i] = 0;
	}
}
