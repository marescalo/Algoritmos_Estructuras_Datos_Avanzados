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

 #ifndef BIGUNSIGNED_H
 #define BIGUNSIGNED_H
 
 #include <algorithm>
 #include <iostream>
 #include <stdexcept>
 #include <string>
 #include <vector>
 
 class BigUnsigned {
  public:
   // Constructores
   BigUnsigned();                      // Por defecto
   BigUnsigned(const unsigned char*);  // Con char
   BigUnsigned(const BigUnsigned&);    // Copia
 
   // Asignacion
   BigUnsigned& operator=(const BigUnsigned&);
 
   // Insercion y extraccion
   friend std::ostream& operator<<(std::ostream&, const BigUnsigned& number);
   friend std::istream& operator>>(std::istream&, BigUnsigned& number);
 
   // Comparación
   bool operator==(const BigUnsigned&) const;
   friend bool operator<(const BigUnsigned&, const BigUnsigned&);
   friend bool operator<=(const BigUnsigned&, const BigUnsigned&);
   friend bool operator>(const BigUnsigned&, const BigUnsigned&);
   friend bool operator>=(const BigUnsigned&, const BigUnsigned&);
 
   // Incremento y decremento
   BigUnsigned& operator++();    // Preincremento
   BigUnsigned operator++(int);  // Postincremento
   BigUnsigned& operator--();    // Predecremento
   BigUnsigned operator--(int);  // Postdecremento
 
   // Operadores aritméticos
   friend BigUnsigned operator+(const BigUnsigned&, const BigUnsigned&);
   BigUnsigned operator-(const BigUnsigned& other) const;
   BigUnsigned operator*(const BigUnsigned&) const;
   friend BigUnsigned operator/(const BigUnsigned&, const BigUnsigned&);
   BigUnsigned operator%(const BigUnsigned&) const;
 
   // Métodos auxiliares
   std::string ToString() const;  // Convierte el número en string
   void RemoveLeadingZeros();     // Elimina ceros a la izquierda
 
  private:
   std::vector<unsigned char> num_;
 };
 
 #endif  // BIGUNSIGNED_H