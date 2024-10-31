#include <iostream>
#include <windows.h>
#include <conio.h>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
///Função que auxilia na colisão de blocos
void Inverte (int&bolaX,int&bolaY,int&direcaoX,int&direcaoY,int m[22][22],int&pontos)
{
    direcaoX= -direcaoX; //inverte sentido
    direcaoY = (rand() % 3) -1;//randomiza direção
    if (m[bolaX+direcaoX][bolaY+direcaoY]==2) ///Se na nova direção há um bloco
    {
        m[bolaX+direcaoX][bolaY+direcaoY]=3;//Tira o bloco
        pontos+= 3; //Adiciona três pontos
        return Inverte (bolaX,bolaY,direcaoX,direcaoY,m,pontos); //Colide
    }

}
///Função que auxilia na colisão de paredes
void Inverte (int&bolaX,int&bolaY,int&direcaoX,int&direcaoY,int m[22][22])
{
    direcaoX= -direcaoX; //inverte sentido
    direcaoY = (rand() % 3) -1;//randomiza direção
    if (m[bolaX+direcaoX][bolaY+direcaoY]==1) //Se na nova direção há uma parede
    {
        direcaoY=(rand()%2)?-direcaoY:0;//tenta outras
    }

}
///Detecta colisão com blocos, e remove
void Colisao (int&bolaX,int&bolaY,int&direcaoX,int&direcaoY,int m[22][22],int&pontos)
{
    if (m[bolaX+direcaoX][bolaY]==2) ///Se há uma colisão vertical
    {
        m[bolaX+direcaoX][bolaY]=3;//Tira o bloco
        pontos+= 3; //Adiciona três pontos
        Inverte (bolaX,bolaY,direcaoX,direcaoY,m,pontos); //Colide
        return; //sai
    }
    if (m[bolaX][bolaY+direcaoY]==2)    ///Se há uma colisão lateral
    {
        m[bolaX][bolaY+direcaoY]=3;//Tira o bloco
        pontos+= 3; //Adiciona três pontos
        direcaoY= -direcaoY;//inverte direção
        return; //sai
    }
    if (m[bolaX+direcaoX][bolaY+direcaoY]==2)   ///Se há uma colisão diagonal
    {
        m[bolaX+direcaoX][bolaY+direcaoY]=3;//Tira o bloco
        pontos+= 3; //Adiciona três pontos
        Inverte (bolaX,bolaY,direcaoX,direcaoY,m,pontos); //Colide
        return; //sai
    }
    if (m[bolaX][bolaY] == 2)     ///Entrou em um bloco
    {
        m[bolaX][bolaY] = 3; //Remove o bloco
        pontos += 3; //Pontos
        Inverte (bolaX,bolaY,direcaoX,direcaoY,m,pontos); //Colide
        return; //sai
    }
}
///Detecta colisão com paredes
void Colisao (int&bolaX,int&bolaY,int&direcaoX,int&direcaoY,int m[22][22])
{
    if (m[bolaX+direcaoX][bolaY]==1) ///Se há uma colisão vertical
    {
        return Inverte (bolaX,bolaY,direcaoX,direcaoY,m); //Colide
    }
    else if (m[bolaX][bolaY+direcaoY]==1)    ///Se há uma colisão lateral
    {
        direcaoY= -direcaoY;//inverte direção
        return; //sai
    }
    else if (m[bolaX+direcaoX][bolaY+direcaoY]==1)   ///Se há uma colisão diagonal
    {
        return Inverte (bolaX,bolaY,direcaoX,direcaoY,m); //Colide
    }
    else if (m[bolaX][bolaY] == 1)    ///Entrou em uma parede
    {
        if (direcaoY>0)   //Vindo da esquerda
        {
            bolaY--; //Força 1 para esquerda
            return Inverte (bolaX,bolaY,direcaoX,direcaoY,m); //Colide
        }
        else if (direcaoY<0)    //Vindo da direita
        {
            bolaY++; //Força 1 para direita
            return Inverte (bolaX,bolaY,direcaoX,direcaoY,m); //Colide
        }
        else if (direcaoX>0)   //Se vem de cima
        {
            bolaX--; //Força um para cima
            return Inverte (bolaX,bolaY,direcaoX,direcaoY,m); //Colide
        }
        else if (direcaoX<0)   //Se vem de baixo
        {
            bolaX++;//Força um para baixo
            return Inverte (bolaX,bolaY,direcaoX,direcaoY,m); //Colide
        }
    }
}
///Função do menu
void menuInicial (int&menu,string&nome)
{
    cout<<"\nBEM VINDO AO ARKANOID LITE, "<<nome<<"!\n\nMENU\n\n[ 1 ] JOGAR\n[ 2 ] ESCOLHER A DIFICULDADE\n[ 3 ] SOBRE E COMO JOGAR\n[ 4 ] RANK TOP 5\n[ 5 ] SAIR\n"<< endl;
    cin>>menu;
}
///Função que salva as variáveis em um arquivo
void salvandoPontos(string nome,int dificuldade,int pontos,int alvo,int vidas,int vidasAUX,int fase,int minutos,int segundos,int segundos2)
{
    ofstream arquivo("pontuacoes.txt", ios::app); // Abre o arquivo para adicionar dados
    if (arquivo.is_open())
    {
        // Salva todas as variáveis no arquivo
        arquivo<<nome<<" "<<dificuldade<<" "<<pontos<<" "<<alvo<<" "<<vidas<<" "<<vidasAUX<< " "<<fase<<" "<<minutos<<" "<<segundos2<<" "<<segundos<<"\n\n";
        arquivo.close(); // Fecha o arquivo
    }
    else
    {
        cout<<"Erro, pontuação não salva!\nSinto muito, "<<nome<<"\n\n";
    }
}
///Struct para o ranked
struct Pontuacao   //Salva todas as variáveis que vão ser escritas no console
{
    string nome;
    int dificuldade;
    int pontos;
    int alvo;
    int vidas;
    int vidasAUX;
    int fase;
    int minutos;
    int segundos;
    int segundos2;
    int valorRank; //(Ordem das pontuações)
};
///Bool para comparar pontuações
bool comparaPontuacoes(const Pontuacao&a,const Pontuacao&b)
{
    return a.valorRank>b.valorRank;//Maior primeiro
}
///Função que coloca blocos no mapa
void Randomizador(int pontos,int&alvo,int alvoAUX,int m[22][22])
{
    alvo+=alvoAUX;//Novo objetivo de pontos
    for (int i=pontos; i!=alvo; i+=3) ///Randomizador de posição de blocos
    {
        int j=1+(rand()%20); //randomiza horizontalmente
        int k=1+rand()%6; //randomiza verticalmente
        if (m[k][j]==0)  ///Coloca um bloco no mapa se a célula aleatória estiver vazia
        {
            m[k][j]=2; //Coloca um bloco
        }
        else
        {
            i-=3;//falhou
        }
    }
}
///Função que coloca mapas em "m"
void gerarMapas(int pontos,int&alvo,int alvoAUX,int dificuldade,int m[22][22],int fase)
{
    if (fase==1)
    {
        int a[22][22]= {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                        1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                        1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                        1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                        1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                        1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                        1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                        1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                        1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                        1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                        1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                        1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                        1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                        1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                        1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                        1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                        1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                        1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                        1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                        1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                        1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                        1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
                       };
        for (int i = 0; i < 22; ++i)
        {
            for (int j = 0; j < 22; ++j)
            {
                m[i][j]=a[i][j];///TRANSFERE A NOVA MATRIZ PARA A QUE VAI SER USADA NO JOGO
            }
        }
        Randomizador(pontos,alvo,alvoAUX,m); //Coloca os blocos
    }
    else if (fase==2)
    {
        int b[22][22]= { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                         1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                         1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                         1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                         1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                         1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                         1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                         1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                         1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                         1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                         1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                         1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                         1,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,1,
                         1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                         1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                         1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                         1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                         1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                         1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                         1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                         1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                         1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
                       };
        for (int i = 0; i < 22; ++i)
        {
            for (int j = 0; j < 22; ++j)
            {
                m[i][j]=b[i][j];///TRANSFERE A NOVA MATRIZ PARA A QUE VAI SER USADA NO JOGO
            }
        }
        Randomizador(pontos,alvo,alvoAUX,m); //Coloca os blocos
    }
    else
    {
        int c[22][22]= { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                         1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                         1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                         1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                         1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                         1,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,1,
                         1,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,1,
                         1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                         1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                         1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                         1,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,1,
                         1,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,1,
                         1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                         1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                         1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                         1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                         1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                         1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                         1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                         1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                         1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                         1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
                       };
        for (int i = 0; i < 22; ++i)
        {
            for (int j = 0; j < 22; ++j)
            {
                m[i][j]=c[i][j];///TRANSFERE A NOVA MATRIZ PARA A QUE VAI SER USADA NO JOGO
            }
        }
        Randomizador(pontos,alvo,alvoAUX,m); //Coloca os blocos
    }
}
///Func. para resetar a bolinha
void resetBolinha(int&bolaX,int&bolaY,int&direcaoX,int&direcaoY,int&y)
{
    y=8;
    bolaX=10, bolaY=10; // Posição inicial da bolinha
    direcaoX=-1; // Direção vertical
    direcaoY=(rand()%2)?1:-1;// Direção aleatória horizontal
    Sleep(2000);//espera
    return;
}
///Func. para movimentar a bolinha
void moverBolinha(int&bolaX,int&bolaY,int&direcaoX,int&direcaoY,int m[22][22],int&paddleY,int paddleMax,int&pontos,int&menu,int&fase,bool&jogando,int dificuldade,int&alvo,int alvoAUX,int&vidas,bool&perdeuVida)
{
    srand(static_cast<unsigned int>(time(0)));
///PONTUAÇÃO COMEÇO
    if (pontos >= alvo)   ///Verifica a pontuação
    {
        if (fase==3)  //Se é a última fase
        {
            jogando=false; // Para o jogo e retorna ao menu
            menu=6;
            return; //sair da função
        }
        fase++;//passa a fase
        gerarMapas(pontos,alvo,alvoAUX,dificuldade,m,fase);//gera novo mapa
        resetBolinha(bolaX,bolaY,direcaoX,direcaoY,paddleY);//reseta a bolinha
        return;//sai da func.
    }
///PONTUAÇÃO FIM

///PADDLE COMEÇO
    if ((bolaX+direcaoX==18)&&(bolaY>=paddleY-1)&&(bolaY<=paddleY+paddleMax))
    {
        direcaoX=-1;//Faz a bolinha ir para cima
        if (bolaY==paddleY-1)   ///Bate no extremo esquerdo
        {
            if (bolaY>1)   ///Se não está no canto esquerdo do mapa
            {
                direcaoY=-1; //força esquerda
            }
            else
            {
                direcaoY=1; //força direita
            }
        }
        else if (bolaY == paddleY)     ///Bate no esquerdo
        {
            if (bolaY>1)   ///Se não está no canto esquerdo do mapa
            {
                direcaoY=(rand()%2)? -direcaoY:0; //rebate ou anula
            }
            else
            {
                direcaoY=1; //força direita
            }
        }
        else if (bolaY==paddleY+paddleMax)     ///Bate no extremo direito
        {
            if (bolaY<21)   //Se não está no canto direito do mapa
            {
                direcaoY=1; //força direita
            }
            else
            {
                direcaoY=-1; //força esquerda
            }
        }
        else if (bolaY==paddleY+paddleMax-1)     ///Bate no direito
        {
            if (bolaY<21)   //Se não está no canto direito do mapa
            {
                direcaoY=(rand()%2)? -direcaoY:0; //rebate ou anula
            }
            else
            {
                direcaoY= -1; //força esquerda
            }
        }
        else     ///Bate em qualquer outra posição
        {
            direcaoY= (rand()%3)-1; //qualquer direção
        }
    }
///PADDLE FIM

/// COMEÇO DA CORREÇÃO DE CLIPS
    if (bolaX<1)  ///Corrige clips no teto
    {
        bolaX++; //Força casa 1
        Inverte (bolaX,bolaY,direcaoX,direcaoY,m); //Colide
    }
    if (bolaY<1)  ///Corrige clips na extrema esquerda
    {
        bolaY++; //Força casa 1
        Inverte (bolaX,bolaY,direcaoX,direcaoY,m); //Colide
    }
    else if (bolaY>21)    ///Corrige clips na extrema direita
    {
        bolaY--; //Força casa 21
        Inverte (bolaX,bolaY,direcaoX,direcaoY,m); //Colide
    }
/// FIM DA CORREÇÃO DE CLIPS

///DETECTOR DE COLISÃO COMEÇO
    Colisao (bolaX,bolaY,direcaoX,direcaoY,m,pontos);
    Colisao (bolaX,bolaY,direcaoX,direcaoY,m);
///DETECTOR DE COLISÃO FIM


///COMEÇO ATUALIZA A DIREÇÃO
    bolaX+=direcaoX;
    bolaY+=direcaoY;
///FIMA ATUALIZA DIREÇÃO

/// COMEÇO GAME OVER
    if (bolaX > 19) ///Perde vida
    {
        if (vidas==1) ///Última?
        {
            perdeuVida=true;
            jogando = 0; //Para o jogo e retorna ao menu
            menu = 7; //Menu de derrota
            return; //sair da função
        }
        else ///Mais vidas?
        {
            vidas--; //Diminúi vida
            perdeuVida=true; //Sianaliza que perdeu vida
        }
    }
///FIM GAME OVER
}
///Chance de cair powerUP
void chancePowerUp(int&pox,int&poy,int i,int j,bool&poderPresente)
{
    if (poderPresente==false)  ///Se não há powerup
    {
        int l=(rand()%8); //Chance de cair
        int k=(rand()%8);
        if (l==k)
        {
            pox=i;
            poy=j;
            poderPresente=true;///Cai
        }
    }
}
///Func. do powerup
void powerUp(int&pox,int&poy,int m[22][22],int paddleY,int&paddleMax,int&vidas,int vidasAUX,bool&poderAtivo,bool&poderPresente,int&poderAtivoAUX)
{
    int direcaoPox=1;///sempre cai
    int i;
    pox+=direcaoPox;///atualiza a direção
    if (pox>18)///passou do paddle
    {
        m[pox][poy]=3;//explode
        poderPresente=false;//some
        return;
    }
    if ((pox==18)&&(poy>=paddleY-1)&&(poy<=paddleY+paddleMax))///foi pego pelo paddle
    {
        i=(rand()%2); //cara ou coroa
        if ((i==1)&&(vidas<vidasAUX))
        {
            vidas++; //Aumenta a vida
            poderPresente=false; //some
            return;//sai da função
        }
        if (poderAtivo==false) ///Se o poder ainda não está ativo
        {
            paddleMax++; //Aumenta o paddle
            poderAtivo=true; //começa o timer
            poderPresente=false;//some
            return;
        }
        else
        {
            poderPresente=false; ///Se o poder está ativo
            poderAtivoAUX=0;//Reseta o timer do paddle
        }
    }
}
///Func. que auxilia nas config. de dificuldade
void setarStatus (int menuVoid,int&velocidade,int&alvoAUX,int&vidas,int&vidasAUX,int&paddleMax,int&dificuldade)
{
    if (menuVoid==1) ///dificuldade 1
    {
        velocidade=130;
        alvoAUX=30;//pontos necessarios
        vidas=4;
        vidasAUX=vidas;//console
        paddleMax=4;//Tamanho padrão do paddle
        dificuldade=1;//Seta dificuldade
        return;
    }
    else if (menuVoid==2) ///dificuldade 2
    {
        velocidade=115;
        alvoAUX=60;//pontos necessarios
        vidas=3;
        vidasAUX=vidas;//console
        paddleMax=3;//tamanho padrão do paddle
        dificuldade=2;//Seta dificuldade
        return;
    }
    else if (menuVoid==3) ///dificuldade 3
    {
        velocidade=100;
        alvoAUX=90;//pontos necessarios
        vidas=2;
        vidasAUX=vidas;//console
        paddleMax=2;//tamanho padrão do paddlse
        dificuldade=3;//Seta dificuldade
    }
}
///I.A.
void maquinaAtiva(int bolaX,int bolaY,int direcaoX,int direcaoY,int&paddleY,int paddleMax,int poy,bool poderPresente)
{
    ///Func. para randomizar movimento do paddle
    int m=(rand()%2)?1:0;
    if ((poderPresente==true)&&(((bolaX+direcaoX<9)||direcaoX<0)||((bolaY+2==poy)||(poy==bolaY-2)))) ///PU no mapa e Bola no topo ou subindo, ou PU muito perto da bolinha: Tenta pegar
    {
        if (poy>paddleY+paddleMax) ///Powerup fora do limite direito
        {
            if (paddleY<21-paddleMax)   // limite do mapa em relação ao paddle
            {
                paddleY++;
            }
            return;
        }
        if (paddleY-1>poy) ///Powerup fora do limite esquerdo
        {
            if (paddleY>1)   // limite do mapa
            {
                paddleY--;
            }
            return;
        }
    }
    if (bolaY+direcaoY>paddleY+paddleMax+m) ///Bola fora do limite direito
    {
        if (paddleY<21-paddleMax)   // limite do mapa em relação ao paddle
        {
            paddleY++;
        }
        return;
    }
    if (paddleY-1-m>bolaY+direcaoY) ///Bola fora do limite esquerdo
    {
        if (paddleY>1)   // limite do mapa
        {
            paddleY--;
        }
        return;
    }
}
///Func. para desabilitar powerup
int m=(rand()%2)?1:0;
void powerDown (int&poderAtivoAUX,int&paddleMax,bool&poderAtivo)
{
    if (poderAtivo==true) ///Se ho paddle está exapandido
    {
        paddleMax--;//corrige
        poderAtivoAUX=0;//reseta
        poderAtivo=false;
    }
}
int main()
{
    int menu,submenu,dificuldade=1,pontos,alvo=0,alvoAUX=30,velocidade=130,vidas=4,vidasAUX=4,paddleMax=4,fase; ///Todas as variáveis de jogo por padrão estão no fácil
    int x=18,y=8;/// Posição inicial do personagem no console
    int segundos,segundos2, minutos,poderAtivoAUX=0;///Variáveis de timer
    int bx,by,dx,dy,pox,poy;///Variáveis de entidade
    bool jogando,perdeuVida,poderAtivo,poderPresente,maquinaJogando=false;///Variáveis auxilaires
    string nome;
    int m[22][22];///Matriz mapa
    cout<<"\nBEM VINDO AO ARKANOID LITE!\n\nInsira seu nome de jogador: "<<endl;
    cin>>nome;
    system("cls");//limpa a tela
    menuInicial (menu,nome);//chama o menu
    while (menu!=5)
    {
        switch (menu)
        {
        case 1:
            fase=1;
            jogando=true;//jogando agora
            perdeuVida=false; //seta bools para false
            poderAtivo=false;
            poderPresente=false;
            pontos=0;//zera os pontos
            segundos2=0, segundos=0, minutos=0;//zera o timer
            setarStatus (dificuldade,velocidade,alvoAUX,vidas,vidasAUX,paddleMax,dificuldade);///Define as variáveis com base na dificuldade
            gerarMapas(pontos,alvo,alvoAUX,dificuldade,m,fase);///Faz o mapa aleatório
            resetBolinha(bx,by,dx,dy,y);///Seta a bolinha no mapa
            alvo=alvoAUX;//começa pelo menor objetivo
            system("cls");//limpa a tela
///COMEÇA O JOGO
            do
            {
                // INICIO: COMANDOS PARA QUE O CURSOR NAO FIQUE PISCANDO NA TELA
                HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
                CONSOLE_CURSOR_INFO cursorInfo;
                GetConsoleCursorInfo(out, &cursorInfo);
                cursorInfo.bVisible = false; // set the cursor visibility
                SetConsoleCursorInfo(out, &cursorInfo);
                // FIM: COMANDOS PARA QUE O CURSOR NAO FIQUE PISCANDO NA TELA
                // INICIO: COMANDOS PARA REPOSICIONAR O CURSOR NO INICIO DA TELA
                short int CX = 0, CY = 0;
                COORD coord;
                coord.X = CX;
                coord.Y = CY;
                // FIM: COMANDOS PARA REPOSICIONAR O CURSOR NO INICIO DA TELA

                // Inicializa o gerador de números aleatórios
                srand(static_cast<unsigned int>(time(0)));
                // Variável para tecla pressionada
                char tecla;

                /// COMEÇO DAS VARIÁVEIS DE TEMPO
                DWORD lastUpdate = GetTickCount(); //Contagem de ticks para a bola
                DWORD ballUpdateInterval = velocidade; // Intervalo para atualização da bolinha em milissegundos
                DWORD lastTimer = GetTickCount(); //Contagem de ticks para o timer
                /// FIM DAS VARIÁVEIS DE TEMPO

                ///Enquanto não houver game over:
                while (jogando==true)
                {
                    // Posiciona a escrita no início do console
                    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
                    ///COMEÇO DE DWORD TIMER
                    DWORD currentTimer=GetTickCount();
                    if (currentTimer-lastTimer>999) ///Tick equivalente a um segundo
                    {
                        segundos++;///Unidade
                        if (segundos>9)
                        {
                            segundos=0;
                            segundos2++;///Dezena
                        }
                        if (segundos2>5)
                        {
                            segundos2=0;
                            minutos++;///Minutos
                        }
                        if (poderAtivo==true) ///Se ho paddle está exapandido
                        {
                            poderAtivoAUX++;//conta 1 segundo
                            if (poderAtivoAUX>9)//no décimo
                            {
                                powerDown (poderAtivoAUX,paddleMax,poderAtivo);
                            }
                        }
                        lastTimer=currentTimer;
                    }
                    ///FIM DWORD TIMER

                    ///COMEÇO DWORD PARA CHAMAR A BOLINHA, COLISÕES, I.A.
                    DWORD currentTick = GetTickCount();

                    if (currentTick - lastUpdate > ballUpdateInterval)///Tick da bolinha variado pela dificuldade
                    {
                        lastUpdate = currentTick;
                        for (int i= 0; i <22; i++)///Analisa o mapa
                        {
                            for (int j=0; j<22; j++)
                            {
                                if (m[i][j]==3) ///Achou bloco explodindo
                                {
                                    chancePowerUp(pox,poy,i,j,poderPresente);//Chance de powerup
                                    m[i][j]=0;//Apaga a explosão
                                }
                            }
                        }
                        moverBolinha(bx,by,dx,dy,m,y,paddleMax,pontos,menu,fase,jogando,dificuldade,alvo,alvoAUX,vidas,perdeuVida); ///Chama a bolinha
                        if (maquinaJogando==true)  ///Se a máquina estiver jogando
                        {
                            maquinaAtiva(bx,by,dx,dy,y,paddleMax,poy,poderPresente);//Chama I.A.
                        }
                        if (poderPresente==true)  ///Se um powerup estiver presente
                        {
                            powerUp(pox,poy,m,y,paddleMax,vidas,vidasAUX,poderAtivo,poderPresente,poderAtivoAUX);//Chama powerUP
                        }
                    }
                    ///FIM DWORD PARA CHAMAR A BOLINHA E COLISÕES
                    /// Imprime o jogo: mapa, paddle e bolinha
                    for (int i=0; i<22; i++)
                    {
                        for (int j=0; j<22; j++)
                        {
                            if (i==x&&j>=y&&j<=y+paddleMax-1) ///Paddle
                            {
                                cout << "=";
                            }
                            else if (i == bx && j == by)
                            {
                                if (perdeuVida==false) ///Player vivo
                                {
                                    cout << "O"; // bolinha
                                }
                                else
                                {
                                    cout << char(206); ///Morreu
                                    poderPresente=false;//Reseta os poderes no mapa
                                    powerDown (poderAtivoAUX,paddleMax,poderAtivo);
                                    resetBolinha(bx,by,dx,dy,y);//reseta a bolinha
                                    perdeuVida=false;///Continua
                                }
                            }
                            else if ((i==pox&&j==poy)&&(poderPresente==true))///Se há um powerup
                            {
                                cout<<"$";//lootbox
                            }
                            else
                            {
                                switch (m[i][j])///Mapa
                                {
                                case 0:
                                    cout<<" ";
                                    break; // caminho
                                case 1:
                                    cout<<char(219);
                                    break; // parede
                                case 3:
                                    cout<<char(206);
                                    break; // explosão
                                default:
                                    cout<<char(35);
                                    break;//blocos
                                }
                            }
                        }
                        cout<<"\n";
                    }
                    if (maquinaJogando==false)///Se não é a maquina, mostra o nome
                    {
                        cout<<nome;
                    }
                    else
                    {
                        cout<<"CPU";
                    }
                    cout<<"\nVidas: "<<vidas<<"/"<<vidasAUX; //Vidas X de Y
                    cout<<"\nPontos: "<<pontos<< " de "<<alvo; //Pontos e alvo da fase
                    cout<<"\nTempo: "<<minutos<<" : "<<segundos2<<segundos; //Timer
                    if (poderAtivo==true) ///Se o paddle está modificado
                    {
                        cout<<"\nTempo de bonus: 0:0"<<9-poderAtivoAUX; //mostra o timer
                    }
                    else
                        cout<<"\n                       "; //se não apaga
                    /// Executa os movimentos do personagem
                    if (_kbhit())
                    {
                        tecla = getch();
                        switch (tecla)
                        {
                        case 75:
                            if (maquinaJogando==false)
                            {
                            case 'a': /// esquerda
                                if (y>1)   /// limite do mapa
                                {
                                    y--;
                                }
                            }
                            break;
                        case 77:
                            if (maquinaJogando==false)
                            {
                            case 'd': /// direita
                                if (y<21-paddleMax)   /// limite do mapa em relação ao paddle
                                {
                                    y++;
                                }
                            }
                            break;
                        }
                    }
                }

            }
            while (jogando==1);
            break;

        case 2:
            do
            {
                system("cls");
                cout<<"Dificuldade atual: ";///Mostra a dificuldade atual
                if (dificuldade==1)
                {
                    cout<<"Facil\n";
                }
                else if (dificuldade==2)
                {
                    cout<<"Medio\n";
                }
                else if (dificuldade==3)
                {
                    cout<<"Dificil\n";
                }
                cout<<"Maquina VS Maquina: ";
                if (maquinaJogando==true)///Mostra se a CPU vs CPU está ativa
                {
                    cout<<"Habilitado\n";
                }
                else
                {
                    cout<<"Desabilitado\n";
                }
                cout<<"\nSELECIONAR NOVA DIFICULDADE?\n" << endl; //menu
                cout<<"[ 1 ] FACIL\n";
                cout<<"[ 2 ] MEDIO\n";
                cout<<"[ 3 ] DIFICIL\n";
                cout<<"[ 4 ] MAQUINA VS MAQUINA\n";
                cout<<"[ 0 ] SALVAR E SAIR\n";
                cin>>submenu;
                if ((submenu>0)&&(submenu<4))///Se a opção escolhida é de dificuldade
                {
                    setarStatus (submenu,velocidade,alvoAUX,vidas,vidasAUX,paddleMax,dificuldade);//puxa func.
                    submenu=99;//reseta esse menu
                }
                if (submenu==4) ///Se é para ativar a CPU
                {
                    maquinaJogando=!maquinaJogando;//inverte o bool
                    submenu=99;//reseta esse menu
                }
            }
            while (submenu!=0);///Sai se ==0
            system("cls");
            menuInicial (menu,nome);///Mostra menu inicial
            break;

        case 3: ///MENU SOBRE
            system("cls");//Quem precisa de enter e endl;?
            cout<<"COMO JOGAR:\n1) Utilize as teclas 'A' e 'D' ou setas para mover o paddle\n2)Nao deixe a bolinha cair, ou perdera vidas!\nSe perder todas as vidas, o jogo acaba, e sua pontuacao sera salva!\n3)Voce ganha destruindo todos os blocos de todas as tres fases!\n4)Pegar bonus ($) durante o jogo pode aumentar seu paddle ou regenerar vidas!";
            cout<<"\n\nARKANOID\nFoi lancado pela Taito em 1986\nE um jogo de quebrar blocos usando uma bolinha.\nSeu objetivo e destruir todos os blocos na tela.\nO jogador controla uma 'nave' (paddle) para rebater a bolinha.\nCom o tempo, surgiram versoes modernas e remakes.";
            cout<<"\n\nARKANOID LITE\nEsta e minha versao simplificada do classico.\nCom jogabilidade e controles simples.\nBlocos, paredes e paddle compoem o desafio.\nDesenvolvido em C++ no Code::Blocks.";
            menuInicial (menu,nome);//chama o menu inicial
            break;
        case 4:  ///RANKED
        {
            system("cls");
            ifstream arquivo("pontuacoes.txt");///Abre o arquivo
            vector<Pontuacao> pontuacoes;///Coloca as pontuações num vetor (obrigado GPT)
            if (arquivo.is_open())
            {
                Pontuacao p;//struct
                /// Lê todo o arquivo
                while (arquivo>>p.nome>>p.dificuldade>>p.pontos>>p.alvo>>p.vidas>>p.vidasAUX>>p.fase>>p.minutos>>p.segundos2>>p.segundos)
                {
                    p.valorRank=p.dificuldade*p.pontos; ///O rank é ordenado pelos pontos multiplicados pela dificuldade
                    pontuacoes.push_back(p); //Adiciona à lista
                }
                arquivo.close();
                /// Ordenar as pontuações pelo valorRank
                sort(pontuacoes.begin(), pontuacoes.end(), comparaPontuacoes);//Bruxaria do GPT
                cout << "Top 5 Rank local:\n";
                for (size_t i=0; i<min(pontuacoes.size(),size_t(5)); ++i)
                {
                    const Pontuacao& p = pontuacoes[i];
                    cout <<p.nome<<", dificuldade: "<<p.dificuldade<<", pontos: "<<p.pontos<<"/"<<p.alvo<<", "<<p.vidas<<"/"<<p.vidasAUX<<", fase: "<<p.fase<<", "<<p.minutos<<":"<<p.segundos2<<p.segundos<<"\n";
                }
            }
            else
            {
                cout<<"Erro ao abrir o Rank local!\nSinto muito, "<<nome<<"\n\n";
            }
            cout<<"\n";
            menuInicial (menu,nome);
        }
        break;
        case 5: ///SAIR
            return 0;
            break;
        case 6: /// VITÓRIA
            system("cls");
            if (maquinaJogando==false)
            {
                cout << "\n\nVOCE VENCEU! PARABENS, "<<nome<<"!\nOBRIGADO POR JOGAR!\n"<< endl;
                salvandoPontos(nome,dificuldade,pontos,alvo,vidas,vidasAUX,fase,minutos,segundos,segundos2);
            }
            menuInicial (menu,nome);
            break;
        case 7: /// DERROTA
            system("cls");
            if (maquinaJogando==false)
            {
                cout << "\n\nVOCE PERDEU!\nPARABENS, "<<nome<<", PELOS "<<pontos<<" PONTOS!\n"<< endl;
                salvandoPontos(nome,dificuldade,pontos,alvo,vidas,vidasAUX,fase,minutos,segundos,segundos2);
            }
            menuInicial (menu,nome);
            break;
        default: /// INVÁLIDO
            system("cls");
            menuInicial (menu,nome);//chama menu
            break;
        }
    }
}
