isis_print_mcid(netdissect_options *ndo,
                const struct isis_spb_mcid *mcid)
{
  int i;

  ND_TCHECK(*mcid);
  ND_PRINT((ndo,  "ID: %d, Name: ", mcid->format_id));

  if (fn_printzp(ndo, mcid->name, 32, ndo->ndo_snapend))
    goto trunc;

  ND_PRINT((ndo, "\n\t              Lvl: %d", EXTRACT_16BITS(mcid->revision_lvl)));

  ND_PRINT((ndo,  ", Digest: "));

  for(i=0;i<16;i++)
    ND_PRINT((ndo, "%.2x ", mcid->digest[i]));

trunc:
  ND_PRINT((ndo, "%s", tstr));
}
