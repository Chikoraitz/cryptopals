C implementation of the cryptopals challenges. To execute all challenges tests, run the unit_test.sh file.

# Setup CMocka testing framework 
https://sam.hooke.me/note/2022/04/setting-up-cmocka/

**Cryptopals Rule:** Always operate on raw bytes, never on encoded strings. Only use hex and base64 for pretty-printing.

# Challenge 1: Convert hex to base64
**Resources:**
- https://en.wikipedia.org/wiki/Base64
- https://datatracker.ietf.org/doc/html/rfc4648#section-4

The string:

`49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d`

Should produce:

`SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t`

