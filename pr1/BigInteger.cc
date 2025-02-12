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

 #include "BigInteger.h"

 #include <algorithm>
 #include <stdexcept>
 
 BigInteger::BigInteger() : magnitude_(), negative_(false) {}
 
 BigInteger::BigInteger(const BigUnsigned& value)
     : magnitude_(value), negative_(false) {}
 
 BigInteger::BigInteger(int value) : magnitude_(), negative_(value < 0) {
   // Convert the absolute value of the integer to BigUnsigned
   magnitude_ = BigUnsigned(reinterpret_cast<const unsigned char*>(
       std::to_string(std::abs(value)).c_str()));
 }
 
 BigInteger::BigInteger(const std::string& value)
     : magnitude_(), negative_(false) {
   if (value.empty()) throw std::invalid_argument("Invalid input string");
   size_t start = 0;
 
   if (value[0] == '-') {
     negative_ = true;
     start = 1;  // Skip the sign
   }
 
   // Convert the remaining characters to BigUnsigned
   magnitude_ = BigUnsigned(
       reinterpret_cast<const unsigned char*>(value.substr(start).c_str()));
 }
 
 bool BigInteger::operator==(const BigInteger& other) const {
   return (negative_ == other.negative_) && (magnitude_ == other.magnitude_);
 }
 
 bool BigInteger::operator!=(const BigInteger& other) const {
   return !(*this == other);
 }
 
 bool BigInteger::operator<(const BigInteger& other) const {
   if (negative_ != other.negative_) {
     return negative_ && !other.negative_;
   }
 
   if (negative_) {
     return magnitude_ > other.magnitude_;  // Inverse comparison
   }
   return magnitude_ < other.magnitude_;
 }
 
 bool BigInteger::operator<=(const BigInteger& other) const {
   return (*this < other) || (*this == other);
 }

 bool BigInteger::operator>(const BigInteger& other) const {
   return !(*this <= other);
 }

 bool BigInteger::operator>=(const BigInteger& other) const {
   return !(*this < other);
 }
 
 BigInteger BigInteger::operator+(const BigInteger& other) const {
   if (negative_ == other.negative_) {
     BigInteger result(magnitude_ + other.magnitude_);
     result.negative_ = negative_;
     return result;
   }
 
   if (magnitude_ >= other.magnitude_) {
     BigInteger result(magnitude_ - other.magnitude_);
     result.negative_ = negative_;
     return result;
   } else {
     BigInteger result(other.magnitude_ - magnitude_);
     result.negative_ = other.negative_;
     return result;
   }
 }

 BigInteger BigInteger::operator-(const BigInteger& other) const {
   BigInteger negatedOther = other;
   negatedOther.negative_ = !other.negative_;
   return *this + negatedOther;
 }

 BigInteger BigInteger::operator*(const BigInteger& other) const {
   BigInteger result(magnitude_ * other.magnitude_);
   result.negative_ = negative_ != other.negative_;
   return result;
 }

 BigInteger BigInteger::operator/(const BigInteger& other) const {
   if (other.magnitude_ ==
       BigUnsigned(reinterpret_cast<const unsigned char*>("0"))) {
     throw std::invalid_argument("Division by zero");
   }
 
   BigInteger result(magnitude_ / other.magnitude_);
   result.negative_ = negative_ != other.negative_;
   return result;
 }

 BigInteger BigInteger::operator%(const BigInteger& other) const {
   if (other.magnitude_ == BigUnsigned(reinterpret_cast<const unsigned char*>("0"))) {
     throw std::invalid_argument("Modulo by zero");
   }
   BigInteger result(magnitude_ % other.magnitude_);
   result.negative_ = negative_;
   return result;
 }
 
 std::string BigInteger::ToString() const {
   std::string result = magnitude_.ToString();
   if (negative_) result.insert(result.begin(), '-');
   return result;
 }
 
 bool BigInteger::isNegative() const { return negative_; }
 
 void BigInteger::RemoveLeadingZeros() { magnitude_.RemoveLeadingZeros(); }
 
 std::ostream& operator<<(std::ostream& out, const BigInteger& bigint) {
   return out << bigint.ToString();
 }

 std::istream& operator>>(std::istream& in, BigInteger& bigint) {
   std::string input;
   in >> input;
   bigint = BigInteger(input);
   return in;
 }

 BigInteger BigInteger::operator-() const {
   BigInteger result = *this;      // Make a copy of the current object
   result.negative_ = !negative_;  // Change the sign
   return result;
 }