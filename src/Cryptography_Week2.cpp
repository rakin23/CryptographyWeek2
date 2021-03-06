//============================================================================
// Name        : Cryptography_Week2.cpp
// Author      : ASnyder
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using std::cout;
using std::cerr;
using std::endl;

#include <string>
using std::string;

#include <aes.h>
using CryptoPP::AES;

#include "cryptlib.h"
using CryptoPP::Exception;

#include "hex.h"
using CryptoPP::HexEncoder;
using CryptoPP::HexDecoder;

#include "filters.h"
using CryptoPP::StringSink;
using CryptoPP::StringSource;
using CryptoPP::StreamTransformationFilter;

#include "ccm.h"
using CryptoPP::CBC_Mode;
using CryptoPP::CTR_Mode;

#include "osrng.h"
using CryptoPP::AutoSeededRandomPool;


using namespace std;

const int cbcKey1[] = {0x14, 0x0b, 0x41, 0xb2, 0x2a, 0x29, 0xbe, 0xb4, 0x06, 0x1b,
      0xda, 0x66, 0xb6, 0x74, 0x7e, 0x14};
unsigned char cbcCipher1[] =
   {0x4c, 0xa0, 0x0f, 0xf4, 0xc8, 0x98, 0xd6, 0x1e,
    0x1e, 0xdb, 0xf1, 0x80, 0x06, 0x18, 0xfb, 0x28,
    0x28, 0xa2, 0x26, 0xd1, 0x60, 0xda, 0xd0, 0x78,
    0x83, 0xd0, 0x4e, 0x00, 0x8a, 0x78, 0x97, 0xee,
    0x2e, 0x4b, 0x74, 0x65, 0xd5, 0x29, 0x0d, 0x0c,
    0x0e, 0x6c, 0x68, 0x22, 0x23, 0x6e, 0x1d, 0xaa,
    0xfb, 0x94, 0xff, 0xe0, 0xc5, 0xda, 0x05, 0xd9,
    0x47, 0x6b, 0xe0, 0x28, 0xad, 0x7c, 0x1d, 0x81};
const int cbcKey2[] = {0x14, 0x0b, 0x41, 0xb2, 0x2a, 0x29, 0xbe, 0xb4, 0x06, 0x1b,
      0xda, 0x66, 0xb6, 0x74, 0x7e, 0x14};
unsigned char cbcCipher2[] = {0x5b, 0x68, 0x62, 0x9f, 0xeb, 0x86, 0x06, 0xf9, 0xa6,
      0x66, 0x76, 0x70, 0xb7, 0x5b, 0x38, 0xa5, 0xb4, 0x83, 0x2d, 0x0f, 0x26,
      0xe1, 0xab, 0x7d, 0xa3, 0x32, 0x49, 0xde, 0x7d, 0x4a, 0xfc, 0x48, 0xe7,
      0x13, 0xac, 0x64, 0x6a, 0xce, 0x36, 0xe8, 0x72, 0xad, 0x5f, 0xb8, 0xa5,
      0x12, 0x42, 0x8a, 0x6e, 0x21, 0x36, 0x4b, 0x0c, 0x37, 0x4d, 0xf4, 0x55,
      0x03, 0x47, 0x3c, 0x52, 0x42, 0xa2, 0x53};

const int ctrKey1[] = {0x36, 0xf1, 0x83, 0x57, 0xbe, 0x4d, 0xbd, 0x77, 0xf0, 0x50,
      0x51, 0x5c, 0x73, 0xfc, 0xf9, 0xf2};
unsigned char ctrCipher1[] = {0x69, 0xdd, 0xa8, 0x45, 0x5c, 0x7d, 0xd4, 0x25, 0x4b,
      0xf3, 0x53, 0xb7, 0x73, 0x30, 0x4e, 0xec, 0x0e, 0xc7, 0x70, 0x23, 0x30,
      0x09, 0x8c, 0xe7, 0xf7, 0x52, 0x0d, 0x1c, 0xbb, 0xb2, 0x0f, 0xc3, 0x88,
      0xd1, 0xb0, 0xad, 0xb5, 0x05, 0x4d, 0xbd, 0x73, 0x70, 0x84, 0x9d, 0xbf,
      0x0b, 0x88, 0xd3, 0x93, 0xf2, 0x52, 0xe7, 0x64, 0xf1, 0xf5, 0xf7, 0xad,
      0x97, 0xef, 0x79, 0xd5, 0x9c, 0xe2, 0x9f, 0x5f, 0x51, 0xee, 0xca, 0x32,
      0xea, 0xbe, 0xdd, 0x9a, 0xfa, 0x93, 0x29};

