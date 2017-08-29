#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#define CANT 28

struct Candidato
{
	char *rut;
	char *nombre;
	char *partidoPolitico;
	int cantidadVotos;
};

struct NodoCandidato
{
	struct Candidato *candidato;
	struct NodoCandidato *sig;
};

struct Distrito
{
	int numeroDistrito;
	int cantidadDiputados;
	struct NodoCandidato *head;
};


int registrarCandidato(struct Distrito **, char *, int);
struct Candidato *crearCandidato(char*,char*,char*,int);
char *ingresarRut();
char *ingresarNombre();
char *ingresarPartido();
int ingresarCantidadVotos();
struct NodoCandidato *CrearNodoCandidato(struct Candidato *, struct NodoCandidato *);
struct Candidato *buscarCandidato(struct Distrito **, char*);
int contarCandidatos();

int registrarDistrito(struct Distrito **);
struct Distrito *crearDistrito(int);
int ingresarNumeroDistrito();

char *ingresarCantidadDiputados();

int registrarVoto();//ingresa nombre de candidato

int ganadoresDistrito();//de un distrito;  recibir el nÃºmero del distrito y
						//la cantidad de diputados electos en dicho distrito
int porcentajeVotosCandidato();//muestra el rut y el porcentaje de votos obtenidos
int ganadoresTotales();//se muestran todos los candidatos ganadores, para esto se agregan a un arreglo aux y se muestan desde ahi
int distritoMasCandidatos();//no se ingresa nada, muestra el num de Distrito con mas candidatos
void main();


struct Distrito **distritos;

void main()
{
	int opcion=0, res,i;
	distritos=(struct Distrito**)malloc(CANT*sizeof(struct Distrito*));
	//distritos=NULL;
    for(i=0;i<CANT;i++)
        distritos[i]=NULL;

	do
	{
		printf("Menu Principal:\n");
		printf("\n");
		printf("1.-Registrar candidato\n");
		printf("2.-Registrar distrito\n");
		printf("3.-Registrar voto\n");
		printf("4.-Obtener ganadores en un distrito\n"); //asdqwe
		printf("5.-Obtener porcentaje de votos de un candidato\n");
		printf("6.-Ganadores totales\n");
		printf("7.-Obtener la media de votantes del total de distritos\n");
		printf("8.-Obtener distrito que tiene mÃ¡s candidatos\n"); // asdqwe
		printf("0.-Salir\n");
		scanf("%d",&opcion);

		switch(opcion)
		{
		case 1:
		    res=registrarCandidato(distritos,ingresarRut(),ingresarNumeroDistrito());
		    if(res==0)
            {
                printf("Error en registro del candidato");
            }
            if(res==1)
            {
                printf("Se registro el candidato");
            }
			break;
		case 2:
		    res=registrarDistrito(distritos);
		    if(res==0)
            {
                printf("Error en registro del distrito");
            }
            else
            {
                printf("Se registro el distrito");
            }
			break;
		case 3:
			break;
		case 4:
			break;
		case 5:
			break;
		case 6:
			break;
		case 7:
			break;
		case 8:
			res=distritoMasCandidatos(distritos);
		    if(res==0)
            {
                printf("Ningun distrito tiene participantes");
            }
            else
            {
				if (res==-1)
				{ printf("Hubo un error en los datos");}
				else
				{
					printf("Se registro el distrito");
				}
            }
			break;
		default:
			break;
		}

	}while(opcion!=0);

}

int distritoMasCandidatos(struct Distrito **distritos)
{
	int i,numDistritoMayor,cantMayor;
	
	numDistritoMayor=0;
	cantMayor=0;

	for (i=0;i<CANT;i++)
	{
		if (distritos[i]!=NULL)
		{
			if (cantMayor<contarCandidatosDelDistrito(distritos[i]->head))//recorre la lista de NodoCandidatos del distrito i, y devuelve la cantidad de candidatos
				cantMayor=contarCandidatosDelDistrito(distritos[i]->head);
				numDistritoMayor=distritos[i]->numeroDistrito;
		}
	}


}

