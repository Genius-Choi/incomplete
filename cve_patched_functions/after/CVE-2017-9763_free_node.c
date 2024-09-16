free_node (grub_fshelp_node_t node, struct grub_fshelp_find_file_closure *c)
{
  if (node != c->rootnode && node != c->currroot)
    grub_free (node);
}
