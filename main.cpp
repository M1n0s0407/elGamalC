#include <iostream>
#include <vector>
#include <cmath>
#include <boost/multiprecision/cpp_int.hpp> // Include the Boost Multiprecision library

using namespace std;
using namespace boost::multiprecision; // Use Boost Multiprecision

// Function to convert a string of digits to a cpp_int
cpp_int stringToNumber(const string &digits)
{
    cpp_int result = 0;

    // Iterate through each character in the string
    for (char digit : digits)
    {
        // Check if the character is a valid digit
        if (isdigit(digit))
        {
            // Convert the character to an integer and update the result
            result = result * 10 + (digit - '0');
            // cout << result << endl;
        }
        else
        {
            // If a non-digit character is encountered, return an error value or handle it as needed
            cerr << "Error: Non-digit character found in input." << endl;
            return -1;
        }
    }

    return result;
}

bool isPrime(const cpp_int &n)
{
    if (n <= 1)
        return false;
    if (n <= 3)
        return true;
    if (n % 2 == 0 || n % 3 == 0)
        return false;

    for (cpp_int i = 5; i * i <= n; i += 6)
    {
        if (n % i == 0 || n % (i + 2) == 0)
            return false;
    }

    return true;
}

cpp_int modPow(const cpp_int &base, const cpp_int &exponent, const cpp_int &modulus)
{
    cpp_int result = 1;
    cpp_int b = base;
    cpp_int e = exponent;
    while (e > 0)
    {
        if (e % 2 == 1)
        {
            result = (result * b) % modulus;
        }
        b = (b * b) % modulus;
        e /= 2;
    }
    return result;
}

cpp_int findPrimitiveRoot(const cpp_int &p)
{
    cpp_int phi = p - 1;
    vector<cpp_int> primeFactors;

    // Find the prime factors of phi
    cpp_int temp = phi;
    for (cpp_int i = 2; i * i <= temp; ++i)
    {
        if (temp % i == 0)
        {
            primeFactors.push_back(i);
            std::cout << "Found prime factor: " << i << std::endl;
            while (temp % i == 0)
            {
                temp /= i;
            }
        }
    }
    if (temp > 1)
    {
        primeFactors.push_back(temp);
        std::cout << "Found prime factor: " << temp << std::endl;
    }

    // Try potential primitive roots until one is found
    for (cpp_int g = 2; g <= p; ++g)
    {
        cout << "Processing g = " << g << endl;
        bool isPrimitive = true;
        for (const cpp_int &factor : primeFactors)
        {
            cpp_int q = phi / factor;
            cpp_int result = modPow(g, q, p);
            if (result == 1)
            {
                isPrimitive = false;
                break;
            }
        }
        if (isPrimitive)
        {
            return g;
        }
    }

    return -1; // No primitive root found
}
int main()
{
    // string input;
    // cin >> input;
    cpp_int p = stringToNumber("100000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000081");

    cpp_int primitiveRoot = findPrimitiveRoot(p);
    if (primitiveRoot != -1)
    {
        cout << "Primitive root modulo "
             << " is: " << primitiveRoot << endl;
    }
    else
    {
        cout << "No primitive root found for p " << endl;
    }

    return 0;
}
