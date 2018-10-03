using namespace std;
class no   //Classe que ser� usada para instanciar os n�s
{
   public:
      int valor;    //Numero que sera armazenado               
            
      no* pFilhoEsquerda;  //Ponteiro p/filho da esquerda
      no* pFilhoDireita;   //Ponteiro p/filho da direita

      no();   //Construtor

      no(int v);

      ~no();  //Destrutor

      void mostrarno();  //Funcao para mostrar o conte�do
      int pegarValor();
      no* pegarFilhoEsquerda();
      no* pegarFilhoDireita();
      void atribuirFilhoDireita(no* p);
      void atribuirFilhoEsquerda(no* p);
};

no::no()
{
    valor=0;
    pFilhoEsquerda=NULL;
    pFilhoDireita=NULL;
}

no::no(int v)
{
    valor=v;
    pFilhoEsquerda=NULL;
    pFilhoDireita=NULL;
}

no::~no()
{}

void no::mostrarno()        
{
    cout << valor;
}

int no::pegarValor()
{
    return valor;
}

no* no::pegarFilhoEsquerda()
{
    return pFilhoEsquerda;
}

no* no::pegarFilhoDireita()
{
    return pFilhoDireita;
}

void no::atribuirFilhoDireita(no* p)
{
    pFilhoDireita = p;
}

void no::atribuirFilhoEsquerda(no* p)
{
    pFilhoEsquerda = p;
}
