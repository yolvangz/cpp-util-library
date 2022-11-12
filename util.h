/*
   ----------------------------
   cpp-util-library - util-0.3
   ----------------------------
*/
// I N F O R M A C I O N
// ======================
// Las siguientes lineas son las librerias de cabecero que usa el programa.
// Para proyecto de un archivo, copiar y pegar las librerias junto al namespace "util".
// Para proyectos multificheros, añadir las siguientes lineas al header.h o el
// archivo de cabecero que use el proyecto, copiar las lineas correspondiente a la definición del namespace util
// y comentar las lineas de abajo (recomendado).

// =============================
//  LIBRERIAS DEL UTIL.H
// =============================
#pragma once // directiva que indica que se compile una sola vez

#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <cctype>
#include <stdlib.h>
#include <climits>
// ==============================
//  DECLARACION DE LAS FUNCIONES
// ==============================

namespace util {
   class Config {
      private:
         bool _win;
         bool _pause;
         bool _clear;
      public:
         Config (bool isWin = false, bool willPause = false, bool willClear = false) {
            _win = isWin;
            _pause = willPause;
            _clear = willClear;
         }
         bool win () {return _win;};
         bool pause () {return _pause;};
         bool clear () {return _clear;};
   };
   Config CONF;
   // Templates & Overloaded Functions
   template <typename numType> numType inputNumber (std::string textoARepetir, numType max = INT_MAX, numType min = INT_MIN);
   std::string formattedFloat (float num);
   std::string formattedFloat (std::string str);
   // Simple Functions
   bool validarClav (std::string clave, int intentos = 3);
   bool inputBool (std::string textoARepetir, std::string valorTrue, std::string valorFalse);
   std::string inputString (std::string textoARepetir, bool espaciosEnBlanco = false, unsigned int longitudDeseada = 0);
   std::string multiplyStr (std::string str, int times);
   void borrarPantalla ();
   void pause ();
   void setConfig(bool isWin = false, bool willPause = false, bool willClear = false);
} // namespace util

// En caso de trabajar con archivo de cabecero, descomentar la siguiente linea y modificar la ruta
// al nombre del archivo a trabajar

// #include "header.h"


