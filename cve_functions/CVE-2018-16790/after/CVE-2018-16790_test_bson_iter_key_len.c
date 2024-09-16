test_bson_iter_key_len (void)
{
   bson_t *bson = bson_with_all_types ();
   bson_iter_t iter;

   BSON_ASSERT (bson_iter_init (&iter, bson));
   while (bson_iter_next (&iter)) {
      ASSERT_WITH_MSG (strlen (bson_iter_key (&iter)) ==
                          bson_iter_key_len (&iter),
                       "iter_key_len differs from real key length. got %d but "
                       "expected %d for key %s\n",
                       bson_iter_key_len (&iter),
                       (int) strlen (bson_iter_key (&iter)),
                       bson_iter_key (&iter));
   }
}
