#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100000

struct Persona
{
	char *nombre;
	char *rut;
	int cantBotellas;
};

struct Persona *buscarPersona(char *,struct Persona **);
int contarBotellas(struct Persona **,char *);
int agregarPersona(struct Persona **, struct Persona *);
char *ingresarNombre();
char *ingresarRut();
int ingresarCantBotellas();
struct Persona *crearPersona(int cantBotellas,char *,char *);
int eliminarRegistrosPersona(struct Persona **, char *);
int listarBotellasPersona(struct Persona **, char *);
int ordenarDatos(struct Persona **personas);
struct Persona ** listadoFinalPersonas (struct Persona **);
void menu(struct Persona **);
void main();

struct Persona **personas=NULL;

void main()
{
    int i;
	personas=((struct Persona**)malloc(MAX*sizeof(struct Persona*)));
	for (i=0;i<MAX;i++){personas[i]=NULL;};
	menu(personas);
}



void menu(struct Persona **personas)
{
	int opcion =0, respuesta =0;

	do
	{
		printf("%s","\n\n");
		printf("%s","1.- Agregar Persona\n");
		printf("%s","2.- Listar botellas que ha reciclado una persona\n");
		printf("%s","3.- Eliminar todos los registros de una persona\n");
		printf("%s","4.- Ordenar datos decendentemente\n");
		printf("%s","5.- Consolidar datos\n");
		printf("%s","6.- Salir\n");

		scanf("%d",&opcion);

		switch(opcion)
		{

			case 1:
				respuesta= agregarPersona(personas, crearPersona(ingresarCantBotellas(),ingresarRut(),ingresarNombre()));
				if (respuesta==0)
				{
					printf("Hubo un error. Caso1");
				}
				else
				{
					printf("La persona se agrego al sistema");
				}
				break;

			case 2:
				respuesta= listarBotellasPersona(personas,ingresarRut());
				if (respuesta==0)
				{
					printf("Hubo un error. Caso2");
				}
				break;

			case 3:
				respuesta= eliminarRegistrosPersona(personas,ingresarRut());
				if (respuesta==0)
				{
					printf("Hubo un error. Caso3");
				}
				else
				{
					printf("La persona fue eliminada");
				}
				break;

			case 4:
				respuesta= ordenarDatos(personas);
				if (respuesta==0)
				{
					printf("Hubo un error. Caso4");
				}
				else
				{
					printf("Los datos fueron ordenados");
				}
				break;

			case 5:
				;
				if (listadoFinalPersonas(personas)==NULL)
				{
					printf("Hubo un error. Caso5");
				}
				else
				{
					printf("Los datos fueron consolidados");
				}
				break;

		}
	}while(opcion!=6);
}



struct Persona *buscarPersona(char *rut,struct Persona **personas)
{
	
	int i;

    for(i=0;i<MAX;i++)
    {
        if(personas[i]!=NULL){

            if(strcmp(rut,personas[i]->rut)==0)
            {
                return personas[i];
            }
        }

    }
	
	return NULL;
}

int contarBotellas(struct Persona **personas,char *rut)
{
	int i,botellas;
	botellas=0;

	for (i=0;i<MAX;i++)
		{
			if(personas[i]!=NULL){

				if(strcmp(rut,personas[i]->rut)==0)
				{
					botellas=botellas+(personas[i]->cantBotellas);
				}
			}
		}

	return botellas;
}

int agregarPersona(struct Persona **personas, struct Persona *nuevo)
{
	int i;
	if (personas!=NULL && nuevo!=NULL)
	{
		for (i=0;i<MAX;i++)
		{
			if(personas[i]==NULL)
			{
				personas[i]=nuevo;			
				return 1;
			}
		}
	}
	return 0;
}


char *ingresarNombre(){
	char *nombre;
	char buffer[50];
	int largo;

	printf(" \n Ingrese el nombre \n ");
	scanf("%s",buffer);
	largo=strlen(buffer);
	nombre=(char*)malloc(largo*sizeof(char));
	strcpy(nombre,buffer);


	return nombre;
}

char *ingresarRut(){
	char *rut;
	char buffer[50];
	int largo;

	printf(" \nIngrese el rut  \n");
	scanf("%s",buffer);
	largo=strlen(buffer);
	rut=(char*)malloc(largo*sizeof(char));
	strcpy(rut,buffer);


	return rut;
}

int ingresarCantBotellas(){
	int cantBotellas;

	printf(" \nIngrese la cantidad de botellas  \n");
	scanf("%d",&cantBotellas);

	return cantBotellas;
}

struct Persona *crearPersona(int cantBotellas,char *rut,char *nombre)
{

	struct Persona *nuevo;
	int largo;

	nuevo=((struct Persona*)malloc(sizeof(struct Persona)));

