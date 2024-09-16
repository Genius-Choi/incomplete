static int chmd_sys_write(struct mspack_file *file, void *buffer, int bytes) {
  struct mschm_decompressor_p *self = (struct mschm_decompressor_p *) file;
  self->d->offset += bytes;
  if (self->d->outfh) {
    return self->system->write(self->d->outfh, buffer, bytes);
  }
  return bytes;
}
