# DENETER

Deneter é um jogo em que você precisa defender a floresta contra lenhadores, escavadores, queimadas
e outros perigos! Para concluir essa missão, você contará com a ajuda dos amigos da floresta e
de diversos upgrades poderosos!

É um jogo de tower defense inspirado em Plants vs Zombies, com a presença de algumas melhorias
para deixar o jogo mais interessante e progressivo.

<img width="1915" height="1044" alt="image" src="https://github.com/user-attachments/assets/b134aa94-c530-4d76-87f7-4e219922b6b6" />

<img width="1913" height="1043" alt="image" src="https://github.com/user-attachments/assets/f5bc68f4-3a9c-4e64-941c-b9a17495a8bf" />



# Grupo 1:
- Davi Nobre Oliveira
- Gabriel Silvério Tavares
- Pedro Henrique Carvalho Martins
- Davi Aziz Santos Salazar
- Enzo de Freitas Alencar

# Como compilar:
**NO LINUX**:

1. Instale a biblioteca SFML 2.6.1
- Você pode caso queira instalar via terminal com o comando: sudo apt-get install libsfml-dev
- Confira sua versão com o comando: apt show libsfml-dev

2. Navegue até a pasta do projeto via terminal
- Use o comando: make run


**NO WINDOWS**:

1. Instale a biblioteca SFML 2.6.1 
- O site possui as versões antigas
- Inclua a pasta do SFML em include

2. Instale Mingw 13.1.0 compatível com SFML 2.6.1
- Configure Mingw propriamente (use PATH do sistema, inclua os arquivos de biblioteca estática em lib do Mingw se necessário)
- Confira sua versão com o comando: g++ --version

3. Inclua os .dlls do SFML na pasta do executável

4. No main.cpp, mude const bool WINDOWS = false; para const bool WINDOWS = true;

5. Navegue até a pasta do projeto via terminal
- Use o comando: make run ou mingw32-make run



# Controles:
**ESC:** Pausa o jogo.

**MOUSE ESQUERDO:** Compra e posiciona as tropas. Também é usado para comprar upgrades.

**MOUSE DIREITO:** Remove uma tropa do espaço dela se o mouse estiver em cima da tropa.
                   Também é usado para cancelar a compra.

**TAB:** Alterna entre a sala de upgrades e a sala principal do jogo.
