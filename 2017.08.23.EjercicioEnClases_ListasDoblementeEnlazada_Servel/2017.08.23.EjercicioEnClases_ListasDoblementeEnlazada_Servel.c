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
struct Persona *buscarCandidato(struct Servel *,char *);
struct Persona *compararCandidatoRut(struct NodoCandidato *, char *)
char *ingresarNombre();
char *ingresarRut();
int contarDiputados(struct NodoCandidato *)
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
				else
				{
					printf("El Distrito %d tiene mas Diputados",respuesta);
				}
				break;
		}
	}while(opcion!=0);
};

int numeroDistritoConMasDiputado(struct Servel *s)
{
	int i,numDistrito,masDiputados=0,cont=0;

	if(*s->plibreDistritos>0)//deberia bastar con plibreDistritos>0
	{
		for (i = 0; i < plibreDistritos; i++)
		{
			if (*s->distritos[i]!=NULL)//comprueba si esa posicion del arreglo existen datos, si existen...
			{
				if (masDiputados<contarDiputados(*s->distritos[i]->candidato))
				{
					masDiputados=contarDiputados(*s->distritos[i]->candidato);
					numDistrito=*s->distritos[i]->numero;
				}
			}
		}
		return numDistrito;
	}
	return -1
};

int contarDiputados(struct NodoCandidato *candidato)
{
	struct NodoCandidato *rec=*candidato;
	int cont=0;

	while (rec!=NULL) { //si existen candidatos
		cont++;//lo cuenta
		if (rec->sig!=candidato)// si no vuelvo al primer candidato
		{
			rec=rec->sig;//avanzo al siguiente
		}
	}
	return cont;
};

int agregarDiputado(struct Servel *s,char *rut)
{
	struct NodoParlamentario *recDiputados=*s->camara->diputados; //se copia el nodo de los diputados
	
	if (*s!= NULL && buscarCandidato(s,rut)!=NULL && camara!= NULL)
		//se comprueba que exista s, el candidato, camara
	{
		if (*recDiputados==NULL)
		{//si no hay diputados, se agrega al principio
		recDiputados->persona=buscarCandidato(s,rut);//devuelve una Persona;
		recDiputados->sig=NULL;
		return 1;			
		}
		else	//si existe diputados, se recorre hasta el final
		{
			while (recDiputados!=NULL)
			{
				if(strcmp(rut,recDiputados->persona->rut)==0) //se comprueba si no está repetido, si lo está finaliza -1
			return -1;
				if (recDiputados->sig==NULL) // si el siguiente es el ultimo, se agrega, y finaliza 1
				{
					recDiputados->sig->persona=buscarCandidato(s,rut);//asigna el candidato con ese rut en diputados
					recDiputados->sig->sig=NULL;
					return 1;
				}
				recDiputados=recDiputados->sig //sino pasa al siguiente diputado
			}
		}
	}
	return 0;	//si no agrega finaliza con 0
};


struct Persona *buscarCandidato(struct Servel *s,char *rut)
{
	int i;

	if(*s!= NULL && *s->plibreDistritos>0)//si existen distritos
	{
		for (i = 0; i < plibreDistritos; i++)//los recorre
		{
			if (*s->distritos[i]!=NULL)//comprueba si en esa posicion del arreglo existen datos
			{
				if(compararCandidatoRut(*s->distritos[i],rut)!=NULL)//revisa si algun candidato tiene ese rut
				{
					return compararCandidatoRut(*s->distritos[i],rut);//devuelve ese candidato
				}
			}
			i++;
		}
	}
	return NULL;
};

struct Persona *compararCandidatoRut(struct NodoCandidato *candidato, char *rut)
{
	struct NodoCandidato *rec=*candidato;
	if (rec!=NULL)
	{
		while (rec->sig!=candidato)
			if((strcmp(rec->persona->rut,rut)==0)
			{
				return rec->persona;
			}
			rec=rec->sig;
	}	
	return NULL
}

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

char *ingresarRut(){
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
