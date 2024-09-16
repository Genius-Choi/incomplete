print_attr_time(netdissect_options *ndo,
                register const u_char *data, u_int length, u_short attr_code _U_)
{
   time_t attr_time;
   char string[26];

   if (length != 4)
   {
       ND_PRINT((ndo, "ERROR: length %u != 4", length));
       return;
   }

   ND_TCHECK2(data[0],4);

   attr_time = EXTRACT_32BITS(data);
   strlcpy(string, ctime(&attr_time), sizeof(string));
   /* Get rid of the newline */
   string[24] = '\0';
   ND_PRINT((ndo, "%.24s", string));
   return;

   trunc:
     ND_PRINT((ndo, "%s", tstr));
}
