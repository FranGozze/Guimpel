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
          if(fgetc(fp)==EOF)    Inicio;

          else
          {
            char dni[9],nombre[20],apellido[20],cargo[100],basura[5];
            int prioridad;
            fscanf(fp,"%[^',']",dni);
            fscanf(fp,"%c",basura);
            fscanf(fp,"%[^',']",nombre);
            fscanf(fp,"%c",basura);
            fscanf(fp,"%[^',']",apellido);
            fscanf(fp,"%c|",basura);
            fscanf(fp,"%[^',']",cargo);
            fscanf(fp,"%c",basura);
            fscanf(fp,"%d",&prioridad);
            Invitado invitado=malloc(sizeof(_Invitado));
            invitado->dni=malloc(sizeof(char)*(strlen(dni)+1));
            strcpy(invitado->dni,dni);
            invitado->nombre=malloc(sizeof(char)*(strlen(nombre)+1));
            strcpy(invitado->nombre,nombre);
            invitado->apellido=malloc(sizeof(char)*(strlen(apellido)+1));
            strcpy(invitado->apellido,apellido);
            invitado->descripcionCargo=malloc(sizeof(char)*(strlen(cargo)+1));
            strcpy(invitado->descripcionCargo,cargo);
            invitado->prioridad=prioridad;
            Inicio=insertar(Inicio,invitado);

            Inicio->sig=Leer(fp,Inicio->sig);
           }

  return Inicio;
}
void comparacion(Lista lista2,Lista lista3)
{       if(lista2 -> invitado -> prioridad > lista3 -> invitado -> prioridad)
            {
                      Invitado aux = lista2 -> invitado;
                                lista2 -> invitado = lista3 -> invitado;
                                lista3 -> invitado = aux;
                      }
       if(lista2 -> invitado -> prioridad==lista3 -> invitado -> prioridad)
                {
                  if(strcmp(lista2 -> invitado -> apellido,lista3 -> invitado -> apellido)==0)
                      {
                        if(strcmp(lista2 -> invitado -> nombre,lista3 -> invitado -> nombre)==0)
                            {
                                if(strcmp(lista2 -> invitado -> dni,lista3 -> invitado -> dni)>0)
                                {
                                Invitado aux = lista2 -> invitado;
                                lista2 -> invitado = lista3 -> invitado;
                                lista3 -> invitado = aux;
                                 }

                            }
                            else
                              if(strcmp(lista2 -> invitado -> nombre,lista3 -> invitado -> nombre)>0)
                              {
                                Invitado aux = lista2 -> invitado;
                                lista2 -> invitado = lista3 -> invitado;
                                lista3 -> invitado = aux;
                               }
                      }
                      else
                      if(strcmp(lista2 -> invitado -> apellido,lista3 -> invitado -> apellido)>0)
                        {
                               Invitado aux = lista2 -> invitado;
                                lista2 -> invitado = lista3 -> invitado;
                                lista3 -> invitado = aux;

                          }

                }


}

Invitado comparacion2(Lista lista2,Lista lista3)
{   Invitado Nuevo=malloc(sizeof(_Invitado));
        Nuevo=lista2->invitado;
        if(lista2 -> invitado -> prioridad > lista3 -> invitado -> prioridad)
            {
                    Nuevo=lista3->invitado;
            }
       if(lista2 -> invitado -> prioridad==lista3 -> invitado -> prioridad)
                {
                  if(strcmp(lista2 -> invitado -> apellido,lista3 -> invitado -> apellido)==0)
                      {
                        if(strcmp(lista2 -> invitado -> nombre,lista3 -> invitado -> nombre)==0)
                            {
                                if(strcmp(lista2 -> invitado -> dni,lista3 -> invitado -> dni)>0)
                                {
                                    Nuevo=lista3->invitado;
                                 }

                            }
                            else
                              if(strcmp(lista2 -> invitado -> nombre,lista3 -> invitado -> nombre)>0)
                              {
                                    Nuevo=lista3->invitado;
                               }
                      }
                      else
                      if(strcmp(lista2 -> invitado -> apellido,lista3 -> invitado -> apellido)>0)
                        {
                                    Nuevo=lista3->invitado;

                          }

                }

return  Nuevo;
}

Lista ordenarPrioridad(Lista lista) {
    Lista lista2 = lista;
    for(; lista2; lista2 = lista2 -> sig)
    {
        for(Lista lista3 = lista2 -> sig; lista3; lista3 = lista3 -> sig)
        {
            comparacion(lista2,lista3);
        }
    }
    return lista;
}
Lista   OrdenarPrioridad2(Lista lista,Lista lista2)
{
    if(lista->sig==NULL)
    {   return lista;}

    if(lista2==NULL)    return OrdenarPrioridad2(lista->sig,lista->sig->sig);

    return OrdenarPrioridad2(lista,lista2->sig);
}

//RENOMBRAR, CREA UNA LISTA NUEVA CON TODOS LOS QUE PASAN
Lista  AAAA(Lista lista,int Total,int Prioridad,Lista Nuevo)
{
    int Largo=list_longitud(lista);



    if(Total==0&&(lista->sig)->invitado->prioridad==Prioridad)
    {printf("No hay mas lugar\n");
    return NULL;}
    if(Total==0)
    {
        printf("Se acabaron las persona de esta prioridad\nNo hay mas lugar\n");
        return NULL;
    }
    if(lista->invitado->prioridad==Prioridad&&Largo==0)
    {
        printf("Se acabaron las personas de esta prioridad\n");
        return NULL;
    }

    if(Largo==0)
    {
        printf("No hay suficientes invitados en la lista\n");
        return NULL;
    }
    if(lista->invitado->prioridad>Prioridad)
    {
        printf("Se acabaron las personas de esta prioridad\n");
        return NULL;
    }
    if(lista->invitado->prioridad!=Prioridad)   AAAA(lista->sig,Total,Prioridad,Nuevo);


         Nuevo=insertar(Nuevo,lista->invitado);
        Nuevo->sig=AAAA(lista->sig,Total-1,Prioridad,Nuevo);

return  Nuevo;
}


Lista Lista_Final(Lista lista, int Total,Lista Nuevo)
{
        if(Total==0)
        {
            return  NULL;
        }
        if(list_longitud(lista)==0)
        {
            return  NULL;
        }
        else
        {   int Prioridad;
            printf("Ingrese la prioridad deseada\n");
            scanf("%d",&Prioridad);
            Nuevo=AAAA(lista,Total,Prioridad,Nuevo);
            int Largo=list_longitud(Nuevo);         //Para no calcular 2 veces el largo
            if(Largo<Total)  Lista_Final(lista,Total-Largo,Nuevo);

                return  Nuevo;

        }
return  Nuevo;
}


int main()
{
  int Total;
  printf("Ingrese el total de invitados\n" );
  scanf("%d",&Total );
  FILE *fp=fopen("test.txt","r");
  char basura=fgetc(fp);
  basura=fgetc(fp);     //En mi pc hay 2 caracteres basura al principio
  Lista Lista_Invitados=NULL;
  Lista_Invitados=Leer(fp,Lista_Invitados);
  //mostrar(Lista_Invitados);
  Lista_Invitados=ordenarPrioridad(Lista_Invitados);
//  Lista_Invitados=Lista_Invitados->ant;
    Lista List_Final=malloc(sizeof(Nodo));
    List_Final=Lista_Final(Lista_Invitados,Total,List_Final);
    printf("Los que ingresaron(en el orden solicitado) fueron:\n");
  mostrar(List_Final);


free(Lista_Invitados);

  fclose(fp);
}
