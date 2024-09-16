static void InsertComplexDoubleRow(Image *image,double *p,int y,double MinVal,
  double MaxVal,ExceptionInfo *exception)
{
  double f;
  int x;
  register Quantum *q;

  if (MinVal >= 0)
    MinVal = -1;
  if (MaxVal <= 0)
    MaxVal = 1;

  q=QueueAuthenticPixels(image,0,y,image->columns,1,exception);
  if (q == (Quantum *) NULL)
    return;
  for (x = 0; x < (ssize_t) image->columns; x++)
  {
    if (*p > 0)
      {
        f=(*p/MaxVal)*(Quantum) (QuantumRange-GetPixelRed(image,q));
        if ((f+GetPixelRed(image,q)) >= QuantumRange)
          SetPixelRed(image,QuantumRange,q);
        else
          SetPixelRed(image,GetPixelRed(image,q)+ClampToQuantum(f),q);
        f=GetPixelGreen(image,q)-f/2.0;
        if (f <= 0.0)
          {
            SetPixelGreen(image,0,q);
            SetPixelBlue(image,0,q);
          }
        else
          {
            SetPixelBlue(image,ClampToQuantum(f),q);
            SetPixelGreen(image,ClampToQuantum(f),q);
          }
      }
    if (*p < 0)
      {
        f=(*p/MinVal)*(Quantum) (QuantumRange-GetPixelBlue(image,q));
        if ((f+GetPixelBlue(image,q)) >= QuantumRange)
          SetPixelBlue(image,QuantumRange,q);
        else
          SetPixelBlue(image,GetPixelBlue(image,q)+ClampToQuantum(f),q);
        f=GetPixelGreen(image,q)-f/2.0;
        if (f <= 0.0)
          {
            SetPixelRed(image,0,q);
            SetPixelGreen(image,0,q);
          }
        else
          {
            SetPixelRed(image,ClampToQuantum(f),q);
            SetPixelGreen(image,ClampToQuantum(f),q);
          }
      }
    p++;
    q++;
  }
  if (!SyncAuthenticPixels(image,exception))
    return;
  return;
}
