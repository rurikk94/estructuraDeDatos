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
	scanf("%s",&cantBotellas);

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
