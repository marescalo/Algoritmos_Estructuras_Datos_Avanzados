 /**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Asignatura: Algoritmos y Estructuras de datos Avanzadas
 * Curso: 2º
 *
 * Autor: Margarita Blanca Escobar Alonso
 * Correo: alu0101567211@ull.edu.es
 * Fecha 10 Feb 2025
 * Archivo: bigUnsigned.h
 * Referencias:
 *     Enunciado de la práctica
 */
 
 #include "BigUnsigned.h"

 BigUnsigned::BigUnsigned() : num_(1, 0) {}
 BigUnsigned::BigUnsigned(const unsigned char* str) {
   // Convert the input string to a vector of digits
   while (*str) {
     if (*str < '0' || *str > '9') {
       throw std::invalid_argument(
           "Invalid character in string input. Must contain only digits.");
     }
     num_.insert(num_.begin(), *str - '0');
     ++str;
   }
 }

 BigUnsigned::BigUnsigned(const BigUnsigned& other) : num_(other.num_) {}

 BigUnsigned& BigUnsigned::operator=(const BigUnsigned& other) {
   if (this != &other) {  // Avoid self-assignment
     num_ = other.num_;
   }
   return *this;
 }
 
 std::ostream& operator<<(std::ostream& os, const BigUnsigned& number) {
   for (auto it = number.num_.rbegin(); it != number.num_.rend(); ++it) {
     os << static_cast<char>(*it + '0');
   }
   return os;
 }
 
 std::istream& operator>>(std::istream& is, BigUnsigned& number) {
   std::string input;
   is >> input;
 
   // Basic verification: ensure it only contains digits
   for (char c : input) {
     if (c < '0' || c > '9') {
       throw std::invalid_argument("Invalid input. Must contain only digits.");
     }
   }
 
   // Convert the string to a number stored in a vector
   number.num_.clear();  // Clear any previous value
   for (auto it = input.rbegin(); it != input.rend(); ++it) {
     number.num_.push_back(static_cast<unsigned char>(*it - '0'));
   }
   return is;
 }

 bool BigUnsigned::operator==(const BigUnsigned& other) const {
   return num_ == other.num_;
 }
 
 bool operator<(const BigUnsigned& lhs, const BigUnsigned& rhs) {
   if (lhs.num_.size() != rhs.num_.size()) {
     return lhs.num_.size() < rhs.num_.size();
   }
 
   // Compare digit by digit starting from the most significant
   for (auto lhs_it = lhs.num_.rbegin(), rhs_it = rhs.num_.rbegin();
        lhs_it != lhs.num_.rend(); ++lhs_it, ++rhs_it) {
     if (*lhs_it != *rhs_it) {
       return *lhs_it < *rhs_it;
     }
   }
   return false;  // They are equal
 }

 bool operator<=(const BigUnsigned& a, const BigUnsigned& b) {
   return (a < b) || (a == b);
 }
 bool operator>(const BigUnsigned& a, const BigUnsigned& b) { return !(a <= b); }
 bool operator>=(const BigUnsigned& a, const BigUnsigned& b) { return !(a < b); }
 
 BigUnsigned& BigUnsigned::operator++() {
   unsigned char carry = 1;
   for (auto& digit : num_) {
     unsigned char sum = digit + carry;
     carry = sum / 10;
     digit = sum % 10;
     if (carry == 0) break;
   }
   if (carry > 0) {
     num_.push_back(carry);
   }
   return *this;
 }
 
 BigUnsigned BigUnsigned::operator++(int) {
   BigUnsigned temp(*this);  // Save the previous state
   ++(*this);                // Call the pre-increment
   return temp;
 }
 
 BigUnsigned& BigUnsigned::operator--() {
   if (num_.size() == 1 && num_[0] == 0) {
     throw std::underflow_error(
         "BigUnsigned underflow: cannot decrement below 0.");
   }
   unsigned char borrow = 1;
   for (auto& digit : num_) {
     if (digit >= borrow) {
       digit -= borrow;
       borrow = 0;
       break;
     } else {
       digit = 9;
     }
   }
   // Remove leading zeros if they exist
   while (num_.size() > 1 && num_.back() == 0) {
     num_.pop_back();
   }
   return *this;
 }
 
 BigUnsigned BigUnsigned::operator--(int) {
   BigUnsigned temp(*this);  // Save the previous state
   --(*this);                // Call the pre-decrement
   return temp;
 }
 
 BigUnsigned operator+(const BigUnsigned& lhs, const BigUnsigned& rhs) {
   BigUnsigned result;
   result.num_.clear();
 
   const auto& larger =
       (lhs.num_.size() > rhs.num_.size()) ? lhs.num_ : rhs.num_;
   const auto& smaller =
       (lhs.num_.size() > rhs.num_.size()) ? rhs.num_ : lhs.num_;
 
   unsigned char carry = 0;
 
   for (size_t i = 0; i < larger.size(); ++i) {
     unsigned char digit1 = (i < smaller.size()) ? smaller[i] : 0;
     unsigned char sum = larger[i] + digit1 + carry;
     carry = sum / 10;
     result.num_.push_back(sum % 10);
   }
 
   if (carry > 0) {
     result.num_.push_back(carry);
   }
   return result;
 }
 
 BigUnsigned BigUnsigned::operator-(const BigUnsigned& other) const {
   if (*this < other) {
     throw std::invalid_argument("Cannot subtract: result would be negative.");
   }
 
   BigUnsigned result(
       *this);  // Create a new object "result" based on "this"
   unsigned char borrow = 0;
 
   for (size_t i = 0; i < result.num_.size(); ++i) {
     unsigned char subtrahend =
         (i < other.num_.size()) ? other.num_[i] : 0;
 
     if (result.num_[i] < subtrahend + borrow) {
       result.num_[i] +=
           10 - (subtrahend + borrow);  // Adjust the current digit
       borrow = 1;
     } else {
       result.num_[i] -=
           (subtrahend + borrow);  // Perform the subtraction normally
       borrow = 0;
     }
   }
 
   // Remove leading zeros if necessary
   while (result.num_.size() > 1 && result.num_.back() == 0) {
     result.num_.pop_back();
   }
 
   return result;  // Return the result by value
 }

 BigUnsigned BigUnsigned::operator*(const BigUnsigned& other) const {
   // Create a vector large enough for the result
   std::vector<unsigned char> resultDigits(num_.size() + other.num_.size(), 0);
 
   // Digit-by-digit multiplication
   for (size_t i = 0; i < num_.size(); ++i) {
     unsigned char carry = 0;
     for (size_t j = 0; j < other.num_.size(); ++j) {
       unsigned long long mult =
           static_cast<unsigned long long>(num_[i]) * other.num_[j] +
           resultDigits[i + j] + carry;
       resultDigits[i + j] = static_cast<unsigned char>(mult % 10);
       carry = static_cast<unsigned char>(mult / 10);
     }
     // Add any remaining carry
     if (carry > 0) {
       resultDigits[i + other.num_.size()] += carry;
     }
   }
 
   // Remove leading zeros
   while (resultDigits.size() > 1 && resultDigits.back() == 0) {
     resultDigits.pop_back();
   }
 
   BigUnsigned result;
   result.num_ = resultDigits;  // Assign the calculated result
   return result;
 }
 
 BigUnsigned operator/(const BigUnsigned& dividend, const BigUnsigned& divisor) {
   if (divisor == BigUnsigned((const unsigned char*)"0")) {
     throw std::invalid_argument("Cannot divide by zero.");
   }
 
   BigUnsigned result;   // The quotient
   BigUnsigned current;  // Temporary remainder during calculations
 
   result.num_ = std::vector<unsigned char>(dividend.num_.size(), 0);
 
   for (size_t i = dividend.num_.size(); i-- > 0;) {
     // Move the next digit of the dividend to the current remainder
     current.num_.insert(current.num_.begin(), dividend.num_[i]);
 
     // Remove leading zeros in the remainder
     while (current.num_.size() > 1 && current.num_.back() == 0) {
       current.num_.pop_back();
     }
 
     // Find the quotient digit for this position
     unsigned char x = 0;
     while (divisor <= current) {
       current = current - divisor;  // Subtract from the current remainder
       ++x;                          // Increment the quotient digit
     }
 
     result.num_[i] =
         x;  // Assign the quotient digit in the appropriate position
   }
 
   // Remove leading zeros from the quotient
   while (result.num_.size() > 1 && result.num_.back() == 0) {
     result.num_.pop_back();
   }
 
   return result;
 }

 BigUnsigned BigUnsigned::operator%(const BigUnsigned& divisor) const {
   if (divisor == BigUnsigned((const unsigned char*)"0")) {
     throw std::invalid_argument("Cannot divide by zero.");
   }
 
   BigUnsigned current;
 
   for (size_t i = num_.size(); i-- > 0;) {
     // Move the next digit to the current remainder
     current.num_.insert(current.num_.begin(), num_[i]);
 
     // Remove leading zeros in the remainder
     while (current.num_.size() > 1 && current.num_.back() == 0) {
       current.num_.pop_back();
     }
 
     // Subtract the divisor until it no longer fits
     while (divisor <= current) {
       current = current - divisor;
     }
   }
 
   return current;  // The remainder
 }

 void BigUnsigned::RemoveLeadingZeros() {
   while (num_.size() > 1 && num_.back() == 0) {
     num_.pop_back();
   }
 }
 
 std::string BigUnsigned::ToString() const {
   if (num_.empty()) return "0";
   std::string result;
   for (auto it = num_.rbegin(); it != num_.rend(); ++it) {
     result += static_cast<char>(*it + '0');
   }
   return result;
 }