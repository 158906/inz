
#define CRYPTOPP_ENABLE_NAMESPACE_WEAK 1
#define _CRT_SECURE_NO_DEPRECATE
#define CRYPTOPP_DEFAULT_NO_DLL

//#include "C:/cryptopp/include/cryptopp/dll.h"
#include <iostream>
using std::cout;
using std::cerr;
using std::endl;

#include <string>
using std::string;
#include <cstdlib>
#include <cmath>

#include "hex.h"
using CryptoPP::HexEncoder;//
using CryptoPP::HexDecoder;//

#include "cryptlib.h"
using CryptoPP::BufferedTransformation;
using CryptoPP::AuthenticatedSymmetricCipher;

#include "secblock.h"
using CryptoPP::SecByteBlock;

#include "filters.h"
using CryptoPP::StringSink;
using CryptoPP::StringSource;
using CryptoPP::AuthenticatedEncryptionFilter;
using CryptoPP::AuthenticatedDecryptionFilter;

#include "aes.h"
using CryptoPP::AES;

#include "eax.h"
using CryptoPP::EAX;

#include "md5.h"
#include "sha.h"
#include "sha3.h"
//using CryptoPP::MD5;

#include "basecode.h"
#include "base32.h"
//http://mcs.une.edu.au/doc/cryptopp-doc-5.6.2/sha3_8h_source.html
using namespace std;
/*
int char2int(char input)
{
  if(input >= '0' && input <= '9')
    return input - '0';
  if(input >= 'A' && input <= 'F')
    return input - 'A' + 10;
  if(input >= 'a' && input <= 'f')
    return input - 'a' + 10;
  throw Exception("Invalid input string");
}

void hex2bin(const char* src, char* target)
{
  while(*src && src[1])
  {
    *(target++) = char2int(*src)*16 + char2int(src[1]);
    src += 2;
  }
}
*/

		int GetIntegerFromBinaryString (string sBin)
		{
			char cc;
			
			int sReturn = 0;
			for (int i = 0; i < sBin.length (); ++i)
			{	
				//char c = sBin[i];
				//cc = sBin[i];
				string sym(1,sBin[i]);
				//string ss(1,sBin[i]);
				//char s=sBin[i];
				//std::cout << sym << " - " << itoa(pow(2,(sBin.length ()-i-1)), (char*)ss.c_str(), 10) << std::endl;  
				sReturn = sReturn + atoi(sym.c_str())*pow(2,(sBin.length ()-i-1));
			}
			return sReturn;
		}


		string GetBinaryStringFromHexString (string sHex)
		{
			string sReturn = "";
			for (int i = 0; i < sHex.length (); ++i)
			{
				switch (sHex [i])
				{
					case '0': sReturn.append ("0000"); break;
					case '1': sReturn.append ("0001"); break;
					case '2': sReturn.append ("0010"); break;
					case '3': sReturn.append ("0011"); break;
					case '4': sReturn.append ("0100"); break;
					case '5': sReturn.append ("0101"); break;
					case '6': sReturn.append ("0110"); break;
					case '7': sReturn.append ("0111"); break;
					case '8': sReturn.append ("1000"); break;
					case '9': sReturn.append ("1001"); break;
					case 'A': sReturn.append ("1010"); break;
					case 'B': sReturn.append ("1011"); break;
					case 'C': sReturn.append ("1100"); break;
					case 'D': sReturn.append ("1101"); break;
					case 'E': sReturn.append ("1110"); break;
					case 'F': sReturn.append ("1111"); break;
				}
			}
			return sReturn;
		}

int crypt(std::string message) {
	CryptoPP::SHA3_256 hash; 
	byte digest[ CryptoPP::SHA::DIGESTSIZE ];
		
	hash.CalculateDigest( digest, (byte*)message.c_str(), message.length() );
	std::cout << digest << std::endl;  
	
	//digest zawiera hasha message
	
	CryptoPP::HexEncoder encoder;//
	
	//CryptoPP::Base32Encoder encoder;
	std::string output;
	encoder.Attach( new CryptoPP::StringSink(output ) );
	encoder.Put( digest, sizeof(digest) );
	encoder.MessageEnd();
	
	std::cout <<"enc: " << output << std::endl; 
	
	std::string output_bin;
	std::string output_bin_wynikDziel;
	std::string output_bin_resztaDziel;
	int output_int_resztaDziel;
	output_bin = GetBinaryStringFromHexString(output);
	output_bin_wynikDziel = output_bin.substr(0, output_bin.length()-6);
	output_bin_resztaDziel = output_bin.substr(output_bin.length()-6, 6);
	
	output_int_resztaDziel = GetIntegerFromBinaryString(output_bin_resztaDziel);
	
	//std::cout << output.length() << std::endl; 
	std::cout << output_bin << std::endl; 
	std::cout << output_bin_wynikDziel << std::endl; 
	std::cout << output_bin_resztaDziel << std::endl; 
	std::cout << output_int_resztaDziel << std::endl; 
	//std::cout << output_bin.length() << std::endl;
	std::cout << "" << std::endl;
	
//std::string digest;

//CryptoPP::StringSource foo(message, true,
//   new CryptoPP::HashFilter(hash,
//      new CryptoPP::HexEncoder (
//         new CryptoPP::StringSink(digest))));

//std::cout << digest << std::endl;

/*	
std::string decoded;
StringSource ss(output, new HexDecoder( new StringSink(decoded) ) // HexDecoder
); // StringSource

CryptoPP::HexDecoder decoder;
decoder.Attach( new CryptoPP::StringSink( decoded ) );
decoder.Put( (byte*)output.data(), output.size() );
decoder.MessageEnd();
std::cout << decoded << std::endl; 
*/
	
	
	/*byte iv[CryptoPP::AES::BLOCKSIZE];
memset(iv, 0x00, CryptoPP::AES::BLOCKSIZE);

CryptoPP::AES::Encryption encrypt(reinterpret_cast<const byte *>(digest), CryptoPP::AES::DEFAULT_KEYLENGTH);
CryptoPP::CBC_Mode_ExternalCipher::Encryption cbc_encrypt(encrypt, iv);

std::string ciphertext;
CryptoPP::StreamTransformationFilter encryptor(cbc_encrypt,
    new CryptoPP::StringSink(ciphertext));
encryptor.Put(reinterpret_cast<const unsigned char *>(message.c_str()), message.length() + 1);
encryptor.MessageEnd();

std::cout << ciphertext << std::endl;

std::string encoded;
CryptoPP::StringSource(ciphertext, true, 
    new CryptoPP::BaseN_Encoder(new CryptoPP::StringSink(encoded)));
	
std::cout << encoded << std::endl;	
	*/
	return 0;
	
	//return std::string((char*)digest);
}



int main(int argc, char** argv) {
	std::string message1 = "aaa";
	std::string message2 = "aab";
	std::string message3 = "aaddddd";
	std::string message4 = "aaa";

	crypt(message1);
	crypt(message2);
	crypt(message3);
	crypt(message4);
	crypt("misie");
	
	return 0;
}

