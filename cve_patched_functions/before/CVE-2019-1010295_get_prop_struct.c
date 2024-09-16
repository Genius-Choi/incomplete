static const struct tee_props *get_prop_struct(unsigned long prop_set,
					       unsigned long index)
{
	const struct tee_props *props;
	const struct tee_props *vendor_props;
	size_t size;
	size_t vendor_size;

	get_prop_set(prop_set, &props, &size, &vendor_props, &vendor_size);

	if (index < size)
		return &(props[index]);
	index -= size;

	if (index < vendor_size)
		return &(vendor_props[index]);

	return NULL;
}
