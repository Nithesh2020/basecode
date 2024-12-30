// Online C++ compiler to run C++ program online
#include <iostream>
using namespace std;
string XORop(string a,string b)
{
    string result = "";
    int i = 0;
    int n = b.length();
    // Traverse all bits, if bits are 
    // same, then XOR is 0, else 1 
    for(i = 0;i < n;i++)
    {
        if(a[i]==b[i])
        {
            result += "0";
        }
        else 
        {
            result += "1";
        }
    }
    return result;
}

// Performs Modulo-2 division 
string mod2div(string dividend, string divisor) 
{
    // Number of bits to be XORed at a time. 
    int pick = divisor.length(); 
    string tmp = dividend.substr(0, pick); 
    int n = dividend.length();
    while (pick < n) { 
        if (tmp[0] == '1') 
        {
            tmp = XORop(divisor, tmp) + dividend[pick];
        }
        else
        {
            tmp = XORop(std::string(pick, '0'), tmp) + dividend[pick]; 
        }
        pick +=1;
    }
    return tmp;
}

void encodeData(string data, string key) 
{ 
    int l_key = key.length(); 
    string appended_data = (data + std::string(l_key - 1, '0')); 
    string remainder = mod2div(appended_data, key); 
    string codeword = data + remainder; 
    cout << "Remainder : " << remainder << "\n"; 
    cout << "Encoded Data (Data + Remainder) :" << codeword<< "\n"; 
} 
// checking if the message received by receiver is correct 
// or not. If the remainder is all 0 then it is correct, 
// else wrong. 
void receiver(string data, string key) 
{ 
    string currxor = mod2div(data.substr(0, key.size()), key); 
    int curr = key.size(); 
    while (curr != data.size()) { 
        if (currxor.size() != key.size()) { 
            currxor.push_back(data[curr++]); 
        } 
        else { 
            currxor = mod2div(currxor, key); 
        } 
    } 
    if (currxor.size() == key.size()) { 
        currxor = mod2div(currxor, key); 
    } 
    if (currxor.find('1') != string::npos) { 
        cout << "there is some error in data" << endl; 
    } 
    else { 
        cout << "correct message received" << endl; 
    } 
} 
string ext(int k,char c){
    int i = 0;
    string result = "";
    for(i = 0;i<k;i++){
        result += c;
    }
    return result;
}
int main() {
    string data = "100100"; 
    string key = "1101"; 
    cout << "Sender side..." << endl; 
    encodeData(data, key); 
    cout << "\nReceiver side..." << endl; 
    string extd = ext(key.size()-1,'0');
    cout << extd << endl;
    string extended_data =  data + extd;
    cout << extended_data << endl;
    string tmp = mod2div(extended_data,key);
    cout <<tmp << endl;
    string tmp2 = data + tmp;
    cout << tmp2<<endl;
    receiver(tmp2, key); 
    return 0; 
}
