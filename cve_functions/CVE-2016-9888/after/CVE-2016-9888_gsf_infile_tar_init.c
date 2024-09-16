gsf_infile_tar_init (GObject *obj)
{
	GsfInfileTar *tar = (GsfInfileTar *)obj;
	tar->source = NULL;
	tar->children = g_array_new (FALSE, FALSE, sizeof (TarChild));
	tar->err = NULL;
}
