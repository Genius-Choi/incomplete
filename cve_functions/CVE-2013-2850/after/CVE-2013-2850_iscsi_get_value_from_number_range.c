static char *iscsi_get_value_from_number_range(
	struct iscsi_param *param,
	char *value)
{
	char *end_ptr, *tilde_ptr1 = NULL, *tilde_ptr2 = NULL;
	u32 acceptor_right_value, proposer_right_value;

	tilde_ptr1 = strchr(value, '~');
	if (!tilde_ptr1)
		return NULL;
	*tilde_ptr1++ = '\0';
	proposer_right_value = simple_strtoul(tilde_ptr1, &end_ptr, 0);

	tilde_ptr2 = strchr(param->value, '~');
	if (!tilde_ptr2)
		return NULL;
	*tilde_ptr2++ = '\0';
	acceptor_right_value = simple_strtoul(tilde_ptr2, &end_ptr, 0);

	return (acceptor_right_value >= proposer_right_value) ?
		tilde_ptr1 : tilde_ptr2;
}
