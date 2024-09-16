val_to_valstr(guint32 val, const value_valuestring *vvs)
{
	gint i = 0;

	while (vvs[i].valstrptr) {
		if (vvs[i].value == val)
			return(vvs[i].valstrptr);
		i++;
	}

	return(NULL);
}
