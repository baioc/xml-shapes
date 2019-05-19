Trabalho de Implementação I - Processamento de XML com imagens binárias
====

Copyright &copy; 2019 <[Alek Frohlich](https://github.com/alekfrohlich), [Gabriel B. Sant'Anna](https://github.com/baioc)>

Veja a [documentação](doc/latex/refman.pdf).

## Objetivo

Este trabalho consiste na utilização de **estruturas de dados lineares**, vistas até o momento no curso, e aplicação de conceitos de **pilha** e/ou **fila** para o processamento de arquivos **XML** contendo **imagens binárias**.
A implementação deverá resolver dois problemas (listados a seguir), e os resultados deverão ser formatados em saída padrão de tela de modo que possam ser automaticamente avaliados no VPL.

## Materiais

De modo a exemplificar as entradas para o seu programa, segue os arquivos XML utilizados no primeiro teste:

- [dataset01.xml](https://moodle.ufsc.br/pluginfile.php/2735418/mod_resource/content/1/dataset01.xml)
  - [visualização ampliada das imagens contidas no mesmo](https://moodle.ufsc.br/pluginfile.php/2735421/mod_resource/content/1/dataset01-images.png)
- [dataset02.xml](https://moodle.ufsc.br/pluginfile.php/2753879/mod_resource/content/2/dataset02.xml)
- [dataset03.xml](https://moodle.ufsc.br/pluginfile.php/2753881/mod_resource/content/2/dataset03.xml)
- [dataset04.xml](https://moodle.ufsc.br/pluginfile.php/2753881/mod_resource/content/2/dataset04.xml)
- [dataset05.xml](https://moodle.ufsc.br/pluginfile.php/2753881/mod_resource/content/2/dataset05.xml)
- [dataset06.xml](https://moodle.ufsc.br/pluginfile.php/2753881/mod_resource/content/2/dataset06.xml)

### Composição da nota:
- Nota automática do [VPL](https://moodle.ufsc.br/mod/vpl/view.php?id=1798658)<sup>*</sup>: **70%**
  * (*) Caso algum caso de teste não tenha sido bem sucedido, o aluno opcionalmente poderá defender sua solução no dia reservado à apresentação do Trabalho de Implementação I.
- [Relatório em PDF](doc/latex/refman.pdf) (utilize [este link](https://moodle.ufsc.br/mod/assign/view.php?id=1798666) para a submissão) com todas as explicações pertinentes e documentação<sup>**</sup> do código: **30%**
  * (**) Sugere-se a escrita no próprio código usando a notação [Doxygen](http://www.doxygen.nl/manual/docblocks.html) com a geração automática de [LaTeX](doc/latex/refman.tex)/[PDF](doc/latex/refman.pdf).


# Primeiro problema: validação de arquivo XML

Para esta parte, pede-se exclusivamente a **verificação de aninhamento e fechamento das marcações** (tags) no arquivo XML (qualquer outra fonte de erro pode ser ignorada).
Um identificador (por exemplo: `img`) constitui uma marcação entre os caracteres `<` e `>`, podendo ser de abertura (por exemplo: `<img>`) ou de fechamento com uma `/` antes do identificador (por exemplo: `</img>`).

Como apresentando em sala de aula, o algoritmo para resolver este problema é baseado em pilha (**LIFO**):
- Ao encontrar uma marcação de abertura, empilha o identificador.
- Ao encontrar uma marcação de fechamento, verifica se o topo da pilha tem o mesmo identificador e desempilha.
Aqui duas situações de erro podem ocorrer:
  - Ao consultar o topo, o identificador é diferente (ou seja, uma marcação aberta deveria ter sido fechada antes);
  - Ao consultar o topo, a pilha encontra-se vazia (ou seja, uma marcação é fechada sem que tenha sido aberta antes);
- Ao finalizar a análise (parser) do arquivo, é necessário que a pilha esteja vazia.
Caso não esteja, mais uma situação de erro ocorre, ou seja, há marcação sem fechamento.


# Segundo problema: contagem de componentes conexos em imagens binárias representadas em arquivo XML

Cada XML contém imagens binárias, com altura e largura definidas respectivamente pelas marcações `<height>` e `<width>`, e sequência dos pixels com valores binários, de intensidade **0 para preto** ou **1 para branco**, em modo texto (embora fosse melhor gravar 1 byte a cada 8 bits, optou-se pelo modo texto por simplicidade), na marcação `<data>`.

Para cada uma dessas imagens, pretende-se **calcular o número de *componentes conexos*** usando **vizinhança-4**.
Para isso, seguem algumas definições importantes:
- A ***vizinhança-4*** de um pixel na linha *x* e coluna *y*, ou seja, na coordenada **(x, y)**, é um conjunto de pixels adjacentes nas coordenadas:
```
         (x, y+1)
(x-1, y)          (x+1, y)
         (x, y-1)
```
- Um ***caminho*** entre um um pixel *p<sub>1</sub>* e outro *p<sub>n</sub>* é uma sequência de pixels distintos **<p<sub>1</sub>,p<sub>2</sub>,...,p<sub>n</sub>>**, de modo que *p<sub>i</sub>* é **vizinho-4** de *p<sub>i+1</sub>*; sendo i=1,2,...,n-1
- Um pixel *p* é ***conexo*** a um pixel *q* se existir um **caminho** de *p* a *q* (no contexto deste trabalho, só há interesse em pixels com intensidade 1, ou seja, brancos).
- Um ***componente conexo*** é um *conjunto maximal* (não há outro maior que o contenha) *C* de pixels, no qual **quaisquer dois pixels** selecionados deste conjunto *C* são **conexos**.

Para a determinação da quantidade de componentes conexos, antes é necessário atribuir um **rótulo** inteiro e crescente (1, 2, ...) para cada pixel de cada componente conexo.
Conforme apresentado em aula, segue o algoritmo de rotulação (*labeling*) usando uma fila (**FIFO**):
- Inicializar `rótulo` com 1.
- Criar uma matriz `R` de zeros com o mesmo tamanho da matriz de entrada `E` lida.
- Varrer a matriz de entrada `E`.
  - Assim que encontrar o primeiro pixel de intensidade **1 ainda não visitado** (igual a **0** na mesma coordenada em `R`).
    - Inserir `(x,y)` na fila.
    - Na coordenada `(x,y)` da imagem `R`, atribuir o `rótulo` atual.
  - Enquanto a fila não estiver vazia:
    - Remover `(x,y)` da fila.
    - Inserir na fila as coordenadas dos quatro vizinhos que estejam dentro do domínio da imagem (não pode ter coordenada negativa ou superar o número de linhas ou de colunas), com intensidade **1** (em `E`) e ainda não tenha sido visitado (igual a **0** em `R`).
      - Na coordenada de cada vizinho selecionado, na imagem `R`, atribuir o `rótulo` atual.
  - Incrementar o `rótulo`.
- O conteúdo final da matriz `R` corresponde ao resultado da rotulação.
A **quantidade de componentes conexos**, que é a resposta do segundo problema, é igual ao último e **maior *rótulo* atribuído**.
