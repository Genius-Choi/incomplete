ofproto_type_wait(const char *datapath_type)
{
    const struct ofproto_class *class;

    datapath_type = ofproto_normalize_type(datapath_type);
    class = ofproto_class_find__(datapath_type);

    if (class->type_wait) {
        class->type_wait(datapath_type);
    }
}
