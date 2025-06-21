#include <iostream>
#include <math.h>
using namespace std;

int main() {
  int nums[15] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14};
  int num = 0;
  cout << "Eliga un numero del rango 1 - 10, para revelar su ubucaion: \n";
  cin >> num;
  if ((num > 14) || (num < 0)) {
    cout << "Numero invalido, ingrese un numero en el rango permitido: 0 - 14";
    return 1;
  }

  // busqueda lineal
  /*for (int i = 1; i < num_m; i++) {
   if ((nums[i] == num) && (nums[i] <= 10)) {
     cout << "el numero es: " << nums[i] << " le tomo: " << i << " vueltas para
  encontrarlo \n"; } else { cout << "numero invalido \n";
   }
  } */

  // Variables para busqueda binaria
  int start = 0;
  int end = 14;
  bool end_loop = false;
  int index = 0;

  // Inicio de busqueda binaria
  while (start <= end) {

    int arr_medio = (start + end) / 2;
    index++;

    if (arr_medio == num) {
      cout << "Numero encontrado en: " << index << " vueltas \n";
      end = true;
    } else if (nums[arr_medio] < num) {
      start = arr_medio + 1;
    } else {
      end = arr_medio - 1;
    }

    if (!end_loop) {
      cout << "Numero no encontrado en la vuelta: " << index << endl;
    }
  }

  return 0;
}
