gsf_infile_tar_constructor (GType                  type,
			    guint                  n_construct_properties,
			    GObjectConstructParam *construct_params)
{
	GsfInfileTar *tar = (GsfInfileTar *)
		(parent_class->constructor (type,
					    n_construct_properties,
					    construct_params));
	if (tar->source)
		tar_init_info (tar);

	return (GObject *)tar;
}
