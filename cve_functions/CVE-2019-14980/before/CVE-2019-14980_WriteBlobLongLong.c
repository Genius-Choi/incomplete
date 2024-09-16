MagickExport ssize_t WriteBlobLongLong(Image *image,const MagickSizeType value)
{
  unsigned char
    buffer[8];

  assert(image != (Image *) NULL);
  assert(image->signature == MagickCoreSignature);
  if (image->endian == LSBEndian)
    {
      buffer[0]=(unsigned char) value;
      buffer[1]=(unsigned char) (value >> 8);
      buffer[2]=(unsigned char) (value >> 16);
      buffer[3]=(unsigned char) (value >> 24);
      buffer[4]=(unsigned char) (value >> 32);
      buffer[5]=(unsigned char) (value >> 40);
      buffer[6]=(unsigned char) (value >> 48);
      buffer[7]=(unsigned char) (value >> 56);
      return(WriteBlobStream(image,8,buffer));
    }
  buffer[0]=(unsigned char) (value >> 56);
  buffer[1]=(unsigned char) (value >> 48);
  buffer[2]=(unsigned char) (value >> 40);
  buffer[3]=(unsigned char) (value >> 32);
  buffer[4]=(unsigned char) (value >> 24);
  buffer[5]=(unsigned char) (value >> 16);
  buffer[6]=(unsigned char) (value >> 8);
  buffer[7]=(unsigned char) value;
  return(WriteBlobStream(image,8,buffer));
}
