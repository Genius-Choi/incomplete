static void dump_cbsize(de265_image* img)
{
  int w = img->get_width(0);
  int h = img->get_height(0);

  for (int y=0;y<h;y+=8) {
    for (int x=0;x<w;x+=8) {
      printf("%d",img->get_log2CbSize(x,y));
    }
    printf("\n");
  }
}
