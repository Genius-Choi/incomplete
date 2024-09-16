bson_iter_overwrite_date_time (bson_iter_t *iter, int64_t value)
{
   BSON_ASSERT (iter);

   if (ITER_TYPE (iter) == BSON_TYPE_DATE_TIME) {
      value = BSON_UINT64_TO_LE (value);
      memcpy ((void *) (iter->raw + iter->d1), &value, sizeof (value));
   }
}
