#include <stdio.h>
#include <stdlib.h>

struct Contacto {
  char *name;
  int tel;
  char *mail;
  struct Contacto* next;
};

struct Contacto* add_contact(struct Contacto* head, char *nombre, int num, char *email) {
  struct Contacto* new = (struct Contacto*)malloc(sizeof(struct Contacto));

  new->name = nombre;
  new->tel = num;
  new->mail = email;
  new->next = NULL;

  // Si no existe una cabeza entoces:
  if(head == NULL) {
    return new; // Retornamos la que va a ser cabeza
  }

  // Si cabeza ya existe entonces:
  struct Contacto* actual = head;
  while(actual->next != NULL) { // Recorremos a cabeza guardamos el ultimo contacto en actual
    actual = actual->next;
  }
 actual->next = new; // Inyectamos al nuevo contacto en la ultima posicion 
 return head;

}

void read_list(struct Contacto* head) {
  struct Contacto* actual = head;
  int index = 0;
  while(actual != NULL) {
    index++;
    printf("Contacto: %d \n\n", index);
    printf("Nombre: %s \n", actual->name);
    printf("Telefono: %d \n", actual->tel);
    printf("Email: %s \n", actual->mail);

    actual = actual->next;
  }

  printf("Se han mostrado todos los contactos.\n");
  printf("Contactos totales: %d \n", index);

}


int main() {
  bool exit = false;

  // Crear una cabeza vacia
  struct Contacto* head = NULL;

  // Crear interfaz
  while(exit != true) {
    
    int value;
    
    printf("\nQue desea hacer: \n1:Nuevo contacto \n2:Ver contactos \n\n");
    scanf("%d", &value);

    // Opciones
     switch(value) {
       case 1:
         
        char nombre[50];
        int numero;
        char email[50];

        printf("Ingrese los siguintes datos: \n");

        printf("\nNombre: \n");
        scanf("%s", &nombre);

        printf("\nNumero de telefono: \n");
        scanf("%d", &numero);

        printf("\nEmail: \n");
        scanf("%s", &email);
      
        head = add_contact(head, nombre, numero, email);

        int value_exit;
        printf("Desea salir: \n1:SI \n2:NO \n3:Mostrar lista\n");
        scanf("%d", &value_exit);

        if(value_exit == 1) {
          exit = true;
          break;
        } else if(value_exit == 2) { 
          exit = true;
          printf("Ahora te jodes no lo eh arreglado :v \n");
          break;
        } else if(value_exit == 3) {
          exit = true;
          read_list(head);
          break;
        }
      case 2:
        exit = true;
        read_list(head);
        break;

      default: 
        exit = true;
        printf("Opcion Invalida, Saliendo...");
        break;

     }
  }

  return 0;
}
