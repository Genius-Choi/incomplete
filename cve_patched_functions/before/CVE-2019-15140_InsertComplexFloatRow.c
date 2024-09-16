static void InsertComplexFloatRow(Image *image,float *p,int y,double MinVal,
  double MaxVal,ExceptionInfo *exception)
{
  double f;
  int x;
  register Quantum *q;

  if (MinVal >= 0)
    MinVal = -1;
  if (MaxVal <= 0)
    MaxVal = 1;

  q = QueueAuthenticPixels(image, 0, y, image->columns, 1,exception);
  if (q == (Quantum *) NULL)
    return;
  for (x = 0; x < (ssize_t) image->columns; x++)
  {
    if (*p > 0)
      {
        f=(*p/MaxVal)*(Quantum) (QuantumRange-GetPixelRed(image,q));
        if ((f+GetPixelRed(image,q)) < QuantumRange)
          SetPixelRed(image,GetPixelRed(image,q)+ClampToQuantum(f),q);
        else
          SetPixelRed(image,QuantumRange,q);
        f/=2.0;
        if (f < GetPixelGreen(image,q))
          {
            SetPixelBlue(image,GetPixelBlue(image,q)-ClampToQuantum(f),q);
            SetPixelGreen(image,GetPixelBlue(image,q),q);
          }
        else
          {
            SetPixelGreen(image,0,q);
            SetPixelBlue(image,0,q);
          }
      }
    if (*p < 0)
      {
        f=(*p/MaxVal)*(Quantum) (QuantumRange-GetPixelBlue(image,q));
        if ((f+GetPixelBlue(image,q)) < QuantumRange)
          SetPixelBlue(image,GetPixelBlue(image,q)+ClampToQuantum(f),q);
        else
          SetPixelBlue(image,QuantumRange,q);
        f/=2.0;
        if (f < GetPixelGreen(image,q))
          {
            SetPixelRed(image,GetPixelRed(image,q)-ClampToQuantum(f),q);
            SetPixelGreen(image,GetPixelRed(image,q),q);
          }
        else
          {
            SetPixelGreen(image,0,q);
            SetPixelRed(image,0,q);
          }
      }
    p++;
    q++;
  }
  if (!SyncAuthenticPixels(image,exception))
    return;
  return;
}
