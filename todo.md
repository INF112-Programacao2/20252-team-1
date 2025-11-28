# Bug ou Feature?
- Leitura da posição do mouse para de funcionar se o tamanho da janela mudar (o jogo deveria rodar em uma resolução fixa de qualquer maneira)
- O elefante é extremamente impreciso

# Bugs:
- Fullscreen não funciona em todos os PCs e nem na versão compilada para windows
- Menu de pause não aparece na UpgradeRoom (obviamente porque não foi implementado lá)
- Sair do jogo sem jogar reseta o save (porque não deveria estar salvando no final do jogo)
- Reembolso de dinheiro ao cancelar compra de tropas é multiplicado pelo upgrade de dinheiro

# Refatoração:
- Usar um sistema melhor pra definir o tamanho da tela e onde posicionar as coisas

# Perguntas sobre implementação:
- FieldTroop deveria ser posicionada em grid (horizontalmente)?

# Pra fazer:
- SEPARAR A HUD DO MENU DA LOJA
- Mais upgrades
- Mais tropas
- Mais inimigos
- Tela de menu inicial (por tutorial e créditos)
- Efeitos sonoros / música
- Logica de ganhar o jogo (salvar a wave anterior à vitória)
- Mostrar o efeito de explosão da noz e da tropa ouriço
- Efeitos de dano melhores no muro
- Balancear a dificuldade

# Sugestões de upgrades:
- Aumentar o raio de ataque do esquilo/ouriço
- Aumentar o stun do guarda/slowndown do macaco (mas precisa nerfar antes)

# Sprites:
- Todos

# Pedro:
- Upgrade de aumentar o dano geral nos inimigos (damage_multiplier) "ta feito com a descrição errada" (esse é mais roubado então aumenta o preço e diminui o incremento do multiplicador)
- Upgrade de aumentar o dano da tropas (troop_damage_multiplier) "não ta feito, mas tem descrição"

# Davi Nobre:
- Salvar o jogo somente no inicio de uma wave

# Gabriel:
- Implementar destroy do Muro (esperar o jogo estar implementado 100%)
- Ajudar com tropas e inimigos
- Ajudar com upgrades
- Ajudar a balancear a dificuldade