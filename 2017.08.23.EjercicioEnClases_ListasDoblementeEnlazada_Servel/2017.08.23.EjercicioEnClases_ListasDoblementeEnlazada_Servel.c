#include <stdio.h>
#include <stdlib.h>

struct Servel
{
	char *nombreDirector;
	struct Distrito **distritos;
	int plibreDistritos;
	struct CamraDiputados *camara;
};

struct Distrito
{
	int numero;
	char *nombre;
	struct NodoCandidato *candidato;
};

struct CamaraDiputados
{
	char *nombrePresidente;
	struct NodoParlamentario *diputados;
};

struct NodoCandidato
{
	struct Persona *persona;
	struct NodoCandidato *ant, *sig; //lista circular doblemente enlazada
};

struct NodoParlamentario
{
	struct Persona *persona;
	struct NodoParlamentario *sig;
};

struct Persona
{
	char *nombre;
	char *rut;
};

int agregarDiputado(struct Servel *,char *);
int numeroDistritoConMasDiputado(struct Servel *);
char *ingresarNombre();
char *ingresarRut();
void menu(struct Servel *);
void main();

struct Servel *s;

void main();
{
	int i;
	s=((struct Servel*)malloc(sizeof(struct Servel*)));
	menu(s);
}

void menu(struct Servel *s)
{

	int opcion =0, respuesta =0;

	do
	{
		printf("%s","\n\n");
		printf("%s","1.- Agregar Diputado\n");
		printf("%s","2.- Mostrar Distrito con mas Diputados\n");
		printf("%s","0.- Salir\n");

		scanf("%d",&opcion);

		switch(opcion)
		{

			case 1:
				respuesta= agregarDiputado(s, ingresarRut());
				if (respuesta==0)
				{
					printf("Hubo un error. Caso1");
				}
				else
				{
					printf("El Diputado se agrego al sistema");
				}
				break;

			case 2:
				respuesta= numeroDistritoConMasDiputado(s);
				if (respuesta==-1)
				{
					printf("Hubo un error. Caso 2");
				}
				if (respuesta==0)
				{
					printf("Ninguna Distrito tiene Diputados");
				}
				break;
		}
}while(opcion!=0);
};
