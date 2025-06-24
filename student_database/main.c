#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student {
  char name[50];
  char career[50];
  float average;
  struct Student* next;
};

// Funcion para agregar un NUEVO ESTUDIANTE
struct Student* add_student(struct Student* head, char *name, char *career, float average) {
  struct Student* new = (struct Student*)malloc(sizeof(struct Student));

  // Asignar valores
  strcpy(new->name, name); 
  strcpy(new->career, career);
  new->average = average;
  new->next = NULL;

  // Si cabeza no tiene ningun valor
  if(head == NULL) return new;

  // Si ya existe una cabeza recorremos
  struct Student* actual = head;
  while(actual->next != NULL) {
    actual = actual->next;
  }
  // Metemos al nuevo estudiante al final
  actual->next = new;
  return head;
}

// Funcion para BUSCAR UN ESTUDIANTE POR CARRERA
void search_student(struct Student* head, char *name_student) {
  struct Student* actual = head;

  int is_found = 0;
  while(actual != NULL) {
    if(strcmp(name_student, actual->name) == 0) {
      printf("\nNombre: %s\n", actual->name);
      printf("Carrea o Maestria: %s\n", actual->career);
      printf("Calificacion General: %.2f \n", actual->average);
      is_found = 1;
      break;
    }
    actual = actual->next;
  }
    if (is_found == 1) {
      printf("\nEstudiante encontrado\n");
    } else {
      printf("\nNo existe estudiante con tal nombre\n");
    }
}

// Funcion para CALCULAR EL PROMEDIO GENERAL
//void calculate_average(struct Student* head) {}

// Funcion para ELIMINAR UN ESTUDIANTE
void delete_student(struct Student** head, char *name_student) {
  struct Student* actual = *head;
  struct Student* anterior = NULL;

  if (actual == NULL) return;

  if(strcmp(actual->name, name_student) == 0) {
    *head = actual->next;
    free(actual);
    return;
  }

  while((actual != NULL) && (strcmp(actual->name, name_student) != 0)) {
    anterior = actual;
    actual = actual->next;
  }

  if (actual == NULL) return;

  anterior->next = actual->next;
  free(actual);
  printf("\nEstudiante eliminado correctamente\n");
}

// Funcion para MOSTRAR TODOS LOS ESTUDIANTES
void student_list(struct Student* head) {
  struct Student* actual = head;
  int index = 0;
  while(actual != NULL) {
    index++;
    printf("\nAlumno: %d\n\n", index);
    printf("\nNombre: %s\n", actual->name);
    printf("Carrea o Maestria: %s\n", actual->career);
    printf("Calificacion General: %.2f \n", actual->average);
    actual = actual->next;
  }

  printf("\nSe han mostrado todos los estudiantes.\n");
  printf("Estudiantes totales: %d \n", index);
}

// Funcion para GUARDAR LOS ESTUDIANTES EN UN ARCHIVO .TXT
void save_students(struct Student* head) {
  FILE *file = fopen("database.txt", "w");

  if (!file) {
    printf("\nError al abrir para guardar...\n");
    return;
  }

  struct Student* temp = head;
  while(temp != NULL) {
    fprintf(file, "%s,%s,%f\n", temp->name, temp->career, temp->average);
    temp = temp->next;
  }

  printf("\nArchivos guardados con exito\n");
  fclose(file);
}

// Funcion para LEER DATOS DEL ARCHIVO .TXT
struct Student* read_students() {
  FILE *file = fopen("database.txt", "r");

  if (!file) {
    printf("\nError al abrir creando uno nuevo...\n");
    return NULL;
  }

  struct Student* head = NULL;
  char name[50], career[50];
  float average;
  while(fscanf(file, "%49[^,],%49[^,],%f\n", name, career, &average) == 3) {
    head = (add_student(head, name, career, average));
  }

  fclose(file);
  return head;
}


// Funcion principal
int main() {

  struct Student* head = read_students();

  // Datos de Estudiante
  char name_student[50];
  char name_student_delete[50];
  char name_student_search[50];
  char career_student[50];
  int subject_student;
  float averge_student;

  // Interruptor de encendido/apagado
  int key = 0;
  // Opcion
  int option;
  
  // INTERFAZ
  do {
    printf("\n------------------- Bienvenido a la base de datos de estudiantes -------------------\n");
    printf("\nSeleccione una opcion: \n1:Agregar\n2:Buscar\n3:Eliminar\n4:Ver\n5:Salir\n");
    scanf("%d", &option);
    getchar();

    switch(option) {

      // Agregar nuevo estudiante
      case 1: {
                printf("\nIngrese a continuacion los siguientes datos: \n");
              
                printf("\nIngrese el nombre completo del estudiante:\n");
                scanf(" %[^\n]", name_student);

                printf("\nIngrese la carrera/profesion del estudiante:\n");
                scanf(" %[^\n]", career_student);

                printf("\nIngrese cuantas materias va a calificar:\n");
                scanf(" %d", &subject_student);

                int qualifications_student[subject_student];

                // Pedir al profesor ingresar las calificaciones
                printf("\nIngrese las calificaciones del estudiante\n\n");
                for(int i = 0; i < subject_student; i++) {
                  printf("Ingrese la calificion de su materia: %d\n\n", i + 1);
                  scanf("%d", &qualifications_student[i]);
                }

                // Sumar las calificaciones
                int size_qualification = sizeof(qualifications_student) / sizeof(qualifications_student[0]);
                int qualification = 0;
                float qualification_final;
                for(int i = 0; i < size_qualification; i++) {
                  qualification += qualifications_student[i];
                }

                qualification_final = qualification / subject_student;
              
                head = add_student(head, name_student, career_student, qualification_final);
                printf("\nSe agrego un estudiante correctamente\n");
                save_students(head);
                break;
              }
      // Buscar un estudiante
      case 2:
        printf("\nEscriba el nombre del estudiante:\n\n");
        scanf(" %[^\n]", name_student_search);
        search_student(head, name_student_search);
        break;

      // Eliminar un estudiante
      case 3:
        printf("\nEscriba el nombre del estudiante:\n\n");
        scanf(" %[^\n]", name_student_delete); 
        delete_student(&head, name_student_delete);
        save_students(head);
        break;

      // Ver estudiantes
      case 4:
        student_list(head);
        break;

      case 5:
        printf("\nSaliendo...\n");
        key = 1;
        break;
      default:
        printf("\nOpcion Invalida saliendo...\n");
        key = 1;
        break;
    }

  } while(key != 1);

  return 0;
}
