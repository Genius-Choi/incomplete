COMPS_MRTreeData * comps_mrtree_data_create(COMPS_MRTree * tree,
                                            char * key, void * data) {
    return comps_mrtree_data_create_n(tree, key, strlen(key), data);
}
