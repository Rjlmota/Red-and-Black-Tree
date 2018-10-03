#include <stack>
#include "no.h"
using namespace std;

class arvore    //Classe para modelar a �rvore
   {
   private:
      no* pRaiz;   //Ponteiro para o n� pRaiz            

   public:

      arvore();  //Construtor

      ~arvore();  //Destrutor

      void destruirDados(no* pRaizLocal);  //Fun��o a ser usada pelo
                                           //destrutor
      no* procurar(int chave);  //Fun��o p/ procurar um n�

      no* procurar (int chave, no * & pPrevio, char & direcao); //Usada pelo m�todo
                                                                //para remover

      void inserir(int va);  //Fun��o p/inserir um n�

      void percorrer();  //Fun��o p/percorrer a �rvore

      void ascendente(no* pRaizLocal);  //Fun��o a ser usada por 
                                        //percorrer
      bool remover(int chave);  //Fun��o para remover um n�

      void mostrararvore();  //Fun��o p/mostrar a �rvore na tela
      
};


arvore::arvore()
{
    pRaiz=NULL;         
}

arvore::~arvore()                         
{
    destruirDados(pRaiz);
}         

void arvore::destruirDados(no* pRaizLocal)      
{                                   
      if(pRaizLocal != NULL)
         {                                
         destruirDados(pRaizLocal->pFilhoEsquerda);  
         destruirDados(pRaizLocal->pFilhoDireita); 
         delete pRaizLocal;               
         }
}


no* arvore::procurar(int chave)          
{                         
      no* pAtual = pRaiz;             
      while(pAtual->pegarValor() != chave)       
         {
         if(chave < pAtual->pegarValor())        
            pAtual = pAtual->pFilhoEsquerda;
         else                             
            pAtual = pAtual->pFilhoDireita;
         if(pAtual == NULL)             
            return NULL;                  
         }
      return pAtual;                    
}  

void arvore::inserir(int va) 
{
      no* pNovoNo = new no(va);          
              

      if(pRaiz==NULL)                     
         pRaiz = pNovoNo;
      else                                
         {
         no* pAtual = pRaiz;          
         no* pPai;
         while(true)                      
            {
            pPai = pAtual;
            if(va < pAtual->pegarValor())      
               {
               pAtual = pAtual->pFilhoEsquerda;
               if(pAtual == NULL)       
                  {                       
                  pPai->pFilhoEsquerda = pNovoNo;
                  return;
                  }
               }  
            else                          
               {
               pAtual = pAtual->pFilhoDireita;
               if(pAtual == NULL)       
                  {                       
                  pPai->pFilhoDireita = pNovoNo;
                  return;
                  }
               }  
            }  
         }  
}  

void arvore::percorrer()
{
        ascendente(pRaiz);
}

void arvore::ascendente(no* pRaizLocal)
{
      if(pRaizLocal != NULL)
         {
         ascendente(pRaizLocal->pFilhoEsquerda);
         cout << pRaizLocal->pegarValor() << " ";    
         ascendente(pRaizLocal->pFilhoDireita);   
         }
}

void arvore::mostrararvore()
{
      stack<no*> pilhaGlobal;
      pilhaGlobal.push(pRaiz);
      int nVazios = 32;
      bool linhaVazia = false;

      cout << endl;
      while(linhaVazia==false)
         {
         stack<no*> pilhaLocal;
         linhaVazia = true;

         for(int j=0; j<nVazios; j++)
            cout << ' ';

         while(pilhaGlobal.empty()==false)
            {
            no* temp = pilhaGlobal.top();
            pilhaGlobal.pop();
            if(temp != NULL)
               {
               cout << temp->pegarValor();
               pilhaLocal.push(temp->pFilhoEsquerda);
               pilhaLocal.push(temp->pFilhoDireita);

               if(temp->pFilhoEsquerda != NULL || temp->pFilhoDireita != NULL)
                  linhaVazia = false;
               }
            else
               {
               cout << "--";
               pilhaLocal.push(NULL);
               pilhaLocal.push(NULL);
               }
            for(int j=0; j<nVazios*2-2; j++)
               cout << ' ';
            }  
         cout << endl;
         nVazios = nVazios/2;
         while(pilhaLocal.empty()==false)
            {
            pilhaGlobal.push( pilhaLocal.top() );
            pilhaLocal.pop();
            }
         }  

      cout << endl;
}  

