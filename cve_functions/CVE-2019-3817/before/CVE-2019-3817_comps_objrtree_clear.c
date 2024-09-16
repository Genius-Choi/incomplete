void comps_objrtree_clear(COMPS_ObjRTree * rt) {
    COMPS_HSListItem *it, *oldit;
    if (rt==NULL) return;
    if (rt->subnodes == NULL) return;
    oldit = rt->subnodes->first;
    it = (oldit)?oldit->next:NULL;
    for (;it != NULL; it=it->next) {
        comps_object_destroy(oldit->data);
        free(oldit);
        oldit = it;
    }
    if (oldit) {
        comps_object_destroy(oldit->data);
        free(oldit);
    }
}
