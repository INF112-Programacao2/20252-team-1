# DENETER

Um jogo de tower defense inspirado em Plants vs Zombies com temática ambiental e com presença de upgrades para deixar a gameplay mais interessante.

# Grupo 1:
- Davi Aziz Santos Salazar
- Davi Nobre Oliveira
- Enzo de Freitas Alencar
- Gabriel Silvério Tavares
- Pedro Henrique Carvalho Martins

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
**ESC:** pausa o jogo

**MOUSE ESQUERDO:** para comprar e posicionar as tropas

**MOUSE DIREITO:** remove uma tropa se o mouse estiver em cima dela ou cancela a compra

**TAB:** abre a sala de upgrades e sai dela também