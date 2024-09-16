create_attr_ival(
	int attr,
	int value
	)
{
	attr_val *my_val;

	my_val = emalloc_zero(sizeof(*my_val));
	my_val->attr = attr;
	my_val->value.i = value;
	my_val->type = T_Integer;

	return my_val;
}
