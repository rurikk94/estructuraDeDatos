#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 10000

struct Alumno
{
	char *rut;
	char *nombre;
	int notas[50];
	int plibreNotas;
};

struct Alumno *buscarAlumno(char *rut,struct Alumno **alumnos)
{
	int i;

    for(i=0;i<MAX;i++)
    {
        if(alumnos[i]!=NULL){

            if(strcmp(rut,alumnos[i]->rut)==0)
            {
                return alumnos[i];
            }
        }

    }
	return NULL;
}

int agregarAlumno(struct Alumno **alumnos, struct Alumno *nuevo)
{
	int i;
	if (alumnos!=NULL && nuevo!=NULL)
	{
		if(buscarAlumno(nuevo->rut,alumnos)==NULL)
        {
            for (i=0;i<MAX;i++)
            {
                if(alumnos[i]==NULL)
                {
                    alumnos[i]=nuevo;
				
                    return 1;
                }
            }
        }

	}
	return 0;
}


int ingresarNota(){
	int nota;
	printf("\nIngrese la nota ");
	scanf("%d",&nota);
	return nota;
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

struct Alumno *crearAlumno()
{
	struct Alumno *nuevo;
	char buffer[50];
	int largo;

	nuevo=((struct Alumno*)malloc(sizeof(struct Alumno)));


	nuevo->nombre=ingregarNombre();
	nuevo->rut=ingregarRut();

	nuevo->plibreNotas=0;

	return nuevo;
}
int agregarNotaAlumno(struct Alumno **alumnos,int nota, char *rut)
{
	int i;
	if (alumnos!=NULL && nota!=NULL && buscarAlumno(rut,alumnos)!=NULL)
	{
		i=buscarAlumno(rut,alumnos)->plibreNotas;
		
		if (i<=50)
		{
			buscarAlumno(rut,alumnos)->notas[i]=nota;
			buscarAlumno(rut,alumnos)->plibreNotas++;
			return 1;
		}

	}
	return 0;

}

int mostrarAlumno(struct Alumno **alumnos, char *rut)
{
	int i,ultimo;
	if (alumnos!=NULL && buscarAlumno(rut,alumnos)!=NULL)
	{
		printf("\nNombre del alumno: %s \n",buscarAlumno(rut,alumnos)->nombre);
		ultimo=(buscarAlumno(rut,alumnos)->plibreNotas);
		if (ultimo>=0)
		{
			for (i=0;i<ultimo;i++)
			{
				printf("\n nota num %d : %d \n",i,buscarAlumno(rut,alumnos)->notas[i]);
			}
			return 1;
		}

	}
	return 0;

}

void menu(struct Alumno **alumnos)
{
	int opcion =0, respuesta =0;

	do
	{
		printf("%s","\n");
		printf("%s","1.- Agregar Alumno\n");
		printf("%s","2.- Agregar Nota a Alumno\n");
		printf("%s","3.- Buscar un Alumno por rut\n");
		printf("%s","4.- Salir\n");

		scanf("%d",&opcion);

		switch(opcion)
		{

			case 1:
				respuesta= agregarAlumno(alumnos, crearAlumno());
				if (respuesta==0)
				{
					printf("Hubo un error. Caso1");
				}
				else
				{
					printf("El alumno se agrego");
				}
				break;

			case 2:
				respuesta= agregarNotaAlumno(alumnos,ingresarNota(),ingregarRut());
				if (respuesta==0)
				{
					printf("Hubo un error. Caso2");
				}
				else
				{
					printf("La nota se agregó");
				}
				break;

			case 3:
				respuesta= mostrarAlumno(alumnos,ingregarRut());
				if (respuesta==0)
				{
					printf("No existe el rut");
				}
				break;

		}
	}while(opcion!=4);
}


struct Alumno **alumnos=NULL;

main()
{
    int i;
	alumnos=((struct Alumno**)malloc(MAX*sizeof(struct Alumno*)));
	for (i=0;i<MAX;i++){alumnos[i]=NULL;};
	menu(alumnos);
}
