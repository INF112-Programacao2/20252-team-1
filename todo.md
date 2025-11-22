# Bug ou Feature?
- Leitura da posição do mouse para de funcionar se o tamanho da janela mudar (o jogo deveria rodar em uma resolução fixa de qualquer maneira)

# Bugs:
- Fullscreen não funciona em todos os PCs e nem na versão compilada para windows
- dissolving text do UpgradeUI não some quando sai da sala (se não tiver acabado o timer)
- Menu de pause não aparece na UpgradeRoom (obviamente porque não foi implementado lá)

# Refatoração:
- Usar um sistema melhor pra definir o tamanho da tela e onde posicionar as coisas

# Perguntas sobre implementação:
- FieldTroop deveria ser posicionada em grid (horizontalmente)?

# Pra fazer:
- Inimigos
- Tela de menu inicial (por tutorial e créditos)
- Tela de upgrades
- Upgrades
- Mais tropas
- GameSaver
- Efeitos sonoros / música
- Logica de ganhar o jogo (salvar a wave anterior à vitória)

# Sprites:
- Todos

# Pedro:
- Corrigir o BUG dissolving text do UpgradeUI não sumir quando sai da sala
- Fazer o incremento de preço ser um parâmetro da classe UpgradeUI

# Davi Nobre:
- GameSaver (wave, pontos no inicio da wave, tropas no inicio da wave, upgrades, vida do muro no inicio da wave, fieldtroops no inicio da wave)
- Salvar no momento certo
- Poder resetar um save no menu de inicio

# Gabriel:
- Implementar destroy do Muro (esperar projeteis)
- Ajudar com tropas (e inimigos?)
- Ajudar com upgrades
- Ajudar com projetil