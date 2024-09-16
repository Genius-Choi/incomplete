void CLASS imacon_full_load_raw()
{
  int row, col;

  for (row=0; row < height; row++)
    for (col=0; col < width; col++)
      read_shorts (image[row*width+col], 3);
}
