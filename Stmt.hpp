// Copyright 2020 <Copyright hulin>

/*
program     → declaration* EOF ;

declaration → varDecl
            | statement ;

statement → exprStmt
          | ifStmt
          | printStmt
          | block ;

ifStmt    → "if" "(" expression ")" statement ( "else" statement )? ;

block     → "{" declaration* "}" ;

primary → "true" | "false" | "nil"
        | NUMBER | STRING
        | "(" expression ")"
        | IDENTIFIER ;
varDecl → "var" IDENTIFIER ( "=" expression )? ";" ;
*/

#ifndef STMT_HPP_
#define STMT_HPP_

#include <string>
#include <iostream>
#include <memory>
#include <vector>
#include "./Token.hpp"
#include "./Expr.hpp"

using std::string;
using std::shared_ptr;
using std::cout;
using std::endl;
using std::vector;

class Expression;
class Print;
class Var;
class Block;
class If;

class Visitor_Stmt {
 public:
    virtual ~Visitor_Stmt() = default;
    virtual void visitExpressionStmt(const Expression& stmt) = 0;
    virtual void visitPrintStmt(const Print& stmt) = 0;
    virtual void visitVarStmt(const Var& stmt) = 0;
    virtual void visitBlockStmt(const Block& stmt) = 0;
    virtual void visitIfStmt(const If& stmt) = 0;
};

class Stmt {
 public:
    virtual void accept(shared_ptr<Visitor_Stmt> visitor) = 0;
    virtual ~Stmt() = default;  // for derived class
};


class Expression: public Stmt {
 public:
    explicit Expression(shared_ptr<Expr<Object>> expression_):
        expression(expression_) { }
    void accept(shared_ptr<Visitor_Stmt> visitor) override {
        visitor->visitExpressionStmt(*this);
    }
    shared_ptr<Expr<Object>> expression;
};


class Print: public Stmt {
 public:
    explicit Print(shared_ptr<Expr<Object>> expression_):
        expression(expression_) { }
    void accept(shared_ptr<Visitor_Stmt> visitor) override {
        visitor->visitPrintStmt(*this);
    }
    shared_ptr<Expr<Object>> expression;
};

class Var: public Stmt {
 public:
    explicit Var(Token name_, shared_ptr<Expr<Object>> initializer_):
        initializer(initializer_), name(name_) { }
    void accept(shared_ptr<Visitor_Stmt> visitor) override {
        visitor->visitVarStmt(*this);
    }
    shared_ptr<Expr<Object>> initializer;
    Token name;
};

class Block: public Stmt {
 public:
    explicit Block(vector<shared_ptr<Stmt>> statements_):
        statements(statements_) { }
    void accept(shared_ptr<Visitor_Stmt> visitor) override {
        visitor->visitBlockStmt(*this);
    }
    vector<shared_ptr<Stmt>> statements;
};

class If: public Stmt {
 public:
    If(
        shared_ptr<Expr<Object>> condition_,
        shared_ptr<Stmt> thenBranch_,
        shared_ptr<Stmt> elseBranch_):
        condition(condition_),
        thenBranch(thenBranch_),
        elseBranch(elseBranch_) { }
    void accept(shared_ptr<Visitor_Stmt> visitor) override {
        visitor->visitIfStmt(*this);
    }
    shared_ptr<Expr<Object>> condition;
    shared_ptr<Stmt> thenBranch;
    shared_ptr<Stmt> elseBranch;
};

#endif  // STMT_HPP_
