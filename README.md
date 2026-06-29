# Simulador de Sistema de Arquivos (TP2 - SO)

Este é um simulador de sistema de arquivos desenvolvido como Trabalho Prático 2 para a disciplina de Sistemas Operacionais (SO). Ele implementa conceitos fundamentais de sistemas de arquivos reais, como Inodes, blocos de dados, bitmap de Inodes e um superbloco, com suporte a uma árvore de ramificação de diretórios e arquivos interagindo em disco simulado.

## 🚀 Como compilar e executar

O projeto possui um `Makefile` já preparado para compilar o código fonte e gerar os binários na pasta correta (`bin/`), suportando Linux e Windows (MinGW).

Para **compilar**, abra o terminal na pasta raiz do projeto e execute:
```bash
make
```

Para **executar o simulador interativo**, você pode rodar:
```bash
make run
```

E para **limpar os artefatos de compilação**:
```bash
make clean
```

*(Alternativamente, após compilar, você pode executar diretamente com `./bin/simulator` no Linux ou `bin\simulator.exe` no Windows)*.

### Modo Automático (Lote)
Há suporte para inicializar a simulação lendo um roteiro de comandos salvos em arquivo. O `main.c` já possuí lógica para receber entrada do `in/comandos.txt` se você escolher a opção `1 - Arquivo` no menu inicial.

## 💻 Comandos do Interpretador

Após abrir o simulador através do terminal e configurar o tamanho do disco, os seguintes comandos shell estão disponíveis:

- `help` : Mostra a lista de comandos completa.
- `init <tamanho_particao> <tamanho_bloco>` : Formata/Inicializa o sistema de arquivos simulado.
- `mkdir <caminho>` : Cria um novo diretório no caminho indicado.
- `touch <caminho>` : Cria um arquivo vazio. Se já existir, atualiza sua data de acesso e modificação.
- `ls [caminho]` : Lista o conteúdo do diretório (vazio lista o diretório atual `CWD`).
- `rename <caminho/nome_atual> <novo_nome>` : Renomeia um arquivo ou diretório existente.
- `rm [-r] <caminho>` : Remove um arquivo. Para remover diretórios e seu conteúdo, exige-se a flag `-r`.
- `cat <caminho>` : Exibe o conteúdo em texto de um arquivo específico.
- `escreva <caminho> <id_doc>` : Escreve dados no arquivo existente, apontando para o id do texto de carga inicial predefinido no arquivo `data.txt`.
- `listarDocSimulados` : Lista os documentos gerados/estáticos pela camada simulada.
- `mv <caminho_origem> <caminho_destino>` : Move arquivos ou pastas de um lugar para outro.
- `exit` ou `quit` : Finaliza a simulação de modo seguro.

## 📂 Estrutura do Projeto

- `src/` : Código fonte contendo toda a lógica do simulador (interpretador, gerenciamento de disco, blocos, diretórios, inodes e gerenciamento de arquivos de leitura).
- `include/` : Arquivos de cabeçalho (`.h`) definindo a abstração de cada entidade.
- `in/` e `data/` : Contém os arquivos para entrada de testes e leitura inicial do banco de testes de simulação.
- `Makefile` : Script Makefile de automação.