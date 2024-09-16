ofproto_enumerate_types(struct sset *types)
{
    size_t i;

    sset_clear(types);
    for (i = 0; i < n_ofproto_classes; i++) {
        ofproto_classes[i]->enumerate_types(types);
    }
}
