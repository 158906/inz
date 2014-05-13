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

		int GetIntegerFromBinaryString (string sBin)
		{
			char cc;
			int sReturn = 0;
			for (int i = 0; i < sBin.length (); ++i)
			{	
				string sym(1,sBin[i]);
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

void crypt(string message, int &i, int &output_int_resztaDziel){
	CryptoPP::SHA3_512 hash; 
	byte digest[ CryptoPP::SHA512::DIGESTSIZE ];
			
	hash.CalculateDigest( digest, (byte*)message.c_str(), message.length() );
	CryptoPP::HexEncoder encoder;

	std::string output;
	encoder.Attach( new CryptoPP::StringSink( output ) );
	encoder.Put( digest, sizeof(digest) );
	encoder.MessageEnd();
	
	std::string output_bin;
	output_bin = GetBinaryStringFromHexString(output);
	
	std::string output_bin_wynikDziel;
	std::string output_bin_resztaDziel;
	output_bin_wynikDziel = output_bin.substr(0, output_bin.length()-6); //na sztywno dla m=64
	output_bin_resztaDziel = output_bin.substr(output_bin.length()-6, 6);//m = 64
	
	output_int_resztaDziel = GetIntegerFromBinaryString(output_bin_resztaDziel);
	char * rho;
	const char *coutput_bin = output_bin_wynikDziel.c_str();
  	rho = strchr(coutput_bin,'1');
	i = rho-coutput_bin; 
}


int main(int argc, char** argv) {
	
	int B[64][32]={0};
	
	float phi = 0.77351;
	
	FILE *fp;
    FILE *out;
    char nazwa_wej[50];
    char c;
    string wyraz;
    int i = 0;
    int alpha = 0;
    
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
                            }
                            else 
                            {
                            	crypt(wyraz, i, alpha);                           	
                            	B[alpha][i] = 1;
                            	wyraz = "";
                            	i = 0;
                            	alpha = 0;
                        	}                                 

           }
           crypt(wyraz, i, alpha);
           B[alpha][i] = 1;
           int fclose(FILE * fp);
           int fclose(FILE * out);
           
           int R;
           int S = 0;
           
           	for (int k = 0; k < 64; k++)
           	{
           		R = 0;
           		while((B[k][R] == 1) && (R < 32))
           		{
           			R++;
           		}
           		S = S+R;
           	}
           	
           	/////////////////////////////////////WYŒWIETLANIE BITMAPY
        //   	for (int q = 0; q < 64; q++)
		//{
		//	for (int x = 0; x < 32; x++)
		//	{
		//	cout << B[q][x];
		//	}
		//	cout << "\n";
		//}
		////////////////////////////////////////////KONIEC WYŒWIETLANIA
		
           	
           	//cout<<"phi = :"<<phi<<endl;
           	//cout<<"S = :"<<S<<endl;
           	//cout<<"R = :"<<R<<endl;
           	//cout<<"S/64 = :"<<S/64.0<<endl;
           	
           	int n = (1.0/phi)*64.0*pow(2.0,(S/64.0));
           	
    		cout<<"n = :"<<n<<endl;
           
    }
	
	return 0;
}

