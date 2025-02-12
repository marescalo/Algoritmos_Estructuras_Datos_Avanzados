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

 #include <iostream>

 #include "BigInteger.h"
 #include "BigUnsigned.h"
 

 BigInteger mcd(const BigInteger& a, const BigInteger& b) {
   // Ensure we work with positive values
   BigInteger x = a.isNegative() ? -a : a;
   BigInteger y = b.isNegative() ? -b : b;
 
   // Euclidean algorithm
   while (y != BigInteger(0)) {
     BigInteger temp = y;
     y = x % y;  // Get the remainder
     x = temp;   // Update x with y
   }
   return x;  // When y is 0, x is the GCD
 }
 
 int main() {
   // Create two large numbers from strings
   BigUnsigned num1((const unsigned char*)"50");
   BigUnsigned num2((const unsigned char*)"5");
 
   // Display initial numbers
   std::cout << "Número 1: " << num1 << std::endl;
   std::cout << "Número 2: " << num2 << std::endl;
 
   // Sum of the two numbers
   BigUnsigned suma = num1 + num2;
   std::cout << "Suma: " << suma << std::endl;
 
   // Comparison of the numbers
   if (num1 < num2) {
     std::cout << "Número 1 es menor que Número 2." << std::endl;
   } else if (num1 == num2) {
     std::cout << "Número 1 es igual a Número 2." << std::endl;
   } else {
     std::cout << "Número 1 es mayor que Número 2." << std::endl;
   }
 
   // Increment and decrement
   std::cout << "Pre-incremento de Número 1: " << ++num1 << std::endl;
   std::cout << "Post-incremento de Número 2: " << num2++ << std::endl;
   std::cout << "Número 2 después del post-incremento: " << num2 << std::endl;
 
   // Subtraction of the numbers
   BigUnsigned resta = num1 - num2;
   std::cout << "Resta (Número 1 - Número 2): " << resta << std::endl;
 
   // Multiplication
   BigUnsigned product = num1 * num2;
   std::cout << "Producto: " << product << std::endl;
 
   // Division
   BigUnsigned quotient = num1 / num2;
   std::cout << "Cociente: " << quotient << std::endl;
 
   // Modulo
   BigUnsigned remainder = num1 % num2;
   std::cout << "Residuo: " << remainder << std::endl;
 
   // User input
   BigUnsigned num3;
   std::cout << "Introduce un número grande: ";
   std::cin >> num3;
   std::cout << "El número que ingresaste fue: " << num3 << std::endl;
 
   // Calculate GCD of two BigInteger values
   BigInteger a("-48");
   BigInteger b("18");
 
   std::cout << "MCD de " << a << " y " << b << " es: " << mcd(a, b)
             << std::endl;
 
   BigInteger c("12345678901234567890");
   BigInteger d("-98765432109876543210");
 
   std::cout << "MCD de " << c << " y " << d << " es: " << mcd(c, d)
             << std::endl;
 
   return 0;
 }