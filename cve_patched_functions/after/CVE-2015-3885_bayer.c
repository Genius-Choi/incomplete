int CLASS bayer (unsigned row, unsigned col)
{
  return (row < height && col < width) ? BAYER(row,col) : 0;
}
