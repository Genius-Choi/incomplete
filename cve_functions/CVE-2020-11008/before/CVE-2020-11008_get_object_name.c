static char *get_object_name(struct fsck_options *options, struct object *obj)
{
	if (!options->object_names)
		return NULL;
	return lookup_decoration(options->object_names, obj);
}
