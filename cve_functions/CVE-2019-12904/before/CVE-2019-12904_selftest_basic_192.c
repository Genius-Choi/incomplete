selftest_basic_192 (void)
{
  RIJNDAEL_context *ctx;
  unsigned char *ctxmem;
  unsigned char scratch[16];

  static unsigned char plaintext_192[16] =
    {
      0x76,0x77,0x74,0x75,0xF1,0xF2,0xF3,0xF4,
      0xF8,0xF9,0xE6,0xE7,0x77,0x70,0x71,0x72
    };
  static unsigned char key_192[24] =
    {
      0x04,0x05,0x06,0x07,0x09,0x0A,0x0B,0x0C,
      0x0E,0x0F,0x10,0x11,0x13,0x14,0x15,0x16,
      0x18,0x19,0x1A,0x1B,0x1D,0x1E,0x1F,0x20
    };
  static const unsigned char ciphertext_192[16] =
    {
      0x5D,0x1E,0xF2,0x0D,0xCE,0xD6,0xBC,0xBC,
      0x12,0x13,0x1A,0xC7,0xC5,0x47,0x88,0xAA
    };

  ctx = _gcry_cipher_selftest_alloc_ctx (sizeof *ctx, &ctxmem);
  if (!ctx)
    return "failed to allocate memory";
  rijndael_setkey (ctx, key_192, sizeof(key_192), NULL);
  rijndael_encrypt (ctx, scratch, plaintext_192);
  if (memcmp (scratch, ciphertext_192, sizeof (ciphertext_192)))
    {
      xfree (ctxmem);
      return "AES-192 test encryption failed.";
    }
  rijndael_decrypt (ctx, scratch, scratch);
  xfree (ctxmem);
  if (memcmp (scratch, plaintext_192, sizeof (plaintext_192)))
    return "AES-192 test decryption failed.";

  return NULL;
}
