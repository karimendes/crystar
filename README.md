<div align="center">
  <h1>Documentação – Crystar</h1>
</div>

A **Crystar** é uma linguagem de programação fortemente tipada desenvolvida para fins acadêmicos, com sintaxe inspirada em C. O projeto implementa análise léxica, análise sintática, análise semântica e construção de Árvore Sintática Abstrata (AST), permitindo o estudo dos principais conceitos envolvidos no desenvolvimento de compiladores.

Os programas da linguagem utilizam a extensão .star e oferecem suporte a declarações de variáveis, estruturas condicionais, laços de repetição e expressões aritméticas e relacionais.


## 🚀 Tecnologias Utilizadas

**Linguagem**:
- C

## Conceitos Aplicados

- Análise Léxica (Lexer)
- Análise Sintática (Parser)
- Análise Semântica 
- Árvore Sintática Abstrata (AST)
- Gramáticas Livres de Contexto
- Estruturas de Dados
- Tratamento de Erros

## 🧩 Estrutura do Projeto

```text
crystar/
├── README.md      → Documentação do projeto 
├── ast.h          → Definições da AST
├── codigo.star    → Exemplo de programa na linguagem Crystar
├── lexer.c        → Analisador léxico 
├── main.c         → Execução do compilador
├── parser.c       → Analisador sintático 
├── semantic.c     → Analisador semântico 
├── symbol.c       → Implementação da tabela de símbolos 
├── symbol.h       → Definições da tabela de símbolos 
└── token.h        → Definição dos tokens
```

## 🎯 Funcionalidades

### Análise Léxica

- Reconhecimento de identificadores
- Palavras reservadas
- Literais inteiros
- Literais reais
- Literais booleanos
- Literais char
- Literais string
- Operadores aritméticos
- Operadores relacionais

### Análise Sintática

- Declaração de variáveis
- Atribuições
- Blocos de código
- Estruturas condicionais (`if`)
- Estruturas de repetição (`for`)
- Expressões aritméticas
- Expressões relacionais

### Análise Semântica

- Verificação de variáveis declaradas antes do uso
- Verificação de redeclaração de variáveis
- Verificação de atribuições válidas
- Controle da tabela de símbolos
- Identificação de erros semânticos durante a compilação

### Tabela de Símbolos

- Armazenamento de identificadores
- Controle de declarações
- Verificação de redeclarações
- Suporte à análise semântica

### AST (Abstract Syntax Tree)

O compilador gera uma Árvore Sintática Abstrata contendo:

- Programa
- Declarações
- Atribuições
- Blocos
- Estruturas condicionais
- Estruturas de repetição
- Operações binárias
- Literais
- Identificadores

### Tratamento de Erros

- Erros léxicos
- Erros sintáticos
- Erros semânticos
- Mensagens descritivas para depuração

## 🌳 Exemplo de AST

### Código de entrada

```crystar
int x = 10;

x = x + 2;

if (x > 5) {
    x = x * 2;
}
```

### Representação simplificada

```text
Program
├── VarDecl(x, 10)
├── Assign(x)
│   └── BinaryOp(+)
│       ├── x
│       └── 2
└── If
    ├── BinaryOp(>)
    │   ├── x
    │   └── 5
    └── Block
        └── Assign(x)
            └── BinaryOp(*)
```

## ⚙️ Como Compilar

Utilizando GCC:

```bash
gcc main.c lexer.c parser.c semantic.c symbol.c -o crystar
```

## 🛠️ Como Executar

```bash
./crystar
```
O compilador utilizará automaticamente o arquivo:

```text
codigo.star
```

Para testar outro programa, substitua o conteúdo do arquivo `codigo.star` antes da execução.

## 📝 Contribuições
| Nome            |      
|-----------------|
| Karine Ferreira | 
| Rayssa Andrade  |
| Rhaissa Santos  |
