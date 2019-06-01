#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct {
char *dni, *nombre, *apellido, *descripcionCargo;
int prioridad;
} _Invitado;

FILE *fopen( const char * filename, const char * mode );
int fclose( FILE *fp );

typedef _Invitado* Invitado;

typedef struct _Nodo {
Invitado invitado;
struct _Nodo *sig, *ant;
} Nodo;

typedef Nodo* Lista;

int list_longitud(Lista inicio)
{
    if(inicio==NULL) return 0;
    return 1+ list_longitud(inicio->sig);
}

//Parece estar bien
Lista insertar(Lista inicio, Invitado Invitado)
{

  Lista nuevoNodo=malloc(sizeof(Lista));
  nuevoNodo->invitado=Invitado;
  nuevoNodo->sig=inicio;
  nuevoNodo->ant=NULL;
  return nuevoNodo;
}
//revisar mucho(parece que siempre hay un nodo de mas)(me tira muchos cortes)(en algunas pruebas me da 1 de mas, y en la proxima(sin cambiar nada), me da justo)
Lista Leer(FILE *fp,Lista Inicio){

          if(fgetc(fp)!=EOF){

            Inicio=NULL;
            char dni[9],nombre[20],apellido[20],cargo[100],basura[5];
            int prioridad;
            fscanf(fp,"%[^',']",dni);
            fscanf(fp,"%s",basura);
            fscanf(fp,"%[^',']",nombre);
            fscanf(fp,"%s",basura);
            fscanf(fp,"%[^',']",apellido);
            fscanf(fp,"%s",basura);
            fscanf(fp,"%[^',']",cargo);
            fscanf(fp,"%s",basura);
            fscanf(fp,"%d",&prioridad);

             /*
            printf("%s\n",dni);
            printf("%s\n",nombre);
            printf("%s\n",apellido);
            printf("%s\n",cargo);
            printf("%d\n",prioridad);
 */
            Invitado invitado=malloc(sizeof(Invitado));
            invitado->dni=malloc(sizeof(char)*9);
            strcpy(invitado->dni,dni);
            printf("hola:%s\n",invitado->dni);
            invitado->nombre=malloc(sizeof(char)*(strlen(nombre)+1));
            strcpy(invitado->nombre,nombre);
            invitado->apellido=malloc(sizeof(char)*(strlen(apellido)+1));
            strcpy(invitado->apellido,apellido);
            invitado->descripcionCargo=malloc(sizeof(char)*(strlen(cargo)+1));
            strcpy(invitado->descripcionCargo,cargo);
         //   printf("%s\n",invitado->descripcionCargo);
            invitado->prioridad = malloc(sizeof(int));
            invitado->prioridad=prioridad;
            Inicio=insertar(Inicio,invitado);
            Inicio->sig=Leer(fp,Inicio->sig);;

          }
          else
          {
              printf("Pvto");
          Inicio=NULL;
          }

  return Inicio;
}
Invitado Comparar_Prioridad(Invitado invitado1,Invitado Invitado2)
{
    if(Invitado2==NULL) return invitado1;
    if(invitado1->prioridad>Invitado2->prioridad)   return Invitado2;
    else
            return invitado1;
}
Lista Ordenar_Por_Prioridad(Lista lista,int total)
{
    int Largo=list_longitud(lista);         //Para no tener que llamar a list_long mas de 1 vez
    if(lista->sig==NULL||Largo<2)    return lista;
        else
            {
                if(Largo<=total)
                        {
                            Ordenar_Por_Prioridad(lista,total/2);
                        }
                Lista Nuevo=malloc(sizeof(Lista));
                Nuevo->invitado=Comparar_Prioridad(lista->invitado,lista->sig->invitado);

            }
    return lista;
}


//bien(o eso parece)(a lo sumo separar printfs)
void mostrar(Lista Inicio)
    {
    if(Inicio!=NULL)
        {
            printf("%s",Inicio->invitado->dni);
            printf("%s",Inicio->invitado->nombre);
            printf("%s",Inicio->invitado->apellido);
            printf("%s",Inicio->invitado->descripcionCargo);
            printf(" %d\n",Inicio->invitado->prioridad);

            mostrar(Inicio->sig);
        }
    }

int main()
{
  int Total;
  printf("Ingrese el total de invitados\n" );
  scanf("%d",&Total );
  FILE *fp=fopen("test.txt","r");
  Lista Lista_Invitados_Sin_Ordenar,Lista_inivatados_Ordenada;
  Lista_Invitados_Sin_Ordenar=Leer(fp,Lista_Invitados_Sin_Ordenar);
  Lista_inivatados_Ordenada=malloc(sizeof(Lista)*list_longitud(Lista_Invitados_Sin_Ordenar));
  //printf("%d\n",list_longitud(Lista_Invitados_Sin_Ordenar));//esta para corroborar cantidad de nodos de la lista
  //Lista_inivatados_Ordenada=Ordenar_Por_Prioridad(Lista_Invitados_Sin_Ordenar,Total);
  mostrar(Lista_Invitados_Sin_Ordenar);

  fclose(fp);
}
