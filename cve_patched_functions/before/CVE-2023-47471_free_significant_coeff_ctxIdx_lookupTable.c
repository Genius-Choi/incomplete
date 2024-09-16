void free_significant_coeff_ctxIdx_lookupTable()
{
  free(ctxIdxLookup[0][0][0][0]);
  ctxIdxLookup[0][0][0][0]=NULL;
}
