Dicas:

- [ ] Adicione uma nova função de thread de trabalho para a maior parte da sincronização do lado do trabalhador.

- [ ] Implemente a fila de tarefas como uma lista ligada individualmente.
- [ ] Use um mutex para proteger as variáveis agregadas globais.
- [ ] Use um mutex para proteger a fila de tarefas.
- [ ] Use uma condição para bloquear e despertar threads de trabalho e considere o uso de seu
      mutex associado para proteger um contador de "thread inativo".
- [ ] Declare variáveis que você não deseja que o compilador otimize usando a palavra-chave volatile.
- [ ] Não se esqueça dos loops do/while!
- [ ] Está tudo bem para o thread mestre utilizar espera-ocupada.
- [ ] Compile com -O0 para depurar e mude para -O2 depois de ter certeza de que o básico está
      funcionando.
- [ ] Crie vários arquivos de entrada de teste e um script para executar automaticamente (e
      cronometrar) todos eles.
- [ ] Tente remover a chamada para "dormir" na função de atualização para comprimir os tempos
      de trabalho e verificar as condições de corrida.
- [ ] Não exagere na engenharia! Quanto menor o código melhor.