// =============================
//  DEFINICION DE LAS FUNCIONES
// =============================
namespace util {
   // Habilita una entrada de usuario validada para que ingrese un numero entero o flotante,
   // imprimiendo un mensaje descriptivo que se repite tras cada iteracion.
   // Recibe un booleano que dicta ademas si el valor a devolver va a ser decimal o entero.
   template <typename numType> numType inputNumber (std::string textoARepetir, numType max, numType min) {
      std::string input = "";
      numType num;
      while (true) {
         std::cout << textoARepetir;
         std::cin >> input;
         try	{
            // Lo convierte a float y luego al tipo especificado
            num = stof(input);
            // Revisa que no exceda los valores maximos y minimos especificados
            if (num < min) throw 1;
            if (num > max) throw 2;
            return num;
         } catch (int err) {
            borrarPantalla();
            if (err == 1) {
               std::cout << "El numero que ingreso es MENOR al limite establecido ("<< min <<"). Ingrese un numero mayor." << std::endl;
            } else if (err == 2) {
               std::cout << "El numero que ingreso es MAYOR al limite establecido ("<< max <<"). Ingrese un numero menor." << std::endl;
            }
         } catch (...) {
            borrarPantalla();
            std::cout << "Entrada invalida." << std::endl;
         }
         continue;
      }
   }
   // Recibe un FLOAT
   // Retorna una cadena de texto que representa un numero flotante con dos decimales
   std::string formattedFloat (float num) {
      std::string str = "";
      str = std::to_string(num);
      return util::formattedFloat(str);
   }
   // recibe un STRING
   // Retorna una cadena de texto que representa un numero flotante con dos decimales
   std::string formattedFloat (std::string str) {
      int pos;
      pos = str.find('.');
      if (pos == -1) return str;
      return str.substr(0, pos) + str.substr(pos, 3);
   }
   // Genera una entrada booleana con dos valores posibles (ejemplo: S/N)
   bool inputBool (std::string textoARepetir, char valorTrue, char valorFalse) {
      std::string input;
      char option;
      while (true) {
         std::cout << textoARepetir << " (" << valorTrue << "/" << valorFalse << "): ";
         std::cin >> input;
         
         option = tolower(input[0]);
         if (option == std::tolower(valorTrue)) return true;
         if (option == std::tolower(valorFalse)) return false;
         
         std::cout << "Ingrese una letra valida." << std::endl;
      }
   }
   // retorno booleano y cuyos parametros es la clave a validar como entero.
   // Son 3 intentos por DEFAULT
   bool validarClav (std::string clave, int intentos) {
      std::string claveIngresada;
      for (intentos; intentos > 0; intentos--) {
         claveIngresada = util::inputString("Ingrese clave para continuar: ", false);
         borrarPantalla();
         if (claveIngresada == clave) {
            std::cout << "Clave Ingresada Correcta. Puede Continuar.\n";
            pause();
            return true; // Retorna verdadero, que la clave ingresada fue valida
         } else { // Si no coincidio, avisa que se equivoco
            std::cout << "Clave Ingresada Incorrecta. ";
            if (intentos-1 > 0)	{
               std::cout << intentos-1 << " intento(s) restante(s).\n"; // Si los hay, imprime la cantidad de oportunidades restantes
            }
         }
      }
      std::cout << "Operacion Cancelada.\n";
      pause();
      return false;  // Retorna falso, ya que las claves ingresadas no fueron validas
   }
   // Habilita una entrada de usuario validada para que ingrese una cadena de texto validada,
   // imprimiendo un mensaje descriptivo que se repite tras cada iteracion.
   // Recibe un booleano que dicta si el valor acepta espacios en blanco.
   // Recibe un entero positivo que dicta la longitud necesaria de la cadena.
   std::string inputString (std::string textoARepetir, bool espaciosEnBlanco, unsigned int longitudDeseada) {
      std::string input = "";
      while (true) {
         // Imprime el texto en cada vuelta para que no se pierda
         std::cout << textoARepetir;
         if (espaciosEnBlanco) {
            // Limpia los datos para que no se adulteren
            std::cin.ignore();
            // Captura la línea completa
            getline(std::cin, input);
         } else {
            std::cin >> input;
         }
         try	{
            // Valida si tiene carácteres no permitidos '|', '\', ',', '.' o espacios en blanco si lo dice el argumento 
            if (input.find('|') != -1 || input.find('\\') != -1 || input.find(',') != -1 || input.find('.') != -1 || (!espaciosEnBlanco && input.find(' ') != -1)) throw 1;
            if (longitudDeseada > 0 && input.size() != longitudDeseada) throw 2;
            return input;
         } catch (int codigoError) {
            std::string mensajeError = "";
            switch (codigoError) {
               case 1:
                  mensajeError = "Entrada invalida, debe ingresar sin usar "; 
                  if (espaciosEnBlanco) mensajeError += "espacios en blanco ni ";						
                  mensajeError += "los caracteres especiales '|', '\\', ',' o '.'";
                  break;
               case 2:
                  mensajeError = "Entrada valida, el dato debe tener (" + std::to_string(longitudDeseada) + ") caracteres de longitud"; break;
            }
            std::cout << mensajeError << std::endl;
            continue;
         }
      }
   }
   // Recibe un string y lo retorna repetido la cantidad de veces indicada
   std::string multiplyStr (std::string str, int times) {
      std::string textoMultiplicado = "";
      for (int i = 0; i < times; i++) {
         textoMultiplicado += str;
      }
      return textoMultiplicado;
   }
   // Encapsula una funcion para limpiar la pantalla del programa para multiplataforma
   void borrarPantalla () {
      if (!CONF.clear()) return;
      system(((CONF.win()) ? "cls" : "clear")); // LIMPIA LA CONSOLA EN WINDOWS/LINUX
      // std::cout << "\033[2J\033[1;1H"; // LIMPIA LA CONSOLA EN UNIX/LINUX
   }
   // Encapsula la funcion para pausar el programa para multiplataforma
   void pause () {
      if (!CONF.pause()) return;
      if (CONF.win()) {system("pause"); return;}
      std::cout << "Presione una tecla para continuar . . . ";
      std::cin.ignore();
      std::cin.get();
   }
   void setConfig (bool isWin, bool willPause, bool willClear) {
      Config newConf(isWin, willPause, willClear);
      CONF = newConf;
   }
} // namespace util