	largo=strlen(nombre);
	nuevo->nombre=(char*)malloc(largo*sizeof(char));
	strcpy(nuevo->nombre,nombre);


	largo=strlen(rut);
	nuevo->rut=(char*)malloc(largo*sizeof(char));
	strcpy(nuevo->rut,rut);

	nuevo->cantBotellas=cantBotellas;
	
	return nuevo;
}

int eliminarRegistrosPersona(struct Persona **personas, char *rut)
{
	int i;

	if (personas!=NULL)
	{
		for (i=0;i<MAX;i++)
		{
			if(personas[i]!=NULL && strcmp(rut,personas[i]->rut)==0)
            {
				personas[i]=NULL;
            }
		}
		return 1;
	}
	return 0;
}


int listarBotellasPersona(struct Persona **personas, char *rut)
{
	int i,botellas;
	struct Persona *persona;

	persona=buscarPersona(rut,personas);

	botellas=0;
	

	if (personas!=NULL && persona!=NULL)
	{
		printf("\nNombre de la persona: %s \n",persona->nombre);
		printf("\n Tiene %d botellas \n",contarBotellas(personas,rut));
		return 1;
	}
	return 0;

}

int ordenarDatos(struct Persona **personas)
{
	int i,j,maximoBotellas,pos;
	struct Persona *aux;

	aux=((struct Persona*)malloc(sizeof(struct Persona)));

	if (personas!=NULL)
	{

		for (i=0;i<MAX-1;i++)
		{
			if (personas[i]!=NULL)
			{
				if (personas[i]->cantBotellas!=NULL)
				{
					pos=i;
					maximoBotellas=personas[i]->cantBotellas;

					for (j=i+1;j<MAX;j++)
					{

						if (personas[j]!=NULL)
						{

							if (personas[j]->cantBotellas!=NULL)
							{

								if(maximoBotellas<(personas[j]->cantBotellas))
								{
									maximoBotellas=personas[j]->cantBotellas;
									pos=j;
									
								}
							}
						}
					}
					
					aux=personas[pos];
					personas[pos]=personas[i];
					personas[i]=aux;
				}
			}			
		}
		
		printf("\nEl nuevo orden es el siguente!!:\n");
		for (i=0;i<MAX;i++)
		{
			if (personas[i]!=NULL)
			{
				printf("\n%d botellas - %s rut\n",personas[i]->cantBotellas,personas[i]->rut);
			}
		}
		return 1;
	}
	return 0;

}

//struct Persona ** listadoFinalPersonas (struct Persona **clientes){}
//A realizar
//Esta funcion debe  recibir  por  parametro  
//el  arreglo  con  el  total  de  las  personas, 
//y  debera  retornar  otro  arreglo  con  
//el consolidado de personas (sin repetirse) sumando 
//sus valores finales de botellas reutilizadas. 
//En caso de no existir Personas debe retornar null.

struct Persona ** listadoFinalPersonas (struct Persona **clientes)
{
	int i,j,contBotellas,contPersonas,respuesta;
	struct Persona **personasR=NULL;
	struct Persona **personasConsolidadas=NULL;
	char *rut;


	if (clientes!=NULL)
	{
		personasR=clientes;
	}
	contPersonas=0;

	personasConsolidadas=((struct Persona**)malloc(MAX*sizeof(struct Persona*)));

	//recorrera el arreglo, y revisará los datos de un rut diferente por cada aumento de i,
	//ya que mientra recorre con j y compara si tiene el mismo rut, sumara las botellas de la persona j al contador y despues se eliminara la persona j
	// para no volver a revisarla con el contador i
	for (i=0;i<MAX;i++)
	{

		if (personasR[i]!=NULL)
		{
			contBotellas=(personasR[i]->cantBotellas);

			for (j=i+1;j<MAX;j++)
			{
				if(personasR[j]!=NULL)
				{
					if(strcmp(personasR[j]->rut,personasR[i]->rut)==0)
					{
						contBotellas=contBotellas+(personasR[j]->cantBotellas);						
						personasR[j]=NULL;						
					}
				}

			}

			personasConsolidadas[contPersonas]=crearPersona(contBotellas,personasR[i]->rut,personasR[i]->nombre);
		
			contPersonas++;
		}		
	}

	if (contPersonas>0)
	{
		//printf("contPersonas=%d",(contPersonas));
		//printf("\nLos datos consolidados son los siguentes!!:\n");
		for (i=0;i<contPersonas;i++)
		{
			//printf("\n %s nombre - %s rut - %d botellas\n",personasConsolidadas[i]->nombre,personasConsolidadas[i]->rut,personasConsolidadas[i]->cantBotellas);			
		}
		return personasConsolidadas;
	}
	return NULL;
	
}
