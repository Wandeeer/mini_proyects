#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Contacto {
  char name[50];
  char tel[20];
  char mail[50];
  struct Contacto *next;
};

// Funcion para crear un nuevo contacto
struct Contacto *add_contact(struct Contacto *head, char *nombre, char *num,
                             char *email) {
  struct Contacto *new = (struct Contacto *)malloc(sizeof(struct Contacto));

  // new->name = nombre;
  strcpy(new->name, nombre);
  // new->tel = num;
  strcpy(new->tel, num);
  strcpy(new->mail, email);
  // new->mail = email;
  new->next = NULL;

  // Si no existe una cabeza entoces:
  if (head == NULL) {
    return new; // Retornamos la que va a ser cabeza
  }

  // Si cabeza ya existe entonces:
  struct Contacto *actual = head;
  while (actual->next != NULL) {
    actual = actual->next;
  }
  actual->next = new; // Inyectamos al nuevo contacto en la ultima posicion
  return head;
}

// Funcion de busqueda
void search_contact(struct Contacto *head, char *contact_name) {
  struct Contacto *contacto = head;
  int is_found;
  while (contacto != NULL) {
    if (strcmp(contact_name, contacto->name) == 0) {
      printf("\nNombre: %s \n", contacto->name);
      printf("Telefono: %s \n", contacto->tel);
      printf("Email: %s \n\n", contacto->mail);
      is_found = 1;
      break;
    }
    contacto = contacto->next;
  }

  if (is_found == 1) {
    printf("\nContacto encontrado\n");
  } else {
    printf("\nNo existe el contacto\n");
  }
}

// Funcion para listar los contactos
void read_list(struct Contacto *head) {
  struct Contacto *actual = head;
  int index = 0;
  while (actual != NULL) {
    index++;
    printf("\nContacto: %d \n\n", index);
    printf("Nombre: %s \n", actual->name);
    printf("Telefono: %s \n", actual->tel);
    printf("Email: %s \n", actual->mail);

    actual = actual->next;
  }

  printf("\nSe han mostrado todos los contactos.\n");
  printf("Contactos totales: %d \n", index);
}

// Funcion para eliminar una persona

void delete_contact(struct Contacto** head, char *value) {
  struct Contacto *actual = *head;
  struct Contacto *anterior = NULL;

  // Si la la lista esta vacia no hay nada que eliminar
  if(actual == NULL) return; 
  
  // Si el contacto a elimar es el primero
  if(strcmp(actual->name, value) == 0) {
    *head = actual->next;
    free(actual);
    return;
  }

  // Si no es el primero vamos a buscarlo
  while((actual != NULL) && (strcmp(actual->name, value) != 0)) {
    anterior = actual;
    actual = actual->next;
  }

  // Si el contacto no se encontro
  if(actual == NULL) return;

  // Si el contacto se encontro en el medio o al final
  anterior->next = actual->next;
  free(actual);
  printf("\nContacto eliminado con exito\n");
}

// Funcion para guardar datos en un archivo .txt
void save_contact(struct Contacto* head) {
  FILE *file = fopen("agenda.txt", "w");

  // Verificar si el archivo se abrio bien
  if (!file) {
    printf("\nError al abrir para guardar...\n");
    return;
  }

  // Guardar contactos ingresados
  struct Contacto* temp = head;
  while(temp != NULL) {
    fprintf(file, "%s, %s, %s\n", temp->name, temp->tel, temp->mail);
    temp = temp->next;
  }

  // Cerramos el archivo

  printf("\nArchivos guardados con exito\n");
  fclose(file);
}

// Funcion para leer los contacto creados previamente desde un archivo .txt
struct Contacto* read_contacts() {
  FILE *file = fopen("agenda.txt", "r");
  if(!file) {
    printf("\nError al leer agenda creando una nueva...\n");
    return NULL;
  }

  struct Contacto *head = NULL;
  char nombre[50], numero[50], email[50];

  // Asinar datos a cabeza
  while(fscanf(file, "%49[^,],%19[^,],%49[^\n]\n", nombre, numero, email) == 3) {
    head = (add_contact(head, nombre, numero, email));
  }

  fclose(file);
  return head;
}

int main() {
  int exit = 0;
  char nombre[50];
  char numero[20];
  char email[50];

  // Verificar si hay contactos guardados previamente
  // si no devuelve NULL o vacio
  struct Contacto *head = read_contacts();

  // Interfaz
  while (exit != 1) {

    int value;

    printf("\nQue desea hacer: \n1:Nuevo contacto \n2:Ver contactos \n3:Buscar "
           "\n4:Eliminar \n5:Salir\n\n");
    scanf(" %d", &value);

    // Opciones
    switch (value) {
    case 1: {
      printf("Ingrese los siguintes datos: \n");

      printf("\nNombre: ");
      scanf(" %[^\n]", nombre);

      printf("\nNumero de telefono: ");
      scanf(" %[^\n]", numero);

      printf("\nEmail: ");
      scanf(" %[^\n]", email);

      // Crear contacto
      head = add_contact(head, nombre, numero, email);

      // Actualizar agenda
      save_contact(head);
      
      break;
    }
    case 2:
      read_list(head);
      break;
    case 3:
      char name_contact[50];
      printf("Ingrese el nombre de la persona que desea buscar: \n");
      scanf("%s", name_contact);
      search_contact(head, name_contact);
      break;
    case 4:
      char name[50];
      printf("\nIngrese el nombre del contacto que desea eliminar: \n");
      scanf("%49s", name);
      delete_contact(&head, name);

      // Actualizar agenda
      save_contact(head);
      break;
    case 5:
      exit = 1;
      printf("Saliendo...");
      break;
    default:
      exit = 1;
      printf("Opcion Invalida, Saliendo...");
      break;
    }
  }

  return 0;
}
