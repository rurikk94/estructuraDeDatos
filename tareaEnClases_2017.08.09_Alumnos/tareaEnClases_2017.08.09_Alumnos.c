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
        if(alumnos[i]->rut)!=NULL){

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
	     if (buscarAlumno(nuevo->rut,alumnos)==NULL)
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

struct Alumno *crearAlumno()
{
	struct Alumno *nuevo;
    nuevo=((struct Alumno*)malloc(sizeof(struct Alumno)));

	char buffer[50];
	int largo;

	printf("Ingrese el nombre");
	scanf(" %[^\n]",buffer);
	largo=strlen(buffer);
	nuevo->nombre=((char *)malloc(largo*sizeof(char)));
	strcpy(nuevo->nombre,buffer);
	//printf("%s",nuevo->nombre);
	free(buffer);

	printf("Ingrese el rut");
	scanf(" %[^\n]",buffer);
	largo=strlen(buffer);
	nuevo->rut=((char *)malloc(largo*sizeof(char)));
	strcpy(nuevo->rut,buffer);
	//printf("%s",nuevo->rut);
	free(buffer);

	nuevo->plibreNotas=0;

	return nuevo;
}

int agregarNota(){
	int nota;
	printf("Ingrese la nota");
	scanf("%d",&nota);
	return nota;
}

char *ingregarRut(){
	char *rut;
	char buffer[50];
	int largo;

	printf("Ingrese el rut");
	scanf("%s",buffer);
	largo=strlen(buffer);
	rut=(char*)malloc(largo*sizeof(char));
	strcpy(rut,buffer);
	free(buffer);
	return rut;
}

int agregarNotaAlumno(struct Alumno **alumnos,int nota, char *rut)
{
	int i;
	if (alumnos!=NULL && nota!=NULL && buscarAlumno(rut,alumnos)==NULL)
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
		printf("Nombre del alumno: %s\n",buscarAlumno(rut,alumnos)->nombre);
		ultimo=(buscarAlumno(rut,alumnos)->plibreNotas)-1;
		if (ultimo>=0)
		{
			for (i=0;i<ultimo;i++)
			{
				printf("nota n° %d: %d",i,buscarAlumno(rut,alumnos)->notas[i]);
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
					printf("Hubo un error");
				}
				else
				{
					printf("El alumno se agregó");
				}

			case 2:
				respuesta= agregarNotaAlumno(alumnos,agregarNota(),ingregarRut());
				if (respuesta==0)
				{
					printf("Hubo un error");
				}
				else
				{
					printf("La nota se agregó");
				}

			case 3:
				respuesta= mostrarAlumno(alumnos,ingregarRut());
				if (respuesta==0)
				{
					printf("Hubo un error");
				}

		}
	}
	while(opcion!=4);
}


struct Alumno **alumnos;

main()
{
	alumnos=((struct Alumno**)malloc(MAX*sizeof(struct Alumno*)));
	menu(alumnos);
}
