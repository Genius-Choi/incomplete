static void _dlist_free_children(struct dlist *dl)
{
    struct dlist *next;
    struct dlist *i;

    if (!dl) return;

    i = dl->head;
    while (i) {
        next = i->next;
        dlist_free(&i);
        i = next;
    }

    dl->head = dl->tail = NULL;
}
