#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 10000

struct Persona
{
	char *nombre;
	char *rut;
	int cantBotellas;
};

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

					printf("\n i = %d",i);
					printf("\n b = %d en este registo",personas[i]->cantBotellas);

					botellas=botellas+(personas[i]->cantBotellas);

					printf("\n t = %d botellas en total en %d vuelta\n",botellas,i);
				}
			}
		}

	system("pause");

	printf("\n saliendo de contar botellas \n");
	printf("\n hay  %d botellas \n",botellas);
	system("pause");

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


char *ingregarNombre(){
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

char *ingregarRut(){
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

int ingregarCantBotellas(){
	int cantBotellas;

	printf(" \nIngrese la cantidad de botellas  \n");
	scanf("%d",&cantBotellas);

	return cantBotellas;
}

struct Persona *crearPersona()
{
	struct Persona *nuevo;
	char buffer[50];
	int largo;

	nuevo=((struct Persona*)malloc(sizeof(struct Persona)));


	nuevo->nombre=ingregarNombre();
	nuevo->rut=ingregarRut();
	nuevo->cantBotellas=ingregarCantBotellas();


	return nuevo;
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

void menu(struct Persona **personas)
{
	int opcion =0, respuesta =0;

	do
	{
		printf("%s","\n");
		printf("%s","1.- Agregar Persona\n");
		printf("%s","2.- Listar botellas que ha reciclado una persona\n");
		printf("%s","3.- Eliminar registros de una persona\n");
		printf("%s","4.- Ordenar datos decendentemente\n");
		printf("%s","5.- Salir\n");

		scanf("%d",&opcion);

		switch(opcion)
		{

			case 1:
				respuesta= agregarPersona(personas, crearPersona());
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
				respuesta= listarBotellasPersona(personas,ingregarRut());
				if (respuesta==0)
				{
					printf("Hubo un error. Caso2");
				}
				break;

		}
	}while(opcion!=5);
}


struct Persona **personas=NULL;

main()
{
    int i;
	personas=((struct Persona**)malloc(MAX*sizeof(struct Persona*)));
	for (i=0;i<MAX;i++){personas[i]=NULL;};
	menu(personas);
}
