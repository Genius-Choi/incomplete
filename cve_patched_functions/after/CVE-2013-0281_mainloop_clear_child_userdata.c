mainloop_clear_child_userdata(mainloop_child_t *child)
{
    child->privatedata = NULL;
}
