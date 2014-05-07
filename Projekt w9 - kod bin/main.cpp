
#define CRYPTOPP_ENABLE_NAMESPACE_WEAK 1
#define _CRT_SECURE_NO_DEPRECATE
#define CRYPTOPP_DEFAULT_NO_DLL

//#include "C:/cryptopp/include/cryptopp/dll.h"
#include <cstdio>

#include <iostream>
using std::cout;
using std::cerr;
using std::endl;

#include <string>
using std::string;

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

	//std::cout << digest << std::endl;  
	
	//digest zawiera hasha message
	
	CryptoPP::HexEncoder encoder;//
	
	//CryptoPP::BaseN_Encoder encoder;
	std::string output;
	encoder.Attach( new CryptoPP::StringSink( output ) );
	encoder.Put( digest, sizeof(digest) );
	encoder.MessageEnd();
	
	std::string output_bin;
	output_bin = GetBinaryStringFromHexString(output);

	//std::cout << output << std::endl;  
	//std::cout << output.length() << std::endl; 
//std::cout << output_bin << std::endl; 
	//std::cout << output_bin.length() << std::endl;
	//std::cout << "" << std::endl;
	
//	char str11[] = "000100010011111";
	char * rho;
	const char *coutput_bin = output_bin.c_str();
  	rho = strchr(coutput_bin,'1');
  	
	//std::cout << rho-coutput_bin+1 <<std::endl;
	int i = rho-coutput_bin+1;
	
	return i;
	
	//return std::string((char*)digest);
}


int main(int argc, char** argv) {
	
	int B[40];
	
	FILE *fp;
    FILE *out;
    char nazwa_wej[50];
    char c;
    string wyraz;
    int i = 0;
    
    cout << "Podaj nazwê pliku tekstowego" <<endl;
    cin >> nazwa_wej;

	fp = fopen (nazwa_wej, "r");
    if (fp == NULL)
    {
         cout << "Error opening file" << endl;  
    }
    
        else 
    {         
           while((c=fgetc(fp)) != EOF)
           {                                          
                            if ((c>='a' && c<='z') || (c>='A' && c<='Z'))
                            {
                            		wyraz = wyraz + c;
                                    //cout << wyraz <<endl;
                                    //c1=fgetc(fp);
                                    //c1=crypt(c1);  
                                    //cout << c1 <<endl;                              
                            }
                            else 
                            {
                            	i = crypt(wyraz);
                            	B[i - 1] = 1;//numerowanie od 0
                            	//cout << B[i] <<endl;
                            	wyraz = "";
                            	i = 0;
                        	}                                 

           }
           i = crypt(wyraz);
           B[i-1] = 1;//numerowanie od 0
           int fclose(FILE * fp);
           int fclose(FILE * out);
           
           	int k = 0;
           	while(B[k] == 1)
           	{
           		k++;//dodajemy do ostatniego 1, bo potêga musi byæ od 1 a nie od 0
           	}
    		cout<<"Potêga :"<<k<<endl;
           
    }

  //system("pause");
	
	//std::string message1 = "aaa";
	//std::string message2 = "aab";
	//std::string message3 = "aaddddd";
	//std::string message4 = "aaa";

	//crypt(message1);
	//crypt(message2);
	//crypt(message3);
	//crypt(message4);
	//crypt("misie");
	
	return 0;
}