int contarCandidatosDelDistrito(struct NodoCandidato *head)
{
	struct NodoCandidato *rec=head;
	int cont;
	cont =0;

	while(rec!=NULL)
	{
		cont++;
		rec=rec->sig;
	}
	return cont;
}

int registrarCandidato(struct Distrito **distritos, char *rut, int n)
{
    int i,largo;
    if(buscarCandidato(*distritos,rut)==NULL)
    {
        for(i=0;i<CANT;i++)
        {
			if (distritos[i]!=NULL)
			{
				if (distritos[i]->numeroDistrito==n)
				{
					if(1==agregoCandidatoAlNodo(distritos[i]->head,crearCandidato(rut,ingresarNombre(),ingresarPartido(),0)))
					{
						distritos[i]->cantidadDiputados++;
						return 1;//se agregó

					}
				}
			}
        }
    }
    return 0;
}

int agregoCandidatoAlNodo(struct NodoCandidato *headCandidatos,struct Candidato *nuevo)
{
	struct NodoCandidato *rec=headCandidatos;
	

	if (headCandidatos==NULL)
	{
		rec=CrearNodoCandidato(nuevo,NULL);
		return 1;
	}
	else
	{

		while(rec!=NULL)
		{
			if (rec->sig==NULL)
			{
				rec->sig=CrearNodoCandidato(nuevo,NULL);
				return 1;
			}
			rec=rec->sig;
		}
	}
	return 0;
}

struct NodoCandidato *CrearNodoCandidato(struct Candidato *candidato, struct NodoCandidato *sig)
{
	struct NodoCandidato *nuevoNodo;

	nuevoNodo=(struct NodoCandidato*)malloc(sizeof(struct NodoCandidato));
	nuevoNodo->sig=NULL;
	nuevoNodo->candidato=candidato;

	return nuevoNodo;
}

struct Candidato *buscarCandidato(struct Distrito **distritos, char *rut)
{
    struct Candidato *persona;
    struct NodoCandidato *rec;
    int i;

    if(distritos!=NULL)
    {
        for(i=0;i<CANT;i++)
        {
            if(distritos[i]!=NULL)
            {
                rec=distritos[i]->head;

                while(rec!=NULL)
                {
                    if(strcmp(rec->candidato->rut,rut)==0)
                    {
                        persona = rec->candidato;
                        return persona;
                    }
					rec=rec->sig;
                }
            }
        }
    }
    return NULL;
}

int registrarDistrito(struct Distrito **distritos)
{
    int n, m, i;
    if(distritos!=NULL)
    {
        for(i=0;i<CANT;i++) 
        {
            if(distritos[i]==NULL)
            {
				distritos[i]=crearDistrito(ingresarNumeroDistrito());
                return 1;
            }
        }
    }
    return 0;
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

char *ingresarPartido(){
	char *nombre;
	char buffer[50];
	int largo;

	printf(" \n Ingrese el partido \n ");
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

int ingresarNumeroDistrito(){
	int num;

	printf(" \nIngrese num de distrito\n");
	scanf("%d",&num);

	return num;
}

struct Candidato *crearCandidato(char *rut,char *nombre,char *partido,int votos)
{
	struct Candidato *nuevo=(struct Candidato *)malloc(sizeof(struct Candidato));
	int largo;

	nuevo->rut;
	largo=strlen(rut);
	nuevo->rut=(char*)malloc(largo*sizeof(char));
	strcpy(nuevo->rut,rut);

	largo=strlen(nombre);
	nuevo->nombre=(char*)malloc(largo*sizeof(char));
	strcpy(nuevo->nombre,nombre);

	largo=strlen(partido);
	nuevo->partidoPolitico=(char*)malloc(largo*sizeof(char));
	strcpy(nuevo->partidoPolitico,partido);

	nuevo->cantidadVotos=votos;

	return nuevo;

}

struct Distrito *crearDistrito(int numDist)
{
	struct Distrito *nuevoDistrito=(struct Distrito *)malloc(sizeof(struct Distrito));

	nuevoDistrito->numeroDistrito=numDist;
	nuevoDistrito->cantidadDiputados=0;
	nuevoDistrito->head=NULL;

	return nuevoDistrito;
}
