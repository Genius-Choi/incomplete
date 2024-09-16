gsf_infile_tar_get_property (GObject     *object,
			     guint        property_id,
			     GValue      *value,
			     GParamSpec  *pspec)
{
	GsfInfileTar *tar = (GsfInfileTar *)object;

	switch (property_id) {
	case PROP_SOURCE:
		g_value_set_object (value, tar->source);
		break;
	default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
		break;
	}
}
