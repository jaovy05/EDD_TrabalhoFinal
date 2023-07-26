struct data
{
    int minutos;
    int horas;
    int dia;
    int mes;
    long long int ano;
};
typedef struct data Data;

struct evento
{
    char descricao[100];
    int duracaoh;
    int duracaom;
    Data data;
    long long int inicio;
    long long int fim;
    struct evento *left;
    struct evento *right;
};
typedef struct evento Evento;

struct broto
{
    Evento* no;
};
typedef struct broto Raiz;

void incluir(Raiz* head);
void listar(Evento* raiz);
void sair(Evento* raiz);
void consultar(Raiz* raiz);
void alterar(Evento* raiz);
void excluir(Raiz* raiz);

void transformador(Evento* raiz);
int confData(Data data);
Evento* adubo(Evento* raiz, Evento* broto);
Evento *busca(Evento* raiz, Evento* alvo);
Data setdata(int tipo);
void buscaAll(Evento* raiz, Evento* alvo);
Evento*removido(Evento* raiz, Evento* alvo);
void imprimir(Evento* raiz);
int diasnoMes(int mes, int ano);