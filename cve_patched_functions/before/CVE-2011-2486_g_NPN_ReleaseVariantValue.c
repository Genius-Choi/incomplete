g_NPN_ReleaseVariantValue(NPVariant *variant)
{
  D(bugiI("NPN_ReleaseVariantValue\n"));
  npvariant_clear(variant);
  D(bugiD("NPN_ReleaseVariantValue done\n"));
}
