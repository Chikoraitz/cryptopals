#include "../cmocka_api.h"

#include "../../include/challenges/set1.h"

/**
 * Challenge 1:
 * Convert binary in hex format into base64 format 
*/
void validate_challenge1(void ** state) {
  (void) state; // Unused
  const char input[] = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d";
  char result[200];
  
  c1(input, result);
  assert_string_equal(
    result,
    "SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t"
  );  
}

/**
 * Challenge 2:
 * One-time pad XOR encryption
*/
void validate_challenge2(void ** state) {
  (void) state; // Unused
  char result[200];
  c2(
    "1c0111001f010100061a024b53535009181c",
    "686974207468652062756c6c277320657965",
    result
  );
  assert_string_equal(result, "746865206b696420646f6e277420706c6179");
}


/**
 * Challenge 3:
 * Single-byte XOR cipher decryption
*/
void validate_challenge3(void ** state) {
  (void) state; // Unused
  char msg[200];
  c3("1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736", msg);
  assert_string_equal(msg, "Cooking MC's like a pound of bacon");
}

/**
 * Challenge 4:
 * Detect single-character XOR ciphers
*/
void validate_challenge4(void ** state) {
  (void) state;
  char cipher_hexstr[61];
  c4("../../assets/set1/4.txt", cipher_hexstr);
  assert_string_equal(cipher_hexstr, "7b5a4215415d544115415d5015455447414c155c46155f4058455c5b523f");
}


/**
 * Challenge 5:
 * Implementation of Repeating-key XOR
*/
void validate_challenge5(void ** state) {
  (void) state;
  const char * plaintext = "Burning 'em, if you ain't quick and nimble\nI go crazy when I hear a cymbal";
  const char * key = "ICE";
  char cipher_hexstr[strlen(plaintext) * NIBBLE_BYTE];
  
  c5(plaintext, key, cipher_hexstr);
  assert_string_equal(
    cipher_hexstr,
    "0b3637272a2b2e63622c2e69692a23693a2a3c6324202d623d63343c2a26226324272765272a282b2f20430a652e2c652a3124333a653e2b2027630c692b20283165286326302e27282f"
  );
}


/**
 * Challenge 6:
 * Break Repeating-Key XOR
*/
void validate_challenge6(void ** state) {
  (void) state;
  const char * filepath = "../../assets/set1/6.txt";
  char key[100];

  c6(filepath, key);
  assert_string_equal(key, "Terminator X: Bring the noise");
}


/**
 * Challenge 7:
 * AES in ECB mode
 */
void validate_challenge7(void ** state) {
  (void) state;
  const char * filepath = "../../assets/set1/7.txt";
  char plaintext[2000];
  char result[] = "I'm back and I'm ringin' the bell \nA rockin' on the mike while the fly girls yell \nIn ecstasy in the back of me \nWell that's my DJ Deshay cuttin' all them Z's \nHittin' hard and the girlies goin' crazy \nVanilla's on the mike, man I'm not lazy. \n\nI'm lettin' my drug kick in \nIt controls my mouth and I begin \nTo just let it flow, let my concepts go \nMy posse's to the side yellin', Go Vanilla Go! \n\nSmooth 'cause that's the way I will be \nAnd if you don't give a damn, then \nWhy you starin' at me \nSo get off 'cause I control the stage \nThere's no dissin' allowed \nI'm in my own phase \nThe girlies sa y they love me and that is ok \nAnd I can dance better than any kid n' play \n\nStage 2 -- Yea the one ya' wanna listen to \nIt's off my head so let the beat play through \nSo I can funk it up and make it sound good \n1-2-3 Yo -- Knock on some wood \nFor good luck, I like my rhymes atrocious \nSupercalafragilisticexpialidocious \nI'm an effect and that you can bet \nI can take a fly girl and make her wet. \n\nI'm like Samson -- Samson to Delilah \nThere's no denyin', You can try to hang \nBut you'll keep tryin' to get my style \nOver and over, practice makes perfect \nBut not if you're a loafer. \n\nYou'll get nowhere, no place, no time, no girls \nSoon -- Oh my God, homebody, you probably eat \nSpaghetti with a spoon! Come on and say it! \n\nVIP. Vanilla Ice yep, yep, I'm comin' hard like a rhino \nIntoxicating so you stagger like a wino \nSo punks stop trying and girl stop cryin' \nVanilla Ice is sellin' and you people are buyin' \n'Cause why the freaks are jockin' like Crazy Glue \nMovin' and groovin' trying to sing along \nAll through the ghetto groovin' this here song \nNow you're amazed by the VIP posse. \n\nSteppin' so hard like a German Nazi \nStartled by the bases hittin' ground \nThere's no trippin' on mine, I'm just gettin' down \nSparkamatic, I'm hangin' tight like a fanatic \nYou trapped me once and I thought that \nYou might have it \nSo step down and lend me your ear \n'89 in my time! You, '90 is my year. \n\nYou're weakenin' fast, YO! and I can tell it \nYour body's gettin' hot, so, so I can smell it \nSo don't be mad and don't be sad \n'Cause the lyrics belong to ICE, You can call me Dad \nYou're pitchin' a fit, so step back and endure \nLet the witch doctor, Ice, do the dance to cure \nSo come up close and don't be square \nYou wanna battle me -- Anytime, anywhere \n\nYou thought that I was weak, Boy, you're dead wrong \nSo come on, everybody and sing this song \n\nSay -- Play that funky music Say, go white boy, go white boy go \nplay that funky music Go white boy, go white boy, go \nLay down and boogie and play that funky music till you die. \n\nPlay that funky music Come on, Come on, let me hear \nPlay that funky music white boy you say it, say it \nPlay that funky music A little louder now \nPlay that funky music, white boy Come on, Come on, Come on \nPlay that funky music";

  c7(filepath, plaintext);
  // assert_string_equal(plaintext, result);
}


int main(void) {
  const struct CMUnitTest tests[] = {
    cmocka_unit_test(validate_challenge1),
    cmocka_unit_test(validate_challenge2),
    cmocka_unit_test(validate_challenge3),
    cmocka_unit_test(validate_challenge4),
    cmocka_unit_test(validate_challenge5),
    cmocka_unit_test(validate_challenge6),
    cmocka_unit_test(validate_challenge7)
  };

  return cmocka_run_group_tests(tests, NULL, NULL);
}