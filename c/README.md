C implementation of the cryptopals challenges - the solutions implementation were built into a single library with CMake. The solution's validity is ensured through CMocka unit tests: run the unit_test.sh bash file.

# Setup CMocka testing framework 
https://sam.hooke.me/note/2022/04/setting-up-cmocka/

**Cryptopals Rule:** Always operate on raw bytes, never on encoded strings. Only use hex and base64 for pretty-printing.
