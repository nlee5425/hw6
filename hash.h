#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
        // Add your code here
        unsigned long long w[5];
        for ( int i = 0 ;  i < 5 ; ++i ) { //make sure to change all values in the array to 0
            w[i] = 0;
        }
        unsigned long long conversion = 0;
        int multiply = 0;
				unsigned int i = 0; //integer to compare to the string you ar elooking at
				int wincrement = 4; //signifiying where to put in the w array
				int sixincrement = 0;
				int strincrement = k.size() - 1;
        while ( i < k.size()) {
						if (multiply == 0 ) { //if the multiple is 0 then only incrememnt and then multiply
							conversion += letterDigitToNumber(k[strincrement]);
							++multiply;
							multiply *= 36;
							--strincrement;
							++i;

						}
						else { //else, change multiply to 36
            	conversion += (multiply * (letterDigitToNumber(k[strincrement])));
							multiply *= 36;
							--strincrement;
							++i;
						}
						++sixincrement;
            if ( sixincrement == 6 ) { //if the amount of letters reached six, add to w, then move to next w
							w[wincrement] = conversion;
							--wincrement; 
              conversion = 0;
              multiply = 0;
							sixincrement = 0;
            }
        }
				if ( sixincrement < 6 ) { //if amount of digits was less than 6 to begin with, add to w
					w[wincrement] = conversion;
        }
        unsigned long long ans = 0;
        for ( unsigned int i = 0 ; i < 5 ; ++i ) { //multiply the set random values with your w
						std::cout << w[i] << std::endl;
            ans += (w[i] * rValues[i]);
        }
        return ans;
    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it 
        //difference from capital letter to lowercase: lowercase a = 97, uppercase A = 65
        if ( letter >= 65 && letter <= 90 ) { //if it is an uppercase letter, transform into lowercase
            letter += 32;
        }
        int number = 0;
        if ( letter >= 48 && letter <= 57 ) { //if letter is a number, transform into corresponding digit
            number = letter - 22;
        }
        else if ( letter >= 97 &&letter <= 122 ) {
            number = letter - 97;
        }
        return number;
    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
