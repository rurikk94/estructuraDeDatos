#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM 100

struct Persona
{
	char *rut;
	char *nombre;
	int notas[TAM];
};

struct NodoPersona
{
	struct Persona *datos;
	struct NodoPersona *sig;
}

struct NodoPersona **personas=NULL;

struct Persona * crearPersona (char *nombre,char *rut)
{
  int i;

  struct Persona *nuevo =(struct Persona *)malloc(sizeof(struct Alumno));

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

struct NodoPersona *crearNodo (struct Persona *nuevo, struct NodoPersona *sig)
{
	struct NodoPersona *nodo=(struct NodoPersona *)malloc(sizeof(struct NodoPersona));

	nodo->datos=nuevo;
	nodo->sig=sig;
	return nodo;
}

int agregarAlComienzo(struct NodoPersona **head,struct Persona *nuevo)
{
	if (buscarAlumno(nuevo->rut,*head)==null)
	{
		*head=crearNodo(nuevo,*head);
		return 1;
	}
	return 0;
}

struct Persona *buscarAlumno(char *rut,struct NodoPersona *head)
{
	struct NodoPersona *rec=head;

	while (rec!=null) {
		if (strcmp(rec->datos->rut,rut)==0)
		{
			return rec->datos;
		}
		rec = rec->sig;
	}
	return null;
}

int agregarAlumno(struct NodoPersona **head, struct Persona *nuevo)
{
	struct NodoPersona *rec;

	if(*head==null)
	{
		*head->datos = nuevo;
		return 1;
	}

	if(buscarAlumno(nuevo->rut,*head)==null)
	{
		rec=*head;
		while (rec->sig!=null)
		{
			rec=rec->sig;
		}
		rec->sig->datos=nuevo;
		rec->sig->sig=NULL;
		return 1;
	}
	return 0;
}

int asignarNota( struct NodoPersona *head, char *rut, int nota)
{
	int i;
	struct Persona *buscado= buscarAlumno(rut,head);

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

char *alumnoMayorPromedio (struct NodoPersona *head)
{
	struct NodoPersona *rec, *mayor=null;
	rec=head;

	while (rec!=null) {
		if(mayor==null && calcularPromedio(rec->datos->notas)>0)
		{
			mayor=rec;
		}
		if (calcularPromedio(rec->datos->notas)>calcularPromedio(mayor->datos->notas))
		 {
			mayor=rec;
		}
		rec=rec->sig;
	}
	if(mayor!=null)
		return mayor->datos->nombre;
	return null;
}

main()
{
	//menu(alumnos);
}
