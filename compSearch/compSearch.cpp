#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

struct CompSearch
{
    char* word;
    int tab[256] = {};
    
    bool searchBM(const char* key){
        int keySize = strlen(key);
        int wordSize = strlen(word);
        
  
        for (int i = 0; i < 256; i++){
            tab[i] = keySize;
        }
        
        for (int i = 0; i < keySize; i++){
            tab[key[i]] = keySize - 1 - i;
        }
        
        if (wordSize < keySize){
            cout << "WRONG!" << endl;
            return false;
        }
        
        int i = keySize - 1; 
        int j = keySize - 1;  
        
        while (i < wordSize) {
            if (word[i] == key[j]) {
                if (j == 0) {
                    cout << "Found at position: " << i << endl;
                    return true;
                }
                i--;
                j--;
            } else {
            
                int skip = tab[word[i]];
                i += max(skip, keySize - j);
                j = keySize - 1;
            }
        }
        
        return false;
    }
    
    bool searchKMP(const char* key){
        int keySize = strlen(key);
        int wordSize = strlen(word);
        
        if (wordSize < keySize){
            cout << "WRONG!" << endl;
            return false;
        }
        
        if (keySize == 0) {
            cout << "Found at position: 0" << endl;
            return true;
        }
        

        int* prefix = new int[keySize];
        prefix[0] = 0;
        int k = 0;
        
        for (int i = 1; i < keySize; i++) {
            while (k > 0 && key[k] != key[i]) {
                k = prefix[k - 1];
            }
            if (key[k] == key[i]) {
                k++;
            }
            prefix[i] = k;
        }
        
    
        int j = 0;  
        
        for (int i = 0; i < wordSize; i++) {
            while (j > 0 && word[i] != key[j]) {
                j = prefix[j - 1];
            }
            
            if (word[i] == key[j]) {
                j++;
            }
            
            if (j == keySize) {
                cout << "Found at position: " << i - keySize + 1 << endl;
                delete[] prefix;
                return true;
            }
        }
        
        delete[] prefix;
        return false;
    }
    
    CompSearch(const char* w){
        word = new char[strlen(w)+1];
        strcpy(word, w);   
    }
    
    ~CompSearch(){
        delete[] word;
    }
};

int main(){
    CompSearch cs("police i swear to god not");
    
    cout << "Boyer-Moore search:" << endl;
    cs.searchBM("god") ? cout << "True" << endl : cout << "False" << endl;
    cs.searchBM("devil") ? cout << "True" << endl : cout << "False" << endl;
    
    cout << "\nKMP search:" << endl;
    cs.searchKMP("god") ? cout << "True" << endl : cout << "False" << endl;
    cs.searchKMP("devil") ? cout << "True" << endl : cout << "False" << endl;
    cs.searchKMP("police") ? cout << "True" << endl : cout << "False" << endl;
    cs.searchKMP("swear") ? cout << "True" << endl : cout << "False" << endl;
    
    return 0;
}
