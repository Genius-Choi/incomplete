void comps_rtree_print(COMPS_HSList * hl, unsigned  deep) {
    COMPS_HSListItem * it;
    for (it = hl->first; it != NULL; it=it->next) {
        printf("%d %s\n",deep, (((COMPS_RTreeData*)it->data)->key));
        comps_rtree_print(((COMPS_RTreeData*)it->data)->subnodes, deep+1);
    }
}
