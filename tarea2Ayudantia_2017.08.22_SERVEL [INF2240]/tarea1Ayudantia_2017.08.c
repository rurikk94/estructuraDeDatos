#include <stdio.h>
#include <stdlib.h>
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
char *ingresarCantidadVotos();
int agregarCandidato();
int buscarCandidato();
int contarCandidatos();

int registrarDistrito();
int crearDistrito(struct Persona **, struct Persona *);
char *ingresarNumeroDistrito();
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
	int opcion=0;
	distritos=(struct Distrito**)malloc(CANT*sizeof(struct Distrito*));

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
		scanf("%d, &opcion");

		switch(opcion)
		{
		case 1:
			break;
		case 2:
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