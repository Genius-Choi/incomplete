static JSON_INLINE void list_remove(list_t *list)
{
    list->prev->next = list->next;
    list->next->prev = list->prev;
}
