static char *iscsi_check_valuelist_for_support(
	struct iscsi_param *param,
	char *value)
{
	char *tmp1 = NULL, *tmp2 = NULL;
	char *acceptor_values = NULL, *proposer_values = NULL;

	acceptor_values = param->value;
	proposer_values = value;

	do {
		if (!proposer_values)
			return NULL;
		tmp1 = strchr(proposer_values, ',');
		if (tmp1)
			*tmp1 = '\0';
		acceptor_values = param->value;
		do {
			if (!acceptor_values) {
				if (tmp1)
					*tmp1 = ',';
				return NULL;
			}
			tmp2 = strchr(acceptor_values, ',');
			if (tmp2)
				*tmp2 = '\0';
			if (!strcmp(acceptor_values, proposer_values)) {
				if (tmp2)
					*tmp2 = ',';
				goto out;
			}
			if (tmp2)
				*tmp2++ = ',';

			acceptor_values = tmp2;
		} while (acceptor_values);
		if (tmp1)
			*tmp1++ = ',';
		proposer_values = tmp1;
	} while (proposer_values);

out:
	return proposer_values;
}
