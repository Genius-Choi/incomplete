grub_ext2_open (struct grub_file *file, const char *name)
{
  struct grub_ext2_data *data;
  struct grub_fshelp_node *fdiro = 0;

  grub_dl_ref (my_mod);

  data = grub_ext2_mount (file->device->disk);
  if (! data)
    goto fail;

  grub_fshelp_find_file (name, &data->diropen, &fdiro, grub_ext2_iterate_dir, 0,
			 grub_ext2_read_symlink, GRUB_FSHELP_REG);
  if (grub_errno)
    goto fail;

  if (! fdiro->inode_read)
    {
      grub_ext2_read_inode (data, fdiro->ino, &fdiro->inode);
      if (grub_errno)
	goto fail;
    }

  grub_memcpy (data->inode, &fdiro->inode, sizeof (struct grub_ext2_inode));
  grub_free (fdiro);

  file->size = grub_le_to_cpu32 (data->inode->size);
  file->data = data;
  file->offset = 0;

  return 0;

 fail:
  if (fdiro != &data->diropen)
    grub_free (fdiro);
  grub_free (data);

  grub_dl_unref (my_mod);

  return grub_errno;
}