bool arvore::remover (int chave)
{
    no * pPrevio = NULL;  // Usado para armazenar o pai do no achado
    char direcao;
    no * oNo = procurar (chave, pPrevio, direcao);
    
    if (oNo == NULL)
        return false; // chave n�o achada na �rvore
        
    // se n�o h� nenhum filho, atribui NULL ao no
    if (oNo->pegarFilhoDireita() == NULL && oNo->pegarFilhoEsquerda() == NULL)
    {
        if (oNo == pRaiz) 
            pRaiz = NULL; // arvore vazia
        else
            if (direcao == 'd')
                pPrevio->atribuirFilhoDireita(NULL);
            else
                pPrevio->atribuirFilhoEsquerda(NULL);
    }
    // sub-�rvore direita, mas nenhuma sub-�rvore esquerda
    else if (oNo->pegarFilhoDireita() != NULL && oNo->pegarFilhoEsquerda() == NULL)
    {
        no * subarvore = oNo->pegarFilhoDireita();
        if (oNo == pRaiz)
            pRaiz = subarvore;
        else
        {
            if (direcao == 'd')
                pPrevio->atribuirFilhoDireita(subarvore);
            else
                pPrevio->atribuirFilhoEsquerda(subarvore);
        }
    }
    // sub-�rvore esquerda, mas nenhuma sub-�rvore direita
    else if (oNo->pegarFilhoDireita() == NULL && oNo->pegarFilhoEsquerda() != NULL)
    {
        no * subarvore = oNo->pegarFilhoEsquerda(); 
        if (oNo == pRaiz)
            pRaiz = subarvore;
        else    
        {
            if (direcao == 'd')
                pPrevio->atribuirFilhoDireita(subarvore);
            else
                pPrevio->atribuirFilhoEsquerda(subarvore);
        }
    }
    else // deve ter sub-�rvores direita e esquerda
    {
        no* pProximo;
        no* pAtual = oNo->pegarFilhoEsquerda();
        if (pAtual->pegarFilhoDireita() != NULL) // se existir uma sub-�rvore direita do filho esquerdo...
        {
            pProximo = pAtual->pegarFilhoDireita();
            while (pProximo->pegarFilhoDireita() != NULL) // procurar ultimo filho da direita
            {
                pAtual = pProximo;
                pProximo = pAtual->pegarFilhoDireita();
            }  
            
            // substituir no retirado pelo no achado
            pAtual->atribuirFilhoDireita (pProximo->pegarFilhoEsquerda());
            pProximo->atribuirFilhoEsquerda (oNo->pegarFilhoEsquerda());
            pProximo->atribuirFilhoDireita (oNo->pegarFilhoDireita());
            // atribuir ponteiros pais
            if (oNo != pRaiz)
                if (direcao == 'e')
                    pPrevio->atribuirFilhoEsquerda (pProximo);
                else
                    pPrevio->atribuirFilhoDireita (pProximo);
            else pRaiz = pProximo;
        }
        // se n�o existir sub-�rvore direita, substituir por filho esquerdo
        else
        {
            pProximo = pAtual;
            pProximo->atribuirFilhoDireita (oNo->pegarFilhoDireita());
            if (oNo != pRaiz)
                if (direcao == 'e')
                    pPrevio->atribuirFilhoEsquerda (pProximo);
                else
                    pPrevio->atribuirFilhoDireita (pProximo);
            else pRaiz = pProximo;
        }       
    }
    
    // remove o no da mem�ria
    delete oNo;
    return true;
}

no * arvore::procurar (int chave, no * & pPrevio, char & direcao)
{
    no * pAtual;
    
    if (pRaiz) // Checagem para verificar se existe pelo menos um no
    {
        pAtual = pRaiz;
        pPrevio = pAtual;
        while (pAtual!=NULL) // Enquanto o ponteiro n�o for NULL
        {
            int pAtualChave;
            pAtualChave = pAtual->pegarValor();
            if (pAtualChave == chave)
                return pAtual; // retorna o ponteiro para o objeto no
            // se menor, vai para o lado direito
            if (pAtualChave < chave)
            {
                pPrevio = pAtual;
                direcao = 'd';
                pAtual = pAtual->pegarFilhoDireita();
            }
            // se maior, vai para o lado esquerdo
            else
            {
                pPrevio = pAtual;
                direcao = 'e';
                pAtual = pAtual->pegarFilhoEsquerda();
            }
        }
    }
    return 0;
};