const int ctrKey2[] = {0x36, 0xf1, 0x83, 0x57, 0xbe, 0x4d, 0xbd, 0x77, 0xf0, 0x50,
      0x51, 0x5c, 0x73, 0xfc, 0xf9, 0xf2};
unsigned char ctrCipher2[] = {0x77, 0x0b, 0x80, 0x25, 0x9e, 0xc3, 0x3b, 0xeb, 0x25,
      0x61, 0x35, 0x8a, 0x9f, 0x2d, 0xc6, 0x17, 0xe4, 0x62, 0x18, 0xc0, 0xa5,
      0x3c, 0xbe, 0xca, 0x69, 0x5a, 0xe4, 0x5f, 0xaa, 0x89, 0x52, 0xaa, 0x0e,
      0x31, 0x1b, 0xde, 0x9d, 0x4e, 0x01, 0x72, 0x6d, 0x31, 0x84, 0xc3, 0x44,
      0x51};

static void cbc1(void);
static void cbc2(void);
static void ctr1(void);
static void ctr2(void);

int main()
{
   cbc1();
   cbc2();
   ctr1();
   ctr2();
   return 0;
}

static void cbc1(void)
{
   byte key[AES::DEFAULT_KEYLENGTH];
   for (int i = 0; i < (int)sizeof(key); i++)
   {
      key[i] = cbcKey1[i];
   }

   byte iv[AES::BLOCKSIZE];
   for (int i = 0; i < (int)sizeof(iv); i++)
   {
      iv[i] = cbcCipher1[i];
   }

   string cipher((const char *)(&(cbcCipher1[AES::BLOCKSIZE])),
      sizeof(cbcCipher1) - AES::BLOCKSIZE);
   string encoded, recovered;

   /*********************************\
      \*********************************/

   // Pretty print key
   encoded.clear();
   StringSource(key, sizeof(key), true, new HexEncoder(new StringSink(encoded)) // HexEncoder
      );// StringSource
   cout << "key: " << encoded << endl;

   // Pretty print iv
   encoded.clear();
   StringSource(iv, sizeof(iv), true, new HexEncoder(new StringSink(encoded)) // HexEncoder
      );// StringSource
   cout << "iv: " << encoded << endl;

   /*********************************\
      \*********************************/
   // Pretty print
   encoded.clear();
   StringSource(cipher, true, new HexEncoder(new StringSink(encoded)) // HexEncoder
      );// StringSource
   cout << "cipher text: " << encoded << endl;

   /*********************************\
      \*********************************/

   try
   {
      CBC_Mode<AES>::Decryption d;
      d.SetKeyWithIV(key, sizeof(key), iv);

      // The StreamTransformationFilter removes
      //  padding as required.
      StringSource s(cipher, true,
         new StreamTransformationFilter(d, new StringSink(recovered)) // StreamTransformationFilter
            );// StringSource

      cout << "recovered text: " << recovered << endl;
   } catch (const CryptoPP::Exception& e)
   {
      cerr << e.what() << endl;
      exit(1);
   }

   /*********************************\
   \*********************************/
}

static void cbc2(void)
{
   byte key[AES::DEFAULT_KEYLENGTH];
   for (int i = 0; i < (int)sizeof(key); i++)
   {
      key[i] = cbcKey2[i];
   }

   byte iv[AES::BLOCKSIZE];
   for (int i = 0; i < (int)sizeof(iv); i++)
   {
      iv[i] = cbcCipher2[i];
   }

   string cipher((const char *)(&(cbcCipher2[AES::BLOCKSIZE])),
      sizeof(cbcCipher2) - AES::BLOCKSIZE);
   string encoded, recovered;

   /*********************************\
      \*********************************/

   // Pretty print key
   encoded.clear();
   StringSource(key, sizeof(key), true, new HexEncoder(new StringSink(encoded)) // HexEncoder
      );// StringSource
   cout << "key: " << encoded << endl;

   // Pretty print iv
   encoded.clear();
   StringSource(iv, sizeof(iv), true, new HexEncoder(new StringSink(encoded)) // HexEncoder
      );// StringSource
   cout << "iv: " << encoded << endl;

   /*********************************\
      \*********************************/
   // Pretty print
   encoded.clear();
   StringSource(cipher, true, new HexEncoder(new StringSink(encoded)) // HexEncoder
      );// StringSource
   cout << "cipher text: " << encoded << endl;

   /*********************************\
      \*********************************/

   try
   {
      CBC_Mode<AES>::Decryption d;
      d.SetKeyWithIV(key, sizeof(key), iv);

      // The StreamTransformationFilter removes
      //  padding as required.
      StringSource s(cipher, true,
         new StreamTransformationFilter(d, new StringSink(recovered)) // StreamTransformationFilter
            );// StringSource

      cout << "recovered text: " << recovered << endl;
   } catch (const CryptoPP::Exception& e)
   {
      cerr << e.what() << endl;
      exit(1);
   }

   /*********************************\
   \*********************************/
}

