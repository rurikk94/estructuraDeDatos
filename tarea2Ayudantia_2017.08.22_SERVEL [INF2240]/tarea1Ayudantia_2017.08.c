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


int registrarCandidato();
int crearCandidato();
char *ingresarRut();
char *ingresarNombre();
char *ingresarPartidoPolitico();
int ingresarCantidadVotos();
int agregarCandidato();
struct Candidato *buscarCandidato(struct Distrito **, char*);
int contarCandidatos();

int registrarDistrito(struct Distrito **);
int crearDistrito(struct Persona **, struct Persona *);
int
ingresarNumeroDistrito();
char *ingresarCantidadDiputados();

int registrarVoto();//ingresa nombre de candidato

int ganadoresDistrito();//de un distrito;  recibir el número del distrito y
						//la cantidad de diputados electos en dicho distrito
int porcentajeVotosCandidato();//muestra el rut y el porcentaje de votos obtenidos
int ganadoresTotales();//se muestran todos los candidatos ganadores, para esto se agregan a un arreglo aux y se muestan desde ahi
void main();


struct Distrito **distritos;

void main()
{
	int opcion=0, res,i;
	distritos=(struct Distrito**)malloc(CANT*sizeof(struct Distrito*));
	distritos=NULL;
    //for(i=0;i<28;i++)
      //  distritos[i]=NULL;
	do
	{
		printf("Menu Principal:\n");
		printf("\n");
		printf("1.-Registrar candidato\n");
		printf("2.-Registrar distrito\n");
		printf("3.-Registrar voto\n");
		printf("4.-Obtener ganadores en un distrito\n");
		printf("5.-Obtener porcentaje de votos de un candidato\n");
		printf("6.-Ganadores totales\n");
		printf("7.-Obtener la media de votantes del total de distritos\n");
		printf("8.-Obtener distrito que tiene más candidatos\n");
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
            else
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
			break;
		default:
			break;
		}

	}while(opcion!=0);

}
int ingresarNumeroDistrito()
{
    int n;
    printf("Ingrese el numero del distrito: ");
    scanf("%d",&n);
    return n;
}

int registrarCandidato(struct Distrito **distritos, char *rut, int n)
{
    int i;
    if(buscarCandidato(*distritos,rut)==NULL)
    {
        for(i=0;i<28;i++)
        {
            if(distritos[i]==NULL)
            {
                printf("i: %d",i);
                distritos[i]->numeroDistrito=ingresarNumeroDistrito();
                system("pause");
                distritos[i]->cantidadDiputados=0;
                distritos[i]->head=NULL;
                return 1;
            }
        }
    }
    return 0;
}

struct Candidato *buscarCandidato(struct Distrito *distritos, char *rut)
{
    struct Candidato *persona;
    struct NodoCandidato *rec;

    if(distritos!=NULL)
    {
        for(i=0;i<28;i++)
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
        for(i=0;i<28;i++)
        {
            if(distritos[i]==NULL)
            {
                printf("i: %d",i);
                distritos[i]->numeroDistrito=ingresarNumeroDistrito();
                system("pause");
                distritos[i]->cantidadDiputados=0;
                distritos[i]->head=NULL;
                return 1;
            }
        }
    }
    return 0;
}
