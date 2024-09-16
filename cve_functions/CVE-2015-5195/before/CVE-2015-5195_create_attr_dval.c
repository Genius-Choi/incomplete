create_attr_dval(
	int attr,
	double value
	)
{
	attr_val *my_val;

	my_val = emalloc_zero(sizeof(*my_val));
	my_val->attr = attr;
	my_val->value.d = value;
	my_val->type = T_Double;

	return my_val;
}
