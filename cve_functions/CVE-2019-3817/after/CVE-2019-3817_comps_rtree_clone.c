COMPS_RTree * comps_rtree_clone(COMPS_RTree *rt) {

    COMPS_HSList *to_clone, *tmplist, *new_subnodes;
    COMPS_RTree *ret;
    COMPS_HSListItem *it, *it2;
    COMPS_RTreeData *rtdata;
    void *new_data;

    if (!rt) return NULL;

    to_clone = comps_hslist_create();
    comps_hslist_init(to_clone, NULL, NULL, NULL);
    ret = comps_rtree_create(rt->data_constructor, rt->data_cloner,
                             rt->data_destructor);


    for (it = rt->subnodes->first; it != NULL; it = it->next) {
        rtdata = comps_rtree_data_create(ret,
                                      ((COMPS_RTreeData*)it->data)->key, NULL);
        if (((COMPS_RTreeData*)it->data)->data != NULL)
            new_data = rt->data_cloner(((COMPS_RTreeData*)it->data)->data);
        else
            new_data = NULL;
        comps_hslist_destroy(&rtdata->subnodes);
        rtdata->subnodes = ((COMPS_RTreeData*)it->data)->subnodes;
        rtdata->data = new_data;
        comps_hslist_append(ret->subnodes, rtdata, 0);

        comps_hslist_append(to_clone, rtdata, 0);
    }


    while (to_clone->first) {
        it2 = to_clone->first;
        tmplist = ((COMPS_RTreeData*)it2->data)->subnodes;
        comps_hslist_remove(to_clone, to_clone->first);

        new_subnodes = comps_hslist_create();
        comps_hslist_init(new_subnodes, NULL, NULL, &comps_rtree_data_destroy_v);
        for (it = tmplist->first; it != NULL; it = it->next) {
            rtdata = comps_rtree_data_create(ret,
                                      ((COMPS_RTreeData*)it->data)->key, NULL);
            if (((COMPS_RTreeData*)it->data)->data != NULL)
                new_data = rt->data_cloner(((COMPS_RTreeData*)it->data)->data);
            else
                new_data = NULL;
            comps_hslist_destroy(&rtdata->subnodes);
            rtdata->subnodes = ((COMPS_RTreeData*)it->data)->subnodes;
            rtdata->data = new_data;
            comps_hslist_append(new_subnodes, rtdata, 0);

            comps_hslist_append(to_clone, rtdata, 0);
        }
        ((COMPS_RTreeData*)it2->data)->subnodes = new_subnodes;
        free(it2);
    }
    comps_hslist_destroy(&to_clone);
    return ret;
}
