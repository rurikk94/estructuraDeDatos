#include <stdio.h>
#include <string.h>

#define MAX 10

struct Evaluacion
{
	char *fecha;
	float promedio;
};

struct NodoEvaluacion
{
	struct Evaluacion *eval;
	struct NodoEvaluacion *sig;
};

struct Curso
{
	int sigla;
	char *tipo;
	char *nombre;
	int creditos;
	struct NodoEvaluacion *head;
	struct Curso *sig;
};
struct Alumno
{
	char *rut;
	char *nombre;
	struct Curso **cursos;
};
struct NodoAlumno
{
	struct Alumno *alum;
	struct NodoAlumno *sig;
};
struct Universidad
{
	char *rector;
	struct Curso *cursos;
	struct NodoAlumno *headAlumno;
};


int contarAlumnosPUCV(struct NodoAlumno *headAlumno)
{
	struct NodoAlumno *rec=headAlumno;
	int cont=0;

	//recorre alumnos
	while (rec!=NULL)
	{
		cont++;
		rec=rec->sig;
	}
	return cont;

}

float promedioCreditosCursosAlumno(struct Curso **cursos)
{
	int i;
	int suma=0;
	int cantRamos=0;
	float promedio=0;

	for (i=0;i<MAX;i++)
	{
		if (cursos[i]!=NULL)
		{
			suma+=cursos[i]->creditos;
			cantRamos++;
		}
	}

	promedio = (float)suma / (float)cantRamos;
	return promedio;
}

float promedioCreditosCursados(struct Universidad *pucv)
{
	struct NodoAlumno *rec=pucv->headAlumno;
	int cantAlumnos=contarAlumnosPUCV(pucv->headAlumno);
	float suma=0;
	float promedio;

	//recorre alumnos
	while (rec!=NULL)
	{
		suma+=promedioCreditosCursosAlumno(rec->alum);
		rec=rec->sig;
	}

	promedio = (float)suma / (float)cantAlumnos;
	return promedio;
}

int main()
{
	struct Universidad *pucv;
	int sigla=0;

	promedioCreditosCursados(pucv);
	return 0;
}