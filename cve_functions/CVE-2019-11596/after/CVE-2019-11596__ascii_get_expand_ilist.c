static inline int _ascii_get_expand_ilist(conn *c, int i) {
    if (i >= c->isize) {
        item **new_list = realloc(c->ilist, sizeof(item *) * c->isize * 2);
        if (new_list) {
            c->isize *= 2;
            c->ilist = new_list;
        } else {
            STATS_LOCK();
            stats.malloc_fails++;
            STATS_UNLOCK();
            return -1;
        }
    }
    return 0;
}
