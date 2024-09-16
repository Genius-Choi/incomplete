local struct space *get_space(struct pool *pool)
{
    struct space *space;

    /* if can't create any more, wait for a space to show up */
    possess(pool->have);
    if (pool->limit == 0)
        wait_for(pool->have, NOT_TO_BE, 0);

    /* if a space is available, pull it from the list and return it */
    if (pool->head != NULL) {
        space = pool->head;
        possess(space->use);
        pool->head = space->next;
        twist(pool->have, BY, -1);      /* one less in pool */
        twist(space->use, TO, 1);       /* initially one user */
        space->len = 0;
        return space;
    }

    /* nothing available, don't want to wait, make a new space */
    assert(pool->limit != 0);
    if (pool->limit > 0)
        pool->limit--;
    pool->made++;
    release(pool->have);
    space = MALLOC(sizeof(struct space));
    if (space == NULL)
        bail("not enough memory", "");
    space->use = new_lock(1);           /* initially one user */
    space->buf = MALLOC(pool->size);
    if (space->buf == NULL)
        bail("not enough memory", "");
    space->size = pool->size;
    space->len = 0;
    space->pool = pool;                 /* remember the pool this belongs to */
    return space;
}
