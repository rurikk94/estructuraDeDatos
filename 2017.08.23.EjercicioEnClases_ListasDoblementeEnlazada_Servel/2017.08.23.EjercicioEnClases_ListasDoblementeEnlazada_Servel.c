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
int crearPersona (char *,char *);
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
				if (respuesta==0)
				{
					printf("El Diputado se agrego al sistema");
				}
				if (respuesta==-1)
				{
					printf("El Diputado ya existe");
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

int agregarDiputado(struct Servel *s,char *rut)
{
	struct NodoParlamentario *recDiputados=*s->camara->diputados; //se copia el nodo de los diputados

	if (*recDiputados==NULL) //se comprueba que exista algo, sino existe se agrega el diputado
	{
		recDiputados->persona=crearPersona(ingresarNombre(),rut);
		recDiputados->sig=NULL;
		return 1;
	}else	//si existe, se recorre hasta el final, hasta que sea null
	{
		while (recDiputados!=NULL) //se revisa si no es null
		{
			if(strcmp(rut,recDiputados->persona->rut)==0) // si exite dato, se comprueba si está repetido, si lo está finaliza -1
      	return -1;
			if (recDiputados->sig==NULL) // si el siguiente es el ultimo, se agrega el diputado al final, y finaliza 1
			{
				recDiputados->sig->persona=crearPersona(ingresarNombre(),rut);
				recDiputados->sig->sig=NULL;
				return 1;
			}
			recDiputados=recDiputados->sig //sino pasa al siguiente diputado
		}
	}
	return 0;	//si no agrega finaliza con 0
};


struct Persona *crearPersona(char *nombre,char *rut)
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

	return nuevo;
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
