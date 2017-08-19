#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM 100

struct Alumno
{
	char *rut;
	char *nombre;
	int notas[TAM];
	struct Alumno *sig;
};

struct Alumno **alumnos=NULL;

struct Alumno * crearAlumno (char *rut, char *nombre)
{
  int i;

  struct Alumnos *nuevo =(struct Alumno *)malloc(sizeof(struct Alumno));

  nuevo->rut = (char*) malloc (strlen(rut)*sizeof(char));
	strcpy(nuevo->rut,rut);

	nuevo->nombre = (char *)malloc(strlen(nombre)*sizeof(char));
	strcpy(nuevo->nombre,nombre);

	for(i=0;i<TAM;i++)
	{
		nuevo->notas[i]=0;
	}
	nuevo->sig=null;
	return nuevo;
}

struct Alumno *buscarAlumno(char *rut,struct Alumno *head)
{
	struct Alumno *rec=head;

	while (rec!=null) {
		if (strcmp(rec->rut,rut)==0)
		{
			return rec;
		}
		rec = rec->sig;
	}
	return null;
}

int agregarAlumno(struct Alumno **head, struct Alumno *nuevo)
{
	struct Alumno *rec;

	if(*head==null)
	{
		*head = nuevo;
		return 1;
	}

	if(buscarAlumno(*head,nuevo->rut)==null)
	{
		rec=*head;
		while (rec->sig!=null)
		{
			rec=rec->sig;
		}
		rec->sig=nuevo;
		return 1;
	}
	return 0;
}

int asignarNota( struct Alumno *head, char *rut, int nota)
{
	int i;
	struct Alumno *buscado= buscarAlumno(rut,head);

	if(buscado!=null)
	{
		for (i = 0;i<TAM;i++)
		{
			if(buscado->notas[i]==0)
			{
				buscado->notas[i]=nota;
				return 1;
			}
		}
	}
	return 0;
}

float calcularPromedio (int *notas)
{
	int i,cant =0;
	float suma=0;

	for (i = 0; i < TAM; i++)
	{
		if (notas[i]!=0)
		{
			suma+=notas[i];
			cant++;
		}
	}
	if(cant>0)
		return suma/cant;
	return 0;
}

char *alumnoMayorPromedio (struct Alumno *head)
{
	struct Alumno *rec, *mayor=null;
	rec=head;

	while (rec!=null) {
		if(mayor==null && calcularPromedio(rec->notas)>0)
		{
			mayor=rec;
		}
		if (calcularPromedio(rec->notas)>calcularPromedio(mayor->notas))
		 {
			mayor=rec;
		}
		rec=rec->sig;
	}
	if(mayor!=null)
		return mayor->nombre;
	return null;
}

main()
{
	//menu(alumnos);
}
