grub_ext2_dir (grub_device_t device, const char *path,
	       int (*hook) (const char *filename,
			    const struct grub_dirhook_info *info,
			    void *closure),
	       void *closure)
{
  struct grub_ext2_data *data = 0;
  struct grub_fshelp_node *fdiro = 0;
  struct grub_ext2_dir_closure c;

  grub_dl_ref (my_mod);

  data = grub_ext2_mount (device->disk);
  if (! data)
    goto fail;

  grub_fshelp_find_file (path, &data->diropen, &fdiro, grub_ext2_iterate_dir,
			 0, grub_ext2_read_symlink, GRUB_FSHELP_DIR);
  if (grub_errno)
    goto fail;

  c.hook = hook;
  c.closure = closure;
  c.data = data;
  grub_ext2_iterate_dir (fdiro, iterate, &c);

 fail:
  if (fdiro != &data->diropen)
    grub_free (fdiro);
  grub_free (data);

  grub_dl_unref (my_mod);

  return grub_errno;
}
