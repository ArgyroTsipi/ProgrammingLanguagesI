#include <iostream>
#include <fstream>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <cmath>

using namespace std;

int main(int argc, const char * argv[]) {

/****************************************** READ FROM FILE *********************************************/
    ifstream inFile(argv[1]);
    string mystring;
    char mychar;
    
    int pinakasH[26];
    char pinakas[10000];
    int freqBuff[26][26] = {0};
    double givenBuff[26] = {0.08167,0.01492,0.02782,0.04253,0.12702,0.02228,0.02015,0.06094,0.06966,0.00153,0.00772,0.04025,0.02406,0.06749,0.07507,0.01929,0.00095,0.05987,0.06327,0.09056,0.02758,0.00978,0.02360,0.00150,0.01974,0.00074};
    char abcBuff[26] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
    char ABCBuff[26] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
    if(inFile.is_open()){
        while(inFile){
            mychar = inFile.get();
            mystring += mychar;
        }
        
      //  cout << mystring<< endl; //OK
    }
/************************************************** ROTN *****************************************************/
    char a;
    string bigArr[26];
    int strlength = mystring.length() -1;
    
    for(int j=0; j<25; j++){
        for(int i=0; i< strlength; i++){
            
            // check if it's a letter or not
            if(isalpha(mystring[i])){
                
                if(mystring[i] >= 65 && mystring[i] <= 90){
                    a = ((mystring[i]+j-65)%26+65);
                }
                    else{
                        a = ((mystring[i]+j-97)%26+97);
                    }
            
                pinakas[i] = a;
                
                for(int k=0; k<26; k++){
                     if((pinakas[i] == abcBuff[k]) || (pinakas[i] == ABCBuff[k])){
                         freqBuff[j][k]++;
                         //cout << freqBuff[j][k] << " ";
                     }
                 }
            }
            else{
                pinakas[i] = mystring[i];
                
            }
           // cout<< pinakas[i] << " ";// OK
          
        }
        bigArr[j] = pinakas;
       // cout << bigArr[j] << " "; //OK
 
    //still in J loop
/*************************************** CALCULATE H ARRAY *******************************************/
        int sum=0;
            for(int w = 0; w<26; w++){
                sum += freqBuff[j][w]*log(givenBuff[w]);
                freqBuff[j][w] = 0;
            }
        pinakasH[j] = -1*sum;
       // cout << pinakasH[j] << endl;
    } //end of j loop
   
/***************************************** FIND MINIMUM H ************************************************/
    int length = sizeof(pinakasH)/sizeof(pinakasH[0]);
    int min = pinakasH[0];
    for(int i=0; i<length-1; i++){
        if(pinakasH[i] < min){
            min = pinakasH[i];
        }
    }
 
/*********************************** PRINT DECRYPTED MESSAGE *************************************/
    for(int i =0; i<26; i++){

        if(pinakasH[i] == min){
           cout << bigArr[i] << "\n";
            return 0;
        }
    }
}

