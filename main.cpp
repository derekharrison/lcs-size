//
//  main.cpp
//  lcs-size
//
//  Created by Derek Harrison on 24/10/2021.
//

#include <cstdlib>
#include <iostream>
#include <vector>
#include <time.h>
#include <string>

#include <iostream>
#include <string>

typedef struct memo_table {
    bool is_set;
    int size;
} m_table;

int lcs(std::string& x, std::string& y, int jx, int jy, m_table** memo_table) {
    
    int result = 0;

    //Compute longest common subsequence of substring
    if(jx > 0 && jy > 0) {
        
        //Get results from memo table if available
        if(memo_table[jx - 1][jy - 1].is_set) {
            return memo_table[jx - 1][jy - 1].size;
        }
        
        if(x[jx - 1] != y[jy - 1]) {
            int size1 = lcs(x, y, jx - 1, jy, memo_table);
            int size2 = lcs(x, y, jx, jy - 1, memo_table);

            if(size1 > size2) {
                result = result + size1;
            }
            else {
                result = result + size2;
            }
        }
        
        if(x[jx - 1] == y[jy - 1]) {
            result = result + 1;
            result = result + lcs(x, y, jx - 1, jy - 1, memo_table);
        }
        
        //Add results to memo table
        memo_table[jx - 1][jy - 1].is_set = true;
        memo_table[jx - 1][jy - 1].size = result;
    }
    
    return result;
}

int longest_common_subs(std::string& x, std::string& y) {
    int max_size = 0;
    int len1 = (int) x.length();
    int len2 = (int) y.length();
    
    //Compute max length input strings
    if(len1 < len2) {
        max_size = len2;
    }
    else {
        max_size = len1;
    }
    
    //Initialize memo table
    m_table** memo_table = new m_table*[max_size];
    for(int i = 0; i < max_size; ++i) {
        memo_table[i] = new m_table[max_size];
    }
    
    for(int i = 0; i < max_size; ++i) {
        for(int j = 0; j < max_size; ++j) {
            memo_table[i][j].is_set = false;
        }
    }
    
    //Compute longest common subsequence
    int longest_cs = lcs(x, y, len1, len2, memo_table);
    
    return longest_cs;
}

int main(int argc, const char * argv[]) {
    
    //Input
    std::string x = "ACCGGTCGAGTGCGCGGAAGCCGGCCGAA";
    std::string y = "GTCGTTCGGAATGCCGTTGCTCTGTAAA";
    std::string ref = "GTCGTCGGAAGCCGGCCGAA";
    
    //Compute longest comon subsequence
    int lcs_size = longest_common_subs(x, y);
    
    //Print results
    std::cout << "lcs size: " << lcs_size << std::endl;
    std::cout << "lcs size ref: " << (int) ref.size() << std::endl;
    std::cout << "done" << std::endl;
    
    return 0;
}
