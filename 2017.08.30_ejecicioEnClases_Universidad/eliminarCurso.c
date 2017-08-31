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


struct Curso *encontrarCursoAElimnar(struct Curso *head,int sigla)
{
	struct Curso *rec=head;

	while(rec->sig!=head)//recorre los cursos hasta que de la vuelta (el actual sea igual que el head)
	{
		//revisa si la sigla del curso es igual a la ingresada
		if (rec->sigla==sigla)
			return rec;	
		rec=rec->sig;
	}		
	return NULL;
};

int cantCursosPUCV(struct Curso *headCursos)
{
	int contadorCursos=0;
	struct Curso *rec=headCursos;
	//cuenta los cursos que existen
	while (rec->sig!=headCursos)
	{
		contadorCursos++;
		rec=rec->sig;
	}

	return contadorCursos;

}

struct Curso *otroCursoIgual(char *tipo, int creditos, struct Curso *headCursos, int sigla, int saltosADar)
{
	struct Curso *rec=headCursos;
	int i=0;
	//recore los cursos de la u, retorna un curso igual que no haya sido retornado antes (ese antes se ve por saltosADar)
	while (rec->sig!=headCursos)
	{
		if ((strcmp(rec->tipo,tipo)==0) && (rec->creditos==creditos) && (sigla!=rec->sigla) && (i>saltosADar))
			return rec;
		rec=rec->sig;
	}

	return NULL;
}

int cantCursosIguales(char *tipo, int creditos, struct Curso *headCursos, int sigla)
{
	int cantCursosIguales=0;
	struct Curso *rec=headCursos;

	//revisa los cursos, contando los cursos que son iguales, sin contar el mismo curso
	while (rec->sig!=headCursos)
	{
		if ((strcmp(rec->tipo,tipo)==0) && (rec->creditos==creditos) && (sigla!=rec->sigla))
			cantCursosIguales++;
		rec=rec->sig;
	}

	return cantCursosIguales;
}

int AlumnoTieneCurso(struct Curso **cursosAlumno, int sigla)
{
	int i;
	//revisa los cursos del alumno y ve si tiene el curso de tal sigla
	for (i=0;i<MAX;i++)
	{
		if (cursosAlumno[i]->sigla==sigla)
			return 1;
	}
	return 0;
}

int contarAlumnosDelCurso(struct NodoAlumno *headAlumnos,int sigla)
{
	struct NodoAlumno *rec=headAlumnos;
	int contadorAlumnos;
	contadorAlumnos=0;

	//recorre los alumnos contando si el alumno tiene un curso de tal sigla
	while (rec!=NULL)
	{
		if (AlumnoTieneCurso(rec->alum->cursos,sigla)==1)
			contadorAlumnos++;
		rec=rec->sig;
	}
	return contadorAlumnos;
}

void cambiarCursoDeAlumno(struct Curso **cursosAlumno,int sigla, int cantCursosIguales, struct Curso **otrosCursosIguales, int posicionCursoNuevo)
{
	int i;

	//recorre los cursos del alumno hasta encontrar el curso a cambiar y se lo cambia
	for (i=0;i<MAX;i++)
	{
		if (cursosAlumno[i]->sigla==sigla)
		{
			cursosAlumno[i]->sigla = otrosCursosIguales[posicionCursoNuevo]->sigla ;
		}
			
	}
}

void distribuirAlumnos(struct NodoAlumno *headAlumnos,struct Curso *cursos,int cantAlumnos,int sigla,int cantCursosIguales, char *tipo, int creditos)
{
	struct NodoAlumno *rec=headAlumnos;

	//crea un arreglo con los otros cursos iguales
	struct Cursos **otrosCursosIguales;
	int i;	
	int posicionCursoNuevo=0;

	otrosCursosIguales=(struct Cursos **) malloc (cantCursosIguales*sizeof(struct Cursos*));

	for (i=0;i<cantCursosIguales;i++)
	{
		otrosCursosIguales[i]=otroCursoIgual(tipo,creditos,cursos,sigla,i);
	}
	
	//recorre los alumnos que tienen el curso y le cambia el curso por el curso en la posicion posicionCursoNuevo
	while (rec!=NULL)
	{
		if(AlumnoTieneCurso(rec->alum->cursos,sigla)==1)
		{
			cambiarCursoDeAlumno(rec->alum->cursos,sigla,cantCursosIguales,otrosCursosIguales,posicionCursoNuevo);
			posicionCursoNuevo++;
			if (posicionCursoNuevo>cantCursosIguales)
				posicionCursoNuevo=0;
		}
	}
}


void eliminaElCurso(struct Curso *cursos, struct Curso *cursoAEliminar)
{
	struct Curso *rec=cursos;

	//si es el unico curso en la lista, lo cual es improbable
	if (rec==cursoAEliminar)
	{
		cursoAEliminar=NULL;
	}
	else//si hay otros cursos
	{
		//recorre hasta el anterior al eliminar
		while(rec->sig!=cursoAEliminar)
		{
			rec=rec->sig;
		}
		//enlaza al siguiente del que hay que eliminar y elimina el que hay que eliminar
		rec->sig=rec->sig->sig;
		cursoAEliminar=NULL;
	}

}

int eliminarCurso(struct Universidad *pucv,int sigla)
{
	struct Curso *existeCursoAEliminar = encontrarCursoAElimnar(pucv->cursos,sigla);
	int cantAlumnosDelCurso = contarAlumnosDelCurso(pucv->headAlumno,sigla);
	int numCursosIguales;

	//revisa si existe algo en pucv, y en cursos
	if (!pucv)
		return 0;
	if (!pucv->cursos)
		return 0;

	//revisa si el curso a elimnar existe
	if(existeCursoAEliminar!=NULL)
	{
		numCursosIguales = cantCursosIguales(existeCursoAEliminar->tipo,existeCursoAEliminar->creditos,pucv->cursos,sigla);

		//revisa si existen otros cursos
		if(cantCursosIguales>0)
		{
			//revisa si existen alumnos en el curso
			if (cantAlumnosDelCurso>0)
			{
				//distribuye los alumnos
				distribuirAlumnos(pucv->headAlumno,pucv->cursos,cantAlumnosDelCurso,sigla,numCursosIguales,existeCursoAEliminar->tipo,existeCursoAEliminar->creditos);
			}

			//despues de distribuir, elimina el curso
			eliminaElCurso(pucv->cursos,existeCursoAEliminar);
			return 1;
		}
	}
	return 0;		
};

int main()
{
	struct Universidad *pucv;
	int sigla=0;

	eliminarCurso(pucv,sigla);
	return 0;
}