static void ctr1(void)
{
   byte key[AES::DEFAULT_KEYLENGTH];
   for (int i = 0; i < (int)sizeof(key); i++)
   {
      key[i] = ctrKey1[i];
   }

   byte iv[AES::BLOCKSIZE];
   for (int i = 0; i < (int)sizeof(iv); i++)
   {
      iv[i] = ctrCipher1[i];
   }

   string cipher((const char *)(&(ctrCipher1[AES::BLOCKSIZE])),
      sizeof(ctrCipher1) - AES::BLOCKSIZE);
   string encoded, recovered;

   /*********************************\
   \*********************************/

   // Pretty print key
   encoded.clear();
   StringSource(key, sizeof(key), true,
      new HexEncoder(
         new StringSink(encoded)
      ) // HexEncoder
   ); // StringSource
   cout << "key: " << encoded << endl;

   // Pretty print iv
   encoded.clear();
   StringSource(iv, sizeof(iv), true,
      new HexEncoder(
         new StringSink(encoded)
      ) // HexEncoder
   ); // StringSource
   cout << "iv: " << encoded << endl;

   /*********************************\
   \*********************************/

   // Pretty print
   encoded.clear();
   StringSource(cipher, true,
      new HexEncoder(
         new StringSink(encoded)
      ) // HexEncoder
   ); // StringSource
   cout << "cipher text: " << encoded << endl;

   /*********************************\
   \*********************************/

   try
   {
      CTR_Mode< AES >::Decryption d;
      d.SetKeyWithIV(key, sizeof(key), iv);

      // The StreamTransformationFilter removes
      //  padding as required.
      StringSource s(cipher, true,
         new StreamTransformationFilter(d,
            new StringSink(recovered)
         ) // StreamTransformationFilter
      ); // StringSource

      cout << "recovered text: " << recovered << endl;
   }
   catch(const CryptoPP::Exception& e)
   {
      cerr << e.what() << endl;
      exit(1);
   }

   /*********************************\
   \*********************************/
}

static void ctr2(void)
{
   byte key[AES::DEFAULT_KEYLENGTH];
   for (int i = 0; i < (int)sizeof(key); i++)
   {
      key[i] = ctrKey2[i];
   }

   byte iv[AES::BLOCKSIZE];
   for (int i = 0; i < (int)sizeof(iv); i++)
   {
      iv[i] = ctrCipher2[i];
   }

   string cipher((const char *)(&(ctrCipher2[AES::BLOCKSIZE])),
      sizeof(ctrCipher2) - AES::BLOCKSIZE);
   string encoded, recovered;

   /*********************************\
   \*********************************/

   // Pretty print key
   encoded.clear();
   StringSource(key, sizeof(key), true,
      new HexEncoder(
         new StringSink(encoded)
      ) // HexEncoder
   ); // StringSource
   cout << "key: " << encoded << endl;

   // Pretty print iv
   encoded.clear();
   StringSource(iv, sizeof(iv), true,
      new HexEncoder(
         new StringSink(encoded)
      ) // HexEncoder
   ); // StringSource
   cout << "iv: " << encoded << endl;

   /*********************************\
   \*********************************/

   // Pretty print
   encoded.clear();
   StringSource(cipher, true,
      new HexEncoder(
         new StringSink(encoded)
      ) // HexEncoder
   ); // StringSource
   cout << "cipher text: " << encoded << endl;

   /*********************************\
   \*********************************/

   try
   {
      CTR_Mode< AES >::Decryption d;
      d.SetKeyWithIV(key, sizeof(key), iv);

      // The StreamTransformationFilter removes
      //  padding as required.
      StringSource s(cipher, true,
         new StreamTransformationFilter(d,
            new StringSink(recovered)
         ) // StreamTransformationFilter
      ); // StringSource

      cout << "recovered text: " << recovered << endl;
   }
   catch(const CryptoPP::Exception& e)
   {
      cerr << e.what() << endl;
      exit(1);
   }

   /*********************************\
   \*********************************/
}